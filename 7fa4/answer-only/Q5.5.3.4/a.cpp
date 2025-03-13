#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#define THREADS_COUNT 20
class random_engine{
private:
    mt19937 eng;
public:
    template<typename _Ty>
    auto randint(auto l,auto r){
        return uniform_int_distribution<_Ty>(l,r)(eng);
    }
    auto random(){
        return uniform_real_distribution<double>(0,1)(eng);
    }
    random_engine():
        eng(
            // '251Sec'
            random_device().operator()()
        ){}
} rnd;
const auto P=0.9999995;
constexpr auto inrange(int x,int l,int r){
    return l-1<x&&x-1<r;
}
vector<vector<int>> elem_counts;
vector<int> statu,cnt;
int ans;
atomic_bool locked;
atomic_int in_SA;
double T=1.0;
auto SA=[](int n,int m,int p,int l,int u,int id){
    // cerr<<"In "<<id<<'\n';
    while(locked);
    ++in_SA;
    locked=true;
    auto input_statu=statu;
    auto __cnt=cnt;
    auto __ans=ans;
    locked=false;
    cir(i,0,200000){
        if(!(i%50000)){
            // cerr<<format("ans = {}, T = {}, cur = {}\n",ans,T,__ans);
            stringstream qwq;
            qwq<<"ans = "<<ans<<", T = "<<T<<", cur = "<<__ans<<" (Thread: "<<id<<")"<<'\n';
            cerr<<qwq.str();
        }
        const auto lasans=__ans;
        const auto lascnt=__cnt;
        const auto lassta=input_statu;
        auto x=rnd.randint<int>(0,n-1);
        while(input_statu[x]) x=rnd.randint<int>(0,n-1);
        input_statu[x]^=1;
        for(auto&u:elem_counts[x]) ++__cnt[u];
        x=rnd.randint<int>(0,n-1);
        while(!input_statu[x]) x=rnd.randint<int>(0,n-1);
        input_statu[x]^=1;
        for(auto&u:elem_counts[x]) --__cnt[u];
        __ans=0;
        cir(i,0,n) __ans+=inrange(__cnt[i],l,u);
        if(__ans>ans){
            T=1;
            while(locked);
            locked=true;
            if(__ans>ans){
                ans=__ans;
                statu=input_statu;
                cnt=__cnt;
            }
            locked=false;
        }else if(!(rnd.random()<exp(-((ans-__ans)/T)))){
            __ans=lasans;
            __cnt=lascnt;
            input_statu=lassta;
        }
        if(T<1e-3) T=1;
        if(rnd.random()<1.0/THREADS_COUNT) T*=P;
    }
    --in_SA;
    // cerr<<"End Thread #"<<id<<" ans = "<<ans<<" cur = "<<__ans<<" T = "<<T<<'\n';
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,p,l,u;cin>>n>>m>>p>>l>>u;
    elem_counts.resize(n);
    cir(i,0,n){
        cir(c,0,p){
            int x;cin>>x;--x;
            elem_counts[x].emplace_back(i);
        }
    }
    statu.resize(n);
    cnt.resize(n);
    cir(i,0,m){
        // cerr<<i<<' '<<u<<'\n';
        statu[i]=true;
        for(auto&u:elem_counts[i]){
            if(inrange(cnt[u],l,u)) --ans;
            ans+=inrange((++cnt[u]),l,u);
        }
    }
    while(true){
        cir(i,0,THREADS_COUNT){
            try{
                thread x(SA,n,m,p,l,u,i);
                x.detach();
            }catch(system_error&){}
        }
        while(in_SA);
        ofstream ouf("ouf");
        ouf<<ans<<'\n';
        cir(i,0,n) if(statu[i]) ouf<<i+1<<' ';
        ouf<<'\n'<<flush;
        ouf.close();
    }
    return 0;
}
