#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("wizard.in");
ofstream fcout("wizard.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lf=long double;
static constexpr auto eps=1e-10l;
static constexpr auto _inflf=1e18l;
auto check(int n,vector<vector<lf>>&w,vector<vector<lf>>&c,lf delta){
    struct fnode{
        lf w;int cnt;
        auto operator<(const fnode&f) const{
            return w<f.w;
        }
    };
    vector f(1<<n,vector<fnode>(n,{_inflf,-1}));
    cir(i,0,n) f[1<<i][i]={0.0l,0};
    cir(s,1,(1<<n)-1) cir(i,0,n) if(s&(1<<i)){
        auto[wx,cnts]=f[s][i];
        cir(nxt,0,n) if(!(s&(1<<nxt))){
            const auto cst=w[i][nxt]+c[i][nxt]*delta;
            fnode ckmn={wx+cst,cnts+c[i][nxt]};
            f[s|(1<<nxt)][nxt]=min(f[s|(1<<nxt)][nxt],ckmn);
        }
    }
    const auto[wx,cnt]=*min_element(f[(1<<n)-1].begin(),f[(1<<n)-1].end());
    return tuple(wx,cnt);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;fcin>>n>>m;
    vector w(n,vector<lf>(n)),c(n,vector<lf>(n));
    for(auto&x:w) for(auto&i:x) fcin>>i;
    for(auto&x:c) for(auto&i:x) fcin>>i;
    // auto l=-1e7l,r=1e7l,ans=-1.0l,ansm=-1.0l;
    // cir(cx,0,60){
    //     const auto mid=(l+r)/2;
    //     const auto[wx,arr,cnt]=check(n,w,c,mid);
    //     cnt<m+1?((r=mid),(ans=wx+cnt*mid),(ansm=mid)):(l=mid);
    // }
    // if(ans<0) exit((cout<<-1<<'\n',0));
    const auto[as,cx]=(check(n,w,c,0));
    fcout<<(int)(as)<<'\n';
    return 0;
}
