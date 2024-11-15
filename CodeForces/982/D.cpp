#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
static constexpr auto _infl=(lint)(1e18l);
class anstype{
private:
    lint w,cnt;
public:
    auto&operator+=(const anstype x){
        if(w>x.w) w=x.w,cnt=0;
        if(w==x.w) (cnt+=x.cnt)%=MOD;
        return*this;
    }
    auto str(){
    #ifndef __EASY_VERSION
        return w==_infl?format("-1"):format("{} {}",w,cnt);
    #else
        return format("{}",w==_infl?-1:w);
    #endif
    }
    auto detail(){return pair(w,cnt);}
    anstype(lint _w=_infl,lint _cnt=0):w(_w),cnt(_cnt){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;vector<lint> a(n),b(m);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        auto pre=a;
        cir(i,1,n) pre[i]+=pre[i-1];
        vector<anstype> f(n+1);
        f[0]=anstype(0,1);
        cir(i,0,m){
            auto l=0;
            map<lint,lint> cnti,acnt;
            cnti[0]=1;++acnt[0];
            cir(r,1,n+1){
                while(pre[r-1]-(l?pre[l-1]:0)>b[i]){
                    const auto[wi,ci]=f[l].detail();
                    cnti[wi]-=ci;--acnt[wi];
                    if(!acnt[wi]) cnti.extract(wi);
                    ++l;
                }
                if(!cnti.empty()){
                    f[r]+=anstype(cnti.begin()->first+(m-1-i),cnti.begin()->second);
                }
                const auto[wi,ci]=f[r].detail();
                cnti[wi]+=ci;++acnt[wi];
            }
        }
        println("{}",f[n].str());
    }();
    return 0;
}
