#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
auto runx(lint w){
    vector<lint> res(1,1);
    for(lint i=2;i*i<=w;++i){
        if(!(w%i)) res.push_back(i);
    }
    const int sz=res.size();
    cir(i,0,sz) if(w/res[i]!=res[i])
        res.push_back(w/res[i]);
    return res;
}
const lint _inf=1e15+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    sort(a.begin(),a.end());
    auto all=accumulate(a.begin(),a.end(),0LL);
    auto num=runx(all);
    sort(num.begin(),num.end(),greater<lint>());
    for(auto&i:num){
        if([&num,&k,&a,&n](lint w){
            vector<lint> md;
            for(auto&i:a) md.push_back(i%w);
            sort(md.begin(),md.end());
            lint cnx=0,l=0,r=n-1;
            while(r>l){
                auto mn=min(md[l],w-md[r]);
                ((md[l]-=mn))%=w;(md[r]+=mn)%=w;
                cnx+=mn;
                while(l<=r&&(!md[l])) ++l;
                while(l<=r&&(!md[r])) --r;
            }
            return cnx<=k;
        }(i)){
            cout<<i<<'\n';
            break;
        }
    }
    return 0;
}
