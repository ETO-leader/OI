#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
void regetid(VI&a,VI&b){
    unordered_map<int,int> cpx;
    cir(i,0,a.size()) cpx[a[i]]=i;
    cir(i,0,a.size()) b[i]=cpx[b[i]];
    iota(a.begin(),a.end(),0);
}
void swap_e(VI&v,stringstream&iostr,int&cnx,int p){
    const int vp=v[p],px=p;
    if(v[p]==p) return;
    for(int i=px;i>=vp;--i){
        if(v[i]<p) continue;
        iostr<<i+1<<' '<<p+1<<'\n';
        swap(v[i],v[p]);p=i;++cnx;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI va(n),vb(n);
    for(auto&i:vb) cin>>i;
    for(auto&i:va) cin>>i;
    regetid(va,vb);
    cout<<[&](){
        int res=0;
        cir(i,0,n) res+=abs(vb[i]-i);
        return res/2;
    }()<<'\n';
    stringstream ans;int cnx=0;
    cir(i,0,n) cir(j,0,n)
        if(vb[j]==i) swap_e(vb,ans,cnx,j);
    cout<<cnx<<'\n'<<ans.str();
    return 0;
}
