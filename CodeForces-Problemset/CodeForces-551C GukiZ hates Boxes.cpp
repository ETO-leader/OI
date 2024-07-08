#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
bool chk(lint x,lint m,vector<lint> v){
    int pos=0;
    cir(i,0,m){
        lint xi=x;xi-=pos;
        while(pos<v.size()&&v[pos]<=xi)
            xi-=(v[pos]+1),++pos;
        if(pos==v.size()) return true;
        if(xi>0) v[pos]-=xi;
    }
    return false;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<lint> v(n);
    for(auto&i:v) cin>>i;
    v.insert(v.begin(),0);
    while(!v.empty()&&!v.back()) v.pop_back();
    lint l=0,r=accumulate(v.begin(),
        v.end(),0LL)+n,ans=-1;
    while(r>=l){
        lint mid=(l+r)/2;
        chk(mid,m,v)?ans=mid,r=mid-1:l=mid+1;
    }
    cout<<ans<<'\n';
    return 0;
}
