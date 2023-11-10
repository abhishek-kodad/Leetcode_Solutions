class Solution {
public:
   struct Myhash {
        size_t operator()(const vector<int>& vec) const {
            size_t digest = 0;
            auto f=hash<int>();
            for (const auto& v : vec) {
                digest = f(digest^v);
            }
            return digest;
        }
    };
    unordered_map<vector<int>, unordered_set<int>, Myhash> L;

    void line(vector<vector<int>>& points, int i, int j) {
        int x0 = points[i][0], y0 = points[i][1];
        int x1 = points[j][0], y1 = points[j][1];
        int a = y1 - y0;
        int b = x0 - x1;
        int c = x0 * a + y0 * b;
        int d = gcd(a, b); //c is an integer linear combination of a & b therefore d|c
        a /= d, b /= d, c /= d;
        if (c < 0) {
            a = -a, b = -b, c = -c;
        }
        else if (c==0){ // This can occur!
            if (b<0 || (a<0 && b==0)) a=-a, b=-b;
        }
    //    cout<<"("<<x0<<","<<y0<<"),("<<x1<<","<<y1<<")\n";
        vector<int> lineKey={a, b, c};
    //    cout<<lineKey<<endl;
        L[lineKey].insert(i);
        L[lineKey].insert(j);
    //    cout<<L[lineKey].size()<<"\n----\n";
    }

    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n==1) return 1;// edge case;
        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                line(points, i, j);
            }
        }

        int ans = 0;
        for (auto& [_, set] : L) {
            int v = set.size();
            ans = max(ans, v);
        }

        return ans;
    }
};

