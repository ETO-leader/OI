#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto v=(int)(1e5+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int64_t l,r;
    while(cin>>l>>r){
        l+=(l==1);
        vector<int64_t> vis(v),p;
        cir(i,2,v) if(!vis[i]){
            p.emplace_back(i);
            for(auto x=(int64_t)(i)*i;x<v;x+=i) vis[x]=true;
        }
        vector<int> ok(r-l+1,true);
        for(auto&i:p){
            for(auto x=max((l+i-1)/i*i,i*2);x<r+1;x+=i) ok[x-l]=false;
        }
        vector<int> px;
        cir(i,0,r-l+1) if(ok[i]) px.emplace_back(i+l);
        if(px.size()<2){
            cout<<"There are no adjacent primes."<<'\n';
        }else{
            auto mn=make_tuple(numeric_limits<int>::max(),-1,-1);
            auto mx=make_tuple(numeric_limits<int>::min(),1,1);
            cir(i,1,(int)(px.size())){
                mn=min(mn,make_tuple(px[i]-px[i-1],px[i-1],px[i]));
                mx=max(mx,make_tuple(px[i]-px[i-1],-px[i-1],-px[i]));
            }
            cout<<get<1>(mn)<<","<<get<2>(mn)<<" are closest, "<<-get<1>(mx)<<","<<-get<2>(mx)<<" are most distant."<<'\n';
        }
    }
    return 0;
}
