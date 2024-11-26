#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class interactor{
public:
    static auto init(){
        int n,m;cin>>n>>m;
        return pair(n,m);
    }
    static auto cheat(){
        string s;cin>>s;
        return s;
    }
    static auto choose(const int w){
        println(cout,"{}",w);
        cout.flush();
        int ans;cin>>ans;
        return ans;
    }
} interact;
class randomengine{
private:
    mt19937_64 eng;
public:
    template<typename _Ty>
    auto randreal(auto l,auto r){
        return uniform_real_distribution<_Ty>(l,r)(eng);
    }
    randomengine():eng(random_device().operator()()){}
} rnd;
using lf=long double;
static constexpr auto alpha=0.8l;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    const auto[n,m]=interact.init();
    vector rl(n,1.0l);
    cir(i,0,m){
        const auto s=interact.cheat();
        auto cntf=0.0l,cntt=0.0l;
        cir(i,0,n) (s[i]=='0'?cntf:cntt)+=rl[i];
        const auto ans=interact.choose(rnd.randreal<lf>(0.0l,cntf+cntt)>cntf);
        cir(i,0,n) if(s[i]!=ans+'0') rl[i]*=alpha;
    }
    return 0;
}
