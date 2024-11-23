#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class interactor{
public:
    auto getcase(){
        int T;cin>>T;
        return T;
    }
    auto getusers(){
        int n;cin>>n;
        return n;
    }
    auto ask(int u,int v){
        println(cout,"? {} {}",u,v);
        cout.flush();
        int x;cin>>x;
        return x;
    }
    auto answer(int x){
        println(cout,"! {}",x);
        cout.flush();
    }
} interact;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        map<pair<int,int>,int> asked;
        auto optimize_ask=[&](int x,int y){
            if(asked.contains({x,y})) return asked[{x,y}];
            return asked[{x,y}]=interact.ask(x,y);
        };
        if(n&1){
            if(n==3){
                for(auto i=0;i+1<n;i+=2){
                    const auto x=interact.ask(i+1,i+2);
                    const auto y=interact.ask(i+2,i+1);
                    if(x!=y){
                        const auto u=interact.ask(i+1,n);
                        const auto v=interact.ask(n,i+1);
                        if(u!=v) return interact.answer(i+1);
                        return interact.answer(i+2);
                    }
                }
                interact.answer(n);
            }else{
                auto qx=multiset{
                    optimize_ask(1,2),
                    optimize_ask(2,3),
                    optimize_ask(3,1)
                };
                if(qx.count(0)==1||qx.count(0)==3){
                    const auto x=optimize_ask(1,2);
                    const auto y=optimize_ask(2,1);
                    if(x==y) return interact.answer(3);
                    const auto u=optimize_ask(1,3);
                    const auto v=optimize_ask(3,1);
                    if(u!=v) return interact.answer(1);
                    return interact.answer(2);
                }
                for(auto i=3;i+2<n;i+=2){
                    const auto x=interact.ask(i+1,i+2);
                    const auto y=interact.ask(i+2,i+1);
                    if(x!=y){
                        const auto u=interact.ask(i+1,n);
                        const auto v=interact.ask(n,i+1);
                        if(u!=v) return interact.answer(i+1);
                        return interact.answer(i+2);
                    }
                }
                const auto u=interact.ask(1,n);
                const auto v=interact.ask(n,1);
                if(u!=v) interact.answer(n);
                else interact.answer(n-1);
            }
        }else{
            for(auto i=0;i+2<n;i+=2){
                const auto x=interact.ask(i+1,i+2);
                const auto y=interact.ask(i+2,i+1);
                if(x!=y){
                    const auto u=interact.ask(i+1,n);
                    const auto v=interact.ask(n,i+1);
                    if(u!=v) return interact.answer(i+1);
                    return interact.answer(i+2);
                }
            }
            const auto u=interact.ask(1,n);
            const auto v=interact.ask(n,1);
            if(u!=v) interact.answer(n);
            else interact.answer(n-1);
        }
    }();
    return 0;
}
