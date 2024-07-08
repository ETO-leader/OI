#include<bits/stdc++.h>
using namespace std;
void impossible(){cout<<"-1\n";exit(0);}
void init(vector<int>&v,int&ans,
    int pl,int pr,int vl,int vr){
    if(pl==pr-1){v[pl]=vl;return;}
    int mid=(pl+pr)/2,vmid=(vl+vr)/2;
    if(ans>=2){
        ans-=2;
        init(v,ans,pl,mid,vmid+1,vr);
        init(v,ans,mid,pr,vl,vmid);
    }else{
        iota(v.begin()+pl,v.begin()+pr,vl);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    if((k^1)&1) impossible();
    vector<int> v(n);
    init(v,k,0,n,1,n);
    if(k>1) impossible();
    for(auto&i:v) cout<<i<<' ';
    cout<<'\n';
    return 0;
}