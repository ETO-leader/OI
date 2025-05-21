#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("game.in");
ofstream ouf("game.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
};
using lint=long long;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) [&]{
        lint x,l,r,p,op;inf>>x>>l>>r>>p>>op;
        vector<array<vector<pair<int,int>>,2>> to(p);
        if(r-l+1>p-1) l=0,r=p-1;
        vector in(p,vector(2,r-l+1)),f(p,vector<lint>(2,-1));
        vector vis(p,vector<int>(2));
        cir(u,0,p) cir(ty,0,2) cir(w,l,r+1) to[(u+w)%p][ty^1].emplace_back(u,ty);
        queue<pair<int,int>> q;q.emplace(0,0);vis[0][0]=true;f[0][0]=0;
        while(!q.empty()){
            const auto[u,ty]=q.front();q.pop();
            for(auto&[v,tv]:to[u][ty]){
                if(tv){
                    if(vis[v][tv]) continue;
                    vis[v][tv]=true;
                    f[v][tv]=f[u][ty]+1;
                    q.emplace(v,tv);
                }else{
                    if(vis[v][tv]) continue;
                    f[v][tv]=max(f[v][tv],f[u][ty]+1);
                    if(!(--in[v][tv])){
                        vis[v][tv]=true;
                        q.emplace(v,tv);
                    }
                }
            }
        }
        cir(i,0,p) cir(op,0,2) clog<<i<<' '<<op<<": "<<f[i][op]<<'\n';
        ouf<<(vis[x][op]?f[x][op]:-1)<<'\n';
    }();
    return 0;
}
