#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;

#ifdef ONLINE_JUDGE

class interaction{
public:
    static auto casenum(){
        int T;cin>>T;
        return T;
    }
    static auto typescount(){
        lint n;cin>>n;
        return n;
    }
    static auto ask(auto l,auto r){
        println(cout,"xor {} {}",l,r);
        cout.flush();
        lint result;cin>>result;
        assert(result!=-1);
        return result;
    }
    static auto answer(auto a,auto b,auto c){
        println(cout,"ans {} {} {}",a,b,c);
        cout.flush();
    }
} interactor;

#else

#include"grader.h"

#endif

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=interactor.casenum();
    while(T--) [&](){
        const auto n=interactor.typescount();
        vector<lint> ans;
        const auto divide=[&](const auto __self,lint l,lint r,lint cur,int byte)->void {
            if(!cur) return;
            if(l==r) return ans.push_back(l);
            const auto mid=midpoint(l,r);
            const auto askl=interactor.ask(l,mid);
            const auto askr=askl==cur?0:(askl?interactor.ask(mid+1,r):cur);
            if(askl&&askr){
                if((askl>>byte)&1) ans.push_back(askl);
                else __self(__self,l,mid,askl,byte);
                if((askr>>byte)&1) ans.push_back(askr);
                else __self(__self,mid+1,r,askr,byte);
            }else{
                __self(__self,l,mid,askl,byte);
                __self(__self,mid+1,r,askr,byte);
            }
        };
        vector<pair<lint,int>> vaild;
        for(auto i=60;~i;--i) if(n>(1ll<<i)-1){
            const auto rng=interactor.ask(1ll<<i,min(2ll<<i,n+1)-1);
            if(rng) vaild.emplace_back(rng,i);
        }
        if(vaild.size()==3){
            for(auto&[a,b]:vaild) ans.push_back(a);
        }else if(vaild.size()==2){
            for(auto&[a,b]:vaild){
                if((a>>b)&1) ans.push_back(a);
                else divide(divide,1ll<<b,min(2ll<<b,n+1)-1,a,b);
            }
        }else{
            for(auto&[a,b]:vaild){
                divide(divide,1ll<<b,min(2ll<<b,n+1)-1,a,b);
            }
        }
        interactor.answer(ans[0],ans[1],ans[2]);
    }();
    return 0;
}
