#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("a.in");
ofstream ouf("a.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
class floyd{
private:
    vector<vector<lint>> f,*dis;
public:
    auto append(int u){
        const auto n=(int)(f.size());
        cir(s,0,n) cir(i,0,n) if((*dis)[i][u]>-1){
            f[s][u]=min(f[s][u],f[s][i]+(*dis)[i][u]);
        }
        cir(s,0,n) cir(i,0,n){
            f[s][i]=min(f[s][i],f[s][u]+f[u][i]);
        }
    }
    auto dist(int u,int v){
        return f[u][v]==_infl?-1:f[u][v];
    }
    floyd(int _n,auto d):f(_n,vector<lint>(_n,_infl)),dis(d){
        cir(i,0,_n) f[i][i]=0;
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;vector<vector<lint>> a(n,vector<lint>(n));
    for(auto&x:a) for(auto&i:x) inf>>i;
    floyd grx(n,&a);
    cir(i,0,n) grx.append(i);
    auto ans=0ll;
    cir(i,0,n) cir(j,0,n) ans+=grx.dist(i,j)*2;
    auto divide=[&](auto __self,int l,int r,floyd gr)->lint {
        if(l==r){
            auto res=0ll;
            cir(u,0,n) cir(v,0,n) if(u!=l&&v!=l) res+=gr.dist(u,v);
            return res;
        }
        const auto mid=(l+r)/2;
        auto grl=gr,grr=gr;
        cir(i,l,mid+1) grr.append(i);
        cir(i,mid+1,r+1) grl.append(i);
        return __self(__self,l,mid,grl)+__self(__self,mid+1,r,grr);
    };
    ouf<<ans+divide(divide,0,n-1,floyd(n,&a))<<'\n';
    return 0;
}
