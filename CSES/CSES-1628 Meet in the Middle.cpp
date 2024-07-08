#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define vit vector<lint>::iterator
using namespace std;
using lint=long long;
using Map=unordered_map<lint,lint>;
void subseting(vit begin,vit end,Map&res,lint mx){
    vector<lint> v;
    for(;begin!=end;++begin) v.push_back(*begin);
    const int _sz=1<<v.size();
    cir(i,0,_sz){
        lint cnt=0;
        cir(j,0,v.size()) if(i&(1<<j))
            cnt+=v[j];
        if(cnt<=mx) res[cnt]++;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,k;cin>>n>>k;vector<lint> v(n);
    for(auto&i:v) cin>>i;
    if(n==1){cout<<(v[0]==k)<<'\n';exit(0);}
    Map M1,M2;
    subseting(v.begin(),v.begin()+n/2,M1,k);
    subseting(v.begin()+n/2,v.end(),M2,k);
    lint ans=0;
    for(auto&i:M1){
        if(!M2.count(k-i.first)) continue;
        ans+=i.second*M2[k-i.first];
    }
    cout<<ans<<'\n';
    return 0;
}