#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> deg;
    vector<vector<lint>> w;
    vector<tuple<int,int,int>> es;
public:
    auto emplace(int u,int v,int w){
        ++deg[u];++deg[v];
        es.emplace_back(u,v,w);
    }
    auto circlesum(vector<int> mu,vector<__gnu_pbds::gp_hash_table<int,int>> lc,vector<int> lim){
        const auto n=(int)(gr.size());
        auto ans=0ll;
        for(auto&[u,v,w]:es){
            if(deg[u]>deg[v]||(deg[u]==deg[v]&&u>v)) swap(u,v);
            gr[u].emplace_back(v,w);
        }
        vector<int> las(n);
        cir(u,0,n){
            for(auto&[v,w]:gr[u]) las[v]=u;
            for(auto&[v,wuv]:gr[u]) for(auto&[i,wvi]:gr[v]) if(las[i]==u){
                const auto wui=lc[u][i];
                const auto sign=(mu[u]*mu[v]*mu[i]+MOD)%MOD;
                auto uans=0ll;
                if(u==v&&v==i){
                    uans+=w[0][wuv]*w[1][wui]%MOD*w[2][wvi];
                }else if(u==v){
                    uans+=w[0][wuv]*w[1][wui]%MOD*w[2][wvi];
                    uans+=w[0][wui]*w[1][wuv]%MOD*w[2][wvi];
                    uans+=w[0][wui]*w[1][wvi]%MOD*w[2][wuv];
                }else if(u==i){
                    uans+=w[0][wuv]*w[1][wui]%MOD*w[2][wvi];
                    uans+=w[0][wui]*w[1][wuv]%MOD*w[2][wvi];
                    uans+=w[0][wvi]*w[1][wuv]%MOD*w[2][wui];
                }else if(v==i){
                    uans+=w[0][wuv]*w[1][wui]%MOD*w[2][wvi];
                    uans+=w[0][wuv]*w[1][wvi]%MOD*w[2][wui];
                    uans+=w[0][wvi]*w[1][wuv]%MOD*w[2][wui];
                }else{
                    uans+=w[0][wuv]*w[1][wui]%MOD*w[2][wvi];
                    uans+=w[0][wui]*w[1][wuv]%MOD*w[2][wvi];
                    uans+=w[0][wuv]*w[1][wvi]%MOD*w[2][wui];
                    uans+=w[0][wvi]*w[1][wuv]%MOD*w[2][wui];
                    uans+=w[0][wui]*w[1][wvi]%MOD*w[2][wuv];
                    uans+=w[0][wvi]*w[1][wui]%MOD*w[2][wuv];
                }
                ((uans%=MOD)*=sign)%=MOD;
                (ans+=uans)%=MOD;
            }
        }
        return ans;
    }
    auto setw(vector<lint> wx,int u){
        cir(i,0,3) w[i][u]=wx[i];
    }
    graph(int _n):gr(_n),deg(_n),w(3,vector<lint>(_n)){}
};
class mathbase{
public:
    auto init_mu(const int n){
        vector<int> mu(n,1),minp(n);
        iota(minp.begin(),minp.end(),0);
        cir(i,2,n){
            const auto p=minp[i];
            for(int j=i;j<n;j+=i)
                minp[j]=min(minp[j],i);
            if(!((i/p)%p)) mu[i]=0;
            else mu[i]=-mu[i/p];
        }
        return mu;
    }
    auto factors(int x){
        vector<int> res{1,x};
        for(auto i=2;i*i<x+1;++i){
            if(!(x%i)){
                res.emplace_back(i);
                if(i*i<x) res.emplace_back(x/i);
            }
        }
        return res;
    }
    auto getpairs(int lim,vector<int> mu){
        vector<pair<int,int>> res;
        vector<vector<int>> fctrs(1);
        cir(lc,1,lim+1) {
            if(!mu[lc]){
                fctrs.emplace_back();continue;
            }
            const auto fct=factors(lc);
            fctrs.emplace_back(fct);
            for(auto&i:fct) if(mu[i]){
                for(auto&x:fctrs[i]) if(i<x*(lc/i)+1){
                    if((!res.empty())&&(res.back()==make_pair(i,x*(lc/i)))) continue;
                    res.emplace_back(i,x*(lc/i));
                }
            }
        }
        return res;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int a,b,c;cin>>a>>b>>c;
        const auto lim=max({a,b,c})+7;
        const auto mu=math.init_mu(lim);
        auto es=math.getpairs(lim-2,mu);
        graph gr(lim+7);
        vector<__gnu_pbds::gp_hash_table<int,int>> lc(lim+7);
        for(auto&[u,v]:es){
            const auto w=u/__gcd(u,v)*v;
            gr.emplace(u,v,w);
            lc[u][v]=w;
            lc[v][u]=w;
        }
        cir(i,1,lim+5){
            auto aw=0ll,bw=0ll,cw=0ll;
            for(auto x=i;x<lim;x+=i){
                aw+=a/x;bw+=b/x;cw+=c/x;
            }
            gr.setw(vector<lint>{aw,bw,cw},i);
        }
        cout<<gr.circlesum(mu,lc,{a,b,c})<<'\n';
        cout.flush();
    }();
    return 0;
}
