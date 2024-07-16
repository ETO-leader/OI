#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class bitdp{
private:
    vector<array<array<array<array<lint,2>,2>,2>,2>> f,vis;
    static constexpr auto mxwx=63;
    auto dfs(int p,lint lima,lint limb,bool lmda=true,bool lmdb=true,bool atr=false,bool btr=false){
        if(p<0) return (lint)(atr&&btr);
        const auto mxpa=lmda?(int)((lima>>p)&1):1;
        const auto mxpb=lmdb?(int)((limb>>p)&1):1;
        auto&fx=f[p][lmda][lmdb][atr][btr];
        if(vis[p][lmda][lmdb][atr][btr]) return fx;
        vis[p][lmda][lmdb][atr][btr]=true;
        cir(i,0,mxpa+1) cir(j,0,min(i,mxpb)+1){
            if((!atr)&&(!btr)&&(i!=j)) continue;
            (fx+=dfs(p-1,lima,limb,lmda&&(i==mxpa),lmdb&&(j==mxpb),atr||i,btr||j))%=MOD;
        }
        return fx;
    }
public:
    auto check(lint lima,lint limb){
        return dfs(mxwx,lima,limb);
    }
    bitdp():f(mxwx+1),vis(mxwx+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint l,r;cin>>l>>r;
    cout<<(
        bitdp().check(r,r)+
        MOD-bitdp().check(r,l-1)+
        MOD-bitdp().check(l-1,r)+
        bitdp().check(l-1,l-1)
    )%MOD<<'\n';
    return 0;
}
