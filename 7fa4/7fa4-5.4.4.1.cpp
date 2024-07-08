#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
array<array<array<array<
    array<lint,2>,2>,2>,2>,64> D;
lint dfs(int p,bool dwa,bool upa,bool dwb,bool upb,
    lint t,lint lx,lint rx,lint ly,lint ry){
    if(!(~p)) return 1;
    auto&d=D[p][dwa][upa][dwb][upb];
    if(d) return d;
    const int mna=dwa?0:((lx>>p)&1);
    const int mxa=upa?1:((rx>>p)&1);
    const int mnb=dwb?0:((ly>>p)&1);
    const int mxb=upb?1:((ry>>p)&1);
    lint a1=0,a2=0;
    cir(i,mna,mxa+1) cir(j,mnb,mxb+1){
        if((i|j)!=((t>>p)&1)) continue;
        const bool ndwa=dwa||(i>mna);
        const bool nupa=upa||(i<mxa);
        const bool ndwb=dwb||(j>mnb);
        const bool nupb=upb||(j<mxb);
        if(i&&j) a2=dfs(p-1,ndwa,nupa,ndwb,nupb,
            t,lx,rx,ly,ry);
        else a1=max(a1,dfs(p-1,ndwa,nupa,ndwb,nupb,
            t,lx,rx,ly,ry));
    }
    return d=a1+a2;
}
lint slv(lint t,lint lx,lint rx,lint ly,lint ry){
    return dfs(62,false,false,false,false,
        t,lx,rx,ly,ry);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint t,lx,rx,ly,ry;cin>>t>>lx>>rx>>ly>>ry;
    cout<<slv(t,lx,rx,ly,ry)<<'\n';
    return 0;
}
