#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
struct qry{
    int a,b,c;bool isq,q,qx;
};
vector<qry> vx,vxc;
void dac1(int l,int r,VI&D){
    int ans=0;
    cir(i,l,r+1){
        if(vxc[i].isq&&vxc[i].q&&vxc[i].qx)
            D[vxc[i].a]=max(D[vxc[i].a],ans+1);
        if(!(vxc[i].isq||vxc[i].qx||vxc[i].q))
            ans=max(ans,D[vxc[i].a-1]);
    }
}
void dac2(int l,int r,VI&D){
    if(l==r) return;
    const int mid=(l+r)/2;
    dac2(l,mid,D);dac2(mid+1,r,D);
    cir(i,l,mid+1) vxc[i].qx=0;
    cir(i,mid+1,r+1) vxc[i].qx=1;
    vector<qry> rlt(r-l+1);
    merge(vxc.begin()+l,vxc.begin()+mid+1,
        vxc.begin()+mid+1,vxc.begin()+r+1,
        rlt.begin(),[&](qry&i,qry&j){
        return i.c==j.c?(!i.isq):i.c<j.c;
    });
    cir(i,l,r+1) vxc[i]=rlt[i-l];
    dac1(l,r,D);
}
void dac3(int l,int r,VI&D){
    if(l==r) return;
    const int mid=(l+r)/2;
    dac3(l,mid,D);
    cir(i,l,mid+1) vx[i].q=0,vx[i].qx=0;
    cir(i,mid+1,r+1) vx[i].q=1,vx[i].qx=1;
    vxc=vector<qry>(vx.begin()+l,vx.begin()+r+1);
    sort(vxc.begin(),vxc.end(),[&](qry&i,qry&j){
        return i.b==j.b?(!i.isq):i.b<j.b;
    });
    dac2(0,r-l,D);
    dac3(mid+1,r,D);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;VI v(n),D(n,1);
    for(auto&i:v) cin>>i;
    auto mx=v,mn=v;
    cir(i,0,m){
        int x,w;cin>>x>>w;--x;
        mn[x]=min(mn[x],w);mx[x]=max(mx[x],w);
    }
    vx.resize(n<<1);
    cir(i,0,n){
        vx[i<<1]={i,v[i],mn[i],1,0,0};
        vx[i<<1|1]={i+1,mx[i],v[i],0,0,0};
    }
    sort(vx.begin(),vx.end(),[&](qry&i,qry&j){
        return i.a==j.a?(!i.isq):i.a<j.a;
    });
    dac3(0,(n<<1)-1,D);
    cout<<*max_element(D.begin(),D.end())<<'\n';
    return 0;
}
