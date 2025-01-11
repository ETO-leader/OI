#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
constexpr auto factors(auto x){
    multiset<int> res;
    for(auto i=2;i*i<x+1;++i) while(!(x%i)) res.emplace(i),x/=i;
    if(x>1) res.emplace(x);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    const auto T=50;
    multiset<int> cur;
    map<multiset<int>,int> lable;
    cir(i,1,T){
        const auto f=factors(i);
        for(auto&i:f) cur.emplace(i);
        auto acur=cur;
        auto cnt=0;
        if(i>1) while(!acur.empty()){
            acur.erase(acur.begin());
            if(++cnt;lable.count(acur)){
                clog<<i<<'!'<<' '<<lable[acur]<<'!'<<' '<<cnt<<'\n';
                break;
            }
        }
        lable[cur]=i;
    }
    return 0;
}
