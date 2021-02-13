/*********************************************
*     ------------------------
*     ------------------------
*     file name: bipartite_graph.cpp
*     author   : @ JY
*     date     : 2021--01--16
**********************************************/
#include <bits/stdc++.h>
namespace p1963{
    const int N = 1e5 + 12;
    int head[N], ne[N << 4], to[ N << 4 ];
    int vi[N], match[N];
    int n, idx;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _dfs(int x, int id){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(vi[y] == id)continue;
            vi[y] = id;
            if(match[y]==-1 || _dfs(match[y], id)){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> n;
        for(int i=0, k; i<n; ++i){
            std::cin >> k;
            int a = (i + k + n) % n, b = (i - k + n) % n;
            if(a > b)std::swap(a, b);
            _add(i, a), _add(i, b);
        }
        std::fill(match, match + 3*n, -1);
        for(int i=n-1, id=1; i>=0; --i, ++id){
            if(!_dfs(i, id)){
                std::cout << "No Answer" << std::endl;
                return ;
            }
        }
        std::memset(vi, 0, sizeof vi);
        for(int i=0; i<n; ++i){
            if(match[i+n]!=-1)vi[match[i+n]] = i;
        }
        for(int i=0; i<n; ++i)std::cout << vi[i] << " ";
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p1129{
    const int N = 512;
    int g[N][N];
    int vi[N], match[N];
    int n, t;
    void _init(){
        std::memset(vi, 0, sizeof vi);
        std::memset(g, 0, sizeof g);
        std::memset(match, 0, sizeof match);
    }
    bool _dfs(int x, int id) {
        for(int y=1; y<=n; ++y){
            if(vi[y] == id || !g[x][y])continue;
            vi[y] = id;
            if(!match[y] || _dfs(match[y], id)){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _read(){
        std::cin >> n;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                std::cin >> g[i][j];
            }
        }
    }
    bool _clac(){
        for(int i=1,id=1; i<=n; ++i, ++id){
            if(!_dfs(i, id))return false;
        }
        return true;
    }
    void _deal(){
        std::cin >> t;
        while(t--){
            _init();
            _read();
            if(_clac()){
                std::cout << "Yes" << std::endl;
            }else{
                std::cout << "No" << std::endl;
            }
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p2149{
    using pii = std::pair<int, int>;
    const int N = 2048 << 1, INF = 1000010000;
    int head[N], to[N << 12], ne[N << 12], cost[N << 12];
    int d[4][N], vi[N], ok[N << 12], in[N];
    int g[N], v[N];
    int s1, t1, s2, t2;
    int n, m, idx;
    void _add(int x, int y, int v){
        to[++idx] = y;
        cost[idx] = v;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _dijkstra(int s, int k){
        std::memset(d[k], 0x3f, sizeof d[k]);
        std::memset(vi, 0, sizeof vi);
        d[k][s] = 0;
        std::priority_queue<pii,
            std::vector<pii>, std::greater<pii>> q;
        q.emplace(0, s);
        while(q.size()){
            int x = q.top().second;q.pop();
            if(vi[x])continue;
            vi[x] = 1;
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[k][y] > d[k][x] + cost[i]){
                    d[k][y] = d[k][x] + cost[i];
                    q.emplace(d[k][y], y);
                }
            }
        }
    }
    void _read(){
        std::cin >> n >> m >> s1 >> t1 >> s2 >> t2;
        for(int i=1, x, y, v; i<=m; ++i){
            std::cin >> x >> y >> v;
            _add(x, y, v), _add(y, x, v);
        }
    }
    void _deal(){
        _read();
        _dijkstra(s1, 0), _dijkstra(t1, 1);
        _dijkstra(s2, 2), _dijkstra(t2, 3);
        for(int x=1; x<=n; ++x){
            for(int i=head[x]; i; i=ne[i]){
                int y = to[i];
                if(d[0][x] + cost[i] + d[1][y] == d[0][t1]){
                    ok[i] = 1;
                    ++in[y];
                }
            }
        }
        int ans = 0;
        std::queue<int> q;
        q.emplace(s1);
        while(q.size()){
            int x = q.front();q.pop();
            ans = std::max({ans, g[x], v[x]});
            for(int i=head[x]; i; i=ne[i]){
                if(!ok[i])continue;
                int y = to[i];
                if(d[2][x] + cost[i] + d[3][y]==
                        d[2][t2]){
                    g[y] = std::max(g[y], g[x] + cost[i]);
                }
                if(d[3][x] + cost[i] + d[2][y]==
                        d[2][t2]){
                    v[y] = std::max(v[y], v[x] + cost[i]);
                }
                if(!--in[y])q.emplace(y);
            }
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p2526{
    using pii = std::pair<int, int>;
    const int N = 1024;
    int head[N], to[N << 4], ne[N << 4];
    int vi[N << 4], match[ N << 4 ];
    int n, m, idx;
    pii p1[N], p2[N];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    double _dis(const pii &i1, const pii &i2){
        auto [x1, y1] = i1;
        auto [x2, y2] = i2;
        return sqrt( (x1-x2)*(x1-x2) +
                     (y1-y2)*(y1-y2) );
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i){
            std::cin >> p1[i].first >> p1[i].second;
        }
        for(int i=1; i<=m; ++i){
            std::cin >> p2[i].first >> p2[i].second;
        }
        for(int i=1; i<n; ++i){
            double d = _dis(p1[i], p1[i+1]);
            for(int j=1; j<=m; ++j){
                double d1 = _dis(p1[i], p2[j]) +
                            _dis(p1[i+1], p2[j]);
                if(d * 2 < d1)continue;
                _add(i, j + n);
            }
        }
    }
    bool _dfs(int x, int id) {
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(vi[y] == id)continue;
            vi[y] = id;
            if(!match[y] || _dfs(match[y], id)){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        _read();
        int ans = 0;
        for(int i=1, id=1; i<=n; ++i, ++id){
            ans += _dfs(i, id);
        }
        std::cout << ans + n << std::endl;
        std::memset(vi, 0, sizeof vi);
        for(int i=1; i<=m; ++i){
            if(match[i+n])vi[match[i+n]] = i;
        }
        for(int i=1; i<=n; ++i){
            std::cout << p1[i].first << " " << p1[i].second;
            if(vi[i])std::cout << " " << p2[vi[i]].first << " " << p2[vi[i]].second;
            std::cout << " ";
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p1640{
    const int N = 1e6;
    int head[N], ne[N << 3], to[N << 3];
    int vi[N << 3], match[ N << 3 ];
    int n, idx;
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _dfs(int x, int id){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(!(vi[y] - id))continue;
            vi[y] = id;
            if(!match[y] || _dfs(match[y], id)){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> n;
        for(int i=1, x, y; i<=n; ++i){
            std::cin >> x >> y;
            _add(x, i), _add(y, i);
        }
        int ans = 0;
        for(int i=1,id=1; i<=10000; ++i, ++id){
            if(!_dfs(i, id))break;
            ++ans;
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p2055{
    const int N = 64;
    int t, n;
    int sc[N], hm[N], e[N][N];
    int vi[N], match[N];
    void _read(){
        std::cin >> n;
        for(int i=1; i<=n; ++i)std::cin >> sc[i];
        for(int i=1; i<=n; ++i)std::cin >> hm[i];
        for(int i=1; i<=n; ++i){
            if(!sc[i])hm[i] = 0;
            for(int j=1; j<=n; ++j){
                std::cin >> e[i][j];
            }
            if(sc[i])e[i][i] = 1;
        }
    }
    bool _dfs(int x){
        for(int y=1; y<=n; ++y){
            if(vi[y] || !e[x][y] || !sc[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _init(){
        std::memset(match, 0, sizeof match);
        std::memset(e, 0, sizeof e);
    }
    bool _calc(){
        for(int i=1; i<=n; ++i){
            std::memset(vi, 0, sizeof vi);
            if(!hm[i] && !_dfs(i))return false;
        }
        return true;
    }
    void _deal(){
        std::cin >> t;
        while(t--){
            _init();
            _read();
            if(_calc()){
	            puts("^_^");
            }else{
			    puts("T_T");
            }
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p2071{
    const int N = 2048 << 2;
    int head[N], ne[N << 4], to[N << 4];
    int match[N << 4], vi[ N << 4 ];
    int n, idx;
    bool _dfs(int x){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    void _deal(){
        std::cin >> n;
        for(int i=1, x, y; i<=n*2; ++i){
            std::cin >> x >> y;
            _add(i, x), _add(i, x + n);
            _add(i, y), _add(i, y + n);
        }
        int ans = 0;
        for(int i=1; i<=2*n; ++i){
            std::memset(vi, 0, sizeof vi);
            ans += _dfs(i);
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p1155{
    const int N = 1024;
    int head[N], ne[N << 4], to[N << 4];
    int n, idx;
    int color[N], nums[N];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _dfs(int x, int co){
        color[x] = co;
        for(int i=head[x], y; i; i=ne[i]){
            y = to[i];
            if(color[y] == color[x])return false;
            if(!color[y] && !_dfs(y, 3-co))return false;
        }
        return true;
    }
    void _deal(){
        int now = 1, min_ = INT_MAX;
        std::cin >> n;
        for(int i=1; i<=n; ++i)std::cin >> nums[i];
        for(int i=1; i<n-1; ++i){
            min_ = nums[n];
            for(int j=n-1; j>i; --j){
                if(nums[i] < nums[j] && min_ < nums[i]){
                    _add(i, j), _add(j, i);
                }
                min_ = std::min(min_, nums[j]);
            }
        }
        for(int i=1; i<=n; ++i){
            if(!color[i] && !_dfs(i, 1)){
                std::cout << 0 << std::endl;
                return ;
            }
        }
        std::stack<int> s1, s2;
        for(int i=1; i<=n+1; ++i){
            if(color[i] == 1)std::cout << "a ", s1.push(nums[i]);
            if(color[i] == 2)std::cout << "c ", s2.push(nums[i]);
            int case1 = s1.size() && s1.top() == now;
            int case2 = s2.size() && s2.top() == now;
            while(case1 || case2){
                if(case1)std::cout << "b ", s1.pop();
                if(case2){
                    if(color[i+1] == 1)std::cout << "a ", s1.push(nums[++i]);
                    std::cout << "d ", s2.pop();
                }
                ++now;
                case1 = s1.size() && s1.top() == now;
                case2 = s2.size() && s2.top() == now;
            }
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p1263{
    using pii = std::pair<int,int>;
    const int N = 256 << 6;
    int n, m, idx, code1, code2;
    int head[N], ne[N << 10], to[N << 10];
    int match[N << 10], vi[N << 10];
    int e[N][N], mp1[N][N], mp2[N][N];
    pii mp[N][N];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _dfs(int x){
        for(int i=head[x], y; i; i=ne[i]){
            y = to[i];
            if(vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                std::cin >> e[i][j];
            }
        }
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(e[i][j]==2)continue;
                if(mp1[i][j-1]){
                    mp1[i][j] = mp1[i][j-1];
                }else{
                    mp1[i][j] = ++code1;
                }
                if(mp2[i-1][j]){
                    mp2[i][j] = mp2[i-1][j];
                }else{
                    mp2[i][j] = ++code2;
                }
            }
        }
    }
    void _deal(){
        _read();
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(e[i][j])continue;
                _add(mp1[i][j], mp2[i][j]);
                mp[mp1[i][j]][mp2[i][j]] = {i, j};
            }
        }
        int ans = 0;
        for(int i=1; i<=code1; ++i){
            std::memset(vi, 0, sizeof vi);
            ans += _dfs(i);
        }
        std::cout << ans << std::endl;
        for(int i=1; i<=code2; ++i){
            if(!match[i])continue;
            auto [x, y] = mp[match[i]][i];
            std::cout << x << " " << y <<std::endl;
            if(!ans--)break;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p1263_fuck{
    using pii = std::pair<int, int>;
    const int N = 256;
    int n, m, code, code1, code2;
    int e[N][N], g[N][N], mp1[N][N], mp2[N][N];
    int vi[N << 5], match[N << 5];
    pii mp[N][N];
    bool _dfs(int x){
        for(int y=1; y<=code; ++y){
            if(vi[y] || !g[x][y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _read(){
        std::cin >> n >> m;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                std::cin >> e[i][j];
            }
        }
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(e[i][j] == 2)continue;
                if(mp1[i][j-1]){
                    mp1[i][j] = mp1[i][j-1];
                }else{
                    mp1[i][j] = ++code1;
                }
                if(mp2[i-1][j]){
                    mp2[i][j] = mp2[i-1][j];
                }else{
                    mp2[i][j] = ++code2;
                }
            }
        }
        code = std::max(code1, code2);
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=m; ++j){
                if(e[i][j])continue;
                int c1 = mp1[i][j], c2 = mp2[i][j];
                g[c1][c2] = 1;
                mp[c1][c2] = {i, j};
            }
        }
    }
    void _deal(){
        _read();
        int ans = 0;
        for(int i=1; i<=code; ++i){
            std::memset(vi, 0, sizeof vi);
            ans += _dfs(i);
        }
        std::cout << ans << std::endl;
        for(int i=1; i<=code; ++i){
            if(!match[i])continue;
            auto [x,y] = mp[match[i]][i];
            std::cout << x << "  " << y << std::endl;
            if(!ans--)break;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p4014{
    const int N = 128;
    int e[N][N], match[N], va[N], vb[N];
    int la[N], lb[N], upd[N];
    int n;
    bool _dfs(int x){
        va[x] = 1;
        for(int y=1; y<=n; ++y){
            if(vb[y])continue;
            if(la[x] + lb[y] == e[x][y]){
                vb[y] = 1;
                if(!match[y] || _dfs(match[y])){
                    match[y] = x;
                    return true;
                }
            }else{
                upd[y] = std::min(upd[y], la[x]+lb[y]-e[x][y]);
            }
        }
        return false;
    }
    int _km(){
        for(int i=1; i<=n; ++i){
            la[i] = -(1 << 30);
            match[i] = lb[i] = 0;
            for(int j=1; j<=n; ++j){
                la[i] = std::max(la[i], e[i][j]);
            }
        }
        for(int i=1; i<=n; ++i){
            while(true){
                std::memset(va, 0, sizeof va);
                std::memset(vb, 0, sizeof vb);
                for(int j=1; j<=n; ++j)upd[j] = INT_MAX;
                if(_dfs(i))break;
                int delta = INT_MAX;
                for(int j=1; j<=n; ++j){
                    if(!vb[j])delta = std::min(delta, upd[j]);
                }
                for(int j=1; j<=n; ++j){
                    if(va[j])la[j] -= delta;
                    if(vb[j])lb[j] += delta;
                }
            }
        }
        int ans = 0;
        for(int i=1; i<=n; ++i)ans += e[match[i]][i];
        return ans;
    }
    void _deal(){
        int ans1, ans2;
        std::cin >> n;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                std::cin >> e[i][j];
            }
        }
        ans2 = _km();
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                e[i][j] *= -1;
            }
        }
        ans1 = -_km();
        std::cout << ans1 << std::endl;
        std::cout << ans2 << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p2319{
    const int N = 1024;
    int head[N], to[N << 11] , ne[N << 11];
    int n, m, idx;
    int match[N << 11], vi[N << 11], res[N << 11];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _dfs(int x){
        for(int i=head[x], y; i; i=ne[i]){
            y = to[i];
            if(vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                res[x] = y;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=1, x, y; i<=m; ++i){
            std::cin >> x >> y;
            _add(i, ++x), _add(i, ++y);
        }
        int ans = 0;
        for(int i=1; i<=m; ++i){
            std::memset(vi, 0, sizeof vi);
            if(!_dfs(i))break;
            ++ans;
        }
        std::cout << ans << std::endl;
        for(int i=1; i<=ans; ++i){
            std::cout << res[i]-1 << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};

namespace p2756{
#include <bits/stdc++.h>
    const int N = 128 << 1;
    int n, m;
    int e[N][N], vi[N << 2], match[N << 2];
    bool _dfs(int x){
        for(int y=m+1; y<=n; ++y){
            if(vi[y] || !e[x][y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> m >> n;
        for(int x, y ; ;){
            std::cin >> x >> y;
            if(x==-1 || y==-1)break;
            e[x][y] = 1;
        }
        int ans = 0;
        for(int i=1; i<=m; ++i){
            std::memset(vi, 0, sizeof vi);
            ans += _dfs(i);
        }
        std::cout << ans << std::endl;
        for(int i=m+1; i<=n; ++i){
            if(!match[i])continue;
            std::cout << match[i]  << " " << i << std::endl;
        }
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p3386{
    const int N = 512;
    int head[N << 2], ne[N << 4], to[N << 4];
    int n, m, e, idx;
    int vi[N << 2], match[N << 2];
    void _add(int x, int y){
        to[++idx] = y;
        ne[idx] = head[x];
        head[x] = idx;
    }
    bool _dfs(int x){
        for(int i=head[x]; i; i=ne[i]){
            int y = to[i];
            if(vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> n >> m >> e;
        for(int i=0, x, y; i<e; ++i){
            std::cin >> x >> y;
            if(x>n || y>m)continue;
            _add(x, y+n);
        }
        int ans = 0;
        for(int i=1; i<=n; ++i){
            std::memset(vi, 0, sizeof vi);
            ans += _dfs(i);
        }
        std::cout << ans << std::endl;
    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
namespace p2764{
    const int N = 256;
    int n, m;
    int e[N][N], vi[N], match[N], ed[N];
    std::vector<int> pa[N];
    int _dfs(int x){
        for(int y=1; y<=n; ++y){
            if(!e[x][y] || vi[y])continue;
            vi[y] = 1;
            if(!match[y] || _dfs(match[y])){
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    void _deal(){
        std::cin >> n >> m;
        for(int i=0, x, y; i<m; ++i){
            std::cin >> x >> y;
            e[x][y] = 1;
        }
        int ans = n;
        for(int i=1; i<=n; ++i){
            std::memset(vi, 0, sizeof vi);
            ans -= _dfs(i);
        }
        std::memset(vi, 0, sizeof vi);
        for(int i=1; i<=n; ++i)vi[match[i]] = 1;
        for(int i=1, k=0; i<=n; ++i){
            if(!vi[i])ed[++k] = i;
        }
        for(int i=1; i<=ans; ++i){
            pa[i].push_back(ed[i]);
            while(match[ed[i]]){
                ed[i] = match[ed[i]];
                pa[i].push_back(ed[i]);
            }
        }
        for(int i=1; i<=ans; ++i){
            for(int j=pa[i].size()-1; j>=0; --j){
                std::cout << pa[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << ans << std::endl;

    }
    int main(int argc,const char *argv[]){
        _deal();
        return 0;
    }
};
