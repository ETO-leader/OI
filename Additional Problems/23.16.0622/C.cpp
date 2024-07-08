#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<int> v,vcp;
void print(int l,int r){
    reverse(v.begin()+l,v.begin()+r+1);
    for(auto&i:v) cout<<i<<' ';
    cout<<'\n';
    exit(0);
}
int reversesum(int l){
    return (v.size()-l)*(v.size()-l-1)/2;
}
void ansv(int l,int k){
    if(l>=v.size()-1) print(0,0);
    int grtcnt=0,lsscnt=0;
    cir(i,l,v.size())
        grtcnt+=(v[i]>v[l]),lsscnt+=(v[i]<v[l]);
    if(lsscnt>=k||lsscnt+reversesum(l)+l+1<k){
        sort(vcp.begin()+l+1,vcp.end());
        if(k>lsscnt+reversesum(l)) k-=(reversesum(l)+l+1);
        cir(i,l+1,v.size()) if(v[i]==vcp[l+k])
            print(l,i);
    }
    ansv(l+1,k-lsscnt);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;v.resize(n);
    for(auto&i:v) cin>>i;
    vcp=v;ansv(0,k);
    abort();
    return 0;
}