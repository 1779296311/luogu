/*********************************************
*     ------------------------
*     ------------------------
*     file name: bipartite_graph.cpp
*     author   : @ JY
*     date     : 2021--01--16
**********************************************/
#include <bits/stdc++.h>

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
