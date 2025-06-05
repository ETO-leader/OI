#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n;int k,q;cin>>n>>k>>q;
    cir(i,0,q){
        lint u,v;cin>>u>>v;
        if(k==1){
            cout<<abs(u-v)<<'\n';
        }else{
            vector<lint> pw;
            auto cur=(__int128_t)(1);
            pw.emplace_back(1);
            auto pos=1ll;
            while(pos<n+1) pw.emplace_back(pos),pos+=cur,cur*=k;
            auto father=[&](lint u){
                const auto x=prev(upper_bound(pw.begin(),pw.end(),u))-pw.begin();
                const auto ord=(u-pw[x])/k;
                return pw[x-1]+ord;
            };
            vector<lint> a,b;
            while(u>1) a.emplace_back(u),u=father(u);
            while(v>1) b.emplace_back(v),v=father(v);
            while((!a.empty())&&(!b.empty())&&a.back()==b.back()){
                a.pop_back();
                b.pop_back();
            }
            cout<<a.size()+b.size()<<'\n';
        }
    }
    return 0;
}
