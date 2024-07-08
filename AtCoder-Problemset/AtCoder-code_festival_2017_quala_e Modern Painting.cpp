#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
using VB=vector<bool>;
static constexpr int MOD=998244353;
VI fct;
auto initfct(int n){
    fct.push_back(1);
    cir(i,1,n+1)
        fct.push_back(fct.back()*i%MOD);
    return fct;
}
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
lint inv(lint x){return qpow(x,MOD-2);}
lint C(lint a,lint b){
    return fct[a]*inv(fct[b])%MOD*
        inv(fct[a-b])%MOD;
}
auto dir_3(int x,int alx){
    if((!x)||(!alx)) return (lint)(1);
    return C(x+alx-1,x-1);
}
auto solve(VB lf,VB rg,VB up,VB dw){
    if(!count(rg.begin(),rg.end(),true)){
        swap(lf,rg);
        reverse(up.begin(),up.end());
        reverse(dw.begin(),dw.end());
    }
    const int n=up.size();
    const auto cl=count(
        lf.begin(),lf.end(),true);
    const auto cr=count(
        rg.begin(),rg.end(),true);
    VI ok;
    cir(i,0,n) if(up[i]||dw[i])
        ok.push_back(i);
    const int oks=ok.size();
    if(!oks) return (lint)(0);
    if((!cl)&&(!cr)) return [&](){
        lint res=1;
        cir(i,0,n) if(up[i]&&dw[i])
            (res*=2)%=MOD;
        return res;
    }();
    VI lfa(oks),rga(oks);
    const auto sum=accumulate(
        up.begin(),up.end(),0)+
        accumulate(dw.begin(),
        dw.end(),0);
    int cx=0;
    cir(i,0,oks){
        lfa[i]=dir_3(cl,cx);
        rga[i]=dir_3(cr,sum-(
            (cx+=up[ok[i]])+=dw[ok[i]]));
    }
    lint res=0,cnx=0;
    if(!cl) return [&](){
        cnx=1;
        cir(i,0,oks){
            if(up[ok[i]]&&dw[ok[i]])
                (cnx*=2)%=MOD;
            (res+=rga[i]*cnx)%=MOD;
        }
        return res;
    }();
    cir(i,0,oks){
        cnx+=lfa[i];
        if(up[ok[i]]&&dw[ok[i]]) cnx*=2;
        (cnx%=MOD);
        (res+=cnx*rga[i])%=MOD;
    }
    return res;
}
bool readvb(VB&a,int len){
    bool res=false;
    cir(i,0,len){
        char x;cin>>x;
        res|=(a[i]=(bool)(x-'0'));
    }
    return res;
}
void diffprs(){exit((cout<<1<<'\n',0));}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;initfct((n+m)*2);
    VB up(n),dw(n),lf(m),rg(m);
    if(!(readvb(up,n)|readvb(dw,n)|
        readvb(lf,m)|readvb(rg,m))){
        diffprs();
    }
    cout<<(solve(lf,rg,up,dw)+
        solve(up,dw,lf,rg))%MOD<<'\n';
    return 0;
}
