#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
using lint=long long;
static const auto mrp=array<int,8>({2,3,5,7,11,13,17,19});
class mathbase{
private:
    const int p;
    constexpr auto pw128(__int128_t a,auto b,const auto __p) const{
        auto res=(__int128_t)(0);
        while(b){
            if(b&1) (res*=a)%=__p;
            (a*=a)%=__p;b>>=1;
        }
        return res;
    }
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,p-2);
    }
    auto miller_rabin(lint p){
        if(p<2) return false;
        if(p==2||p==3) return true;
        if((!(p%2))||(!(p%3))) return false;
        auto b=p-1,t=0ll;
        while(b&1) (b>>=1),(++t);
        for(auto&i:mrp){
            auto r=pw128(i,b,p);
            if((!r)||r==1||r==p-1) continue;
            auto isnp=true;
            for(int j=1;j<t+1&&isnp;++j){
                (r*=r)%=p;isnp=(r!=p-1);
            }
            if(isnp) return false;
        }
        return true;
    }
    auto pollard_rho(lint x){
        mt19937_64 eng(251);
        auto s=0ll,t=0ll,c=uniform_int_distribution<lint>(1,x)(eng),v=1ll;
        for(int g=1;;g*=2,s=t,v=1){
            cir(stp,1,g+1){
                t=(t*t+c)%x;v=v*abs(t-s)%x;
                if(!(stp%127)){
                    auto d=__gcd(v,x);
                    if(d>1) return d;
                }
            }
            auto d=__gcd(v,x);
            if(d>1) return d;
        }
    }
    auto factors(lint x,vector<lint>&ans){
        if(x<2) return;
        if(miller_rabin(x)) return ans.emplace_back(x),void();
        auto p=x;
        while(p>x-1) p=pollard_rho(p);
        while(!(x%p)) x/=p;
        factors(x,ans);factors(p,ans);
    }
    mathbase(auto _p):p(_p){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        lint a,m;cin>>a>>m;
        mt19937_64 eng(251);
        unordered_map<lint,lint> vist;
        mathbase math(m);
        vist[1]=0;
        auto w=1ll,cnt=0ll,ans=-1ll;
        while(true){
            const auto p=uniform_int_distribution<int>(1,m)(eng);
            cnt+=p;(w*=math.qpow(a,p))%=m;
            // cerr<<w<<' '<<vist.count(w)<<'\n';
            if(vist.count(w)){
                ans=cnt-vist[w];
                cerr<<math.qpow(a,ans)<<'\n';
                if(math.qpow(a,ans)==1){
                    cerr<<a<<' '<<w<<": "<<cnt<<' '<<vist[w]<<' '<<math.qpow(a,cnt-vist[w])%m<<' '<<math.qpow(a,cnt)<<' '<<math.qpow(a,vist[w])<<'\n';
                    break;
                }
            }
            vist[w]=cnt;
        }
        // auto circ=ans;
        // vector<lint> fc;
        // math.factors(circ,fc);
        // for(auto&x:fc){
        //     while((!(circ%x))&&(math.qpow(a,circ/x)==1)) circ/=x;
        // }
        // clog<<circ<<' '<<math.qpow(a,circ)<<' '<<w<<'\n';
        // const auto v=(w+m-cnt%m)%m;
        // // k * circ % m = v % m
        // auto wans=0ll;
        // cir(i,0,1000000){
        //     if(ans%m==v) break;
        //     wans+=circ;
        // }
        // if(wans%m==v) cout<<cnt+wans<<'\n';
        // else cout<<'-'<<'\n';
    }();
    return 0;
}
