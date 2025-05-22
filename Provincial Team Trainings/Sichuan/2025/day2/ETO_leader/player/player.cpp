#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("player.in");
ofstream ouf("player.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
class tree{
private:
    vector<vector<int>> gr;
    vector<int> fr,vis;
    int cnt;
    void dfs(int u,int f=-1){
        fr[u]=f;
        for(auto&i:gr[u]) if(i!=f) dfs(i,u);
    }
    void jump(int u){
        while(u>-1&&(!vis[u])) vis[u]=true,++cnt,u=fr[u];
    }
public:
    void link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    void init(int _r){dfs(_r);vis[_r]=true;}
    void flush(){
        fill(vis.begin(),vis.end(),false);
        cnt=0;
    }
    int emplace(int u){
        jump(u);
        return cnt;
    }
    tree(int _n):gr(_n),fr(_n),vis(_n),cnt(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int id,n,k;inf>>id>>n>>k;
    vector<int> p(n);
    for(auto&i:p) inf>>i,--i;
    tree gr(n);
    cir(i,0,n-1){
        int u,v;inf>>u>>v;--u;--v;
        gr.link(u,v);
    }
    vector<vector<int>> siz(n,vector<int>(n));
    cir(i,0,n){
        gr.flush();
        gr.init(p[i]);
        cir(j,0,n) siz[i][(i+j)%n]=gr.emplace(p[(i+j)%n]);
    }
    auto check=[&](int s){
        vector<int> f(n);
        cir(i,0,n) f[i]=siz[s][(s+i)%n];
        cir(r,0,k-1){
            const auto g=f;
            fill(f.begin(),f.end(),-_inf);
            auto las=0;
            cir(i,r+1,n){
                cir(p,las,i){
                    const auto nw=g[p]+siz[(s+p+1)%n][(s+i)%n];
                    if(nw>f[i]) f[i]=nw,las=p;
                }
            }
        }
        return f[n-1];
    };
    auto ucheck=[&](int s,lint cost){
        vector<lint> f(n),c(n);
        cir(i,0,n) if(siz[s][(s+i)%n]>-cost) f[i]=siz[s][(s+i)%n]+cost,c[i]=1;
        auto las=0;
        cir(i,0,n){
            auto rpos=min(las+15,i);
            cir(p,las,rpos){
                const auto nw=f[p]+siz[(s+p+1)%n][(s+i)%n]+cost;
                if(nw>f[i]) f[i]=nw,c[i]=c[p]+1,las=p,rpos=min(rpos+15,i);
            }
            assert(f[i]-c[i]*cost>-1);
        }
        return make_pair(f[n-1],c[n-1]);
    };
    if(k==2){
        auto ans=0;
        cir(i,0,n) cir(j,i+1,n) ans=max(ans,siz[i][j-1]+siz[j][(i+n-1)%n]);
        ouf<<ans<<'\n';
    }else if(k<27&&n<705){
        auto ans=0;
        cir(i,0,n) ans=max(ans,check(i));
        ouf<<ans<<'\n';
    }else{
        auto l=-_inf,r=_inf;
        auto ans=0ll;
        const auto chks=[&]{
            const auto sval=0;
            auto maxw=make_pair(-1ll,-1ll);
            cir(s,0,n) maxw=max(maxw,ucheck(s,sval));
            return maxw.second<k;
        }();
        if(chks){
            while(l<r){
                const auto mid=(l+r)/2;
                auto maxw=make_pair(-1ll,-1ll);
                cir(s,0,n) maxw=max(maxw,ucheck(s,mid));
                if(maxw.second<k+1){
                    ans=maxw.first-(lint)(k)*mid;
                    l=mid+1;
                }else{
                    r=mid;
                }
            }
        }else{
            while(l<r){
                const auto mid=(l+r)/2;
                auto maxw=make_pair(-1ll,-1ll);
                cir(s,0,n) maxw=max(maxw,ucheck(s,mid));
                if(maxw.second<k){
                    l=mid;
                }else{
                    ans=maxw.first-(lint)(k)*mid;
                    r=mid-1;
                }
            }
        }
        ouf<<ans<<'\n';
    }
    return 0;
}
