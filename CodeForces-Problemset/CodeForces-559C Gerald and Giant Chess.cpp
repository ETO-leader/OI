#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint MOD=1e9+7;
vector<lint> inv,frac;
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;(b>>=1);
    }
    return res;
}
lint C(int a,int b){
    return frac[b]*inv[a]%MOD*inv[b-a]%MOD;
}
struct square{int x,y;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    auto cx=[&](){
        vector<lint> res(n+m+1,1),resf(n+m+1,1);
        cir(i,1,n+m+1)
            resf[i]=resf[i-1]*i%MOD,
            res[i]=qpow(resf[i],MOD-2);
        return make_pair(res,resf);
    }();
    inv=cx.first;frac=cx.second;
    vector<square> vs(k);
    for(auto&i:vs) cin>>i.x>>i.y;
    sort(vs.begin(),vs.end(),[](square&a,square&b){
        return a.x==b.x?a.y<b.y:a.x<b.x;});
    vs.push_back({n,m});
    vector<lint> D(k+1);
    cir(i,0,k+1){
        D[i]=C(vs[i].x-1,vs[i].x+vs[i].y-2);
        cir(j,0,i){
            if(vs[j].y>vs[i].y) continue;
            D[i]-=D[j]*C(vs[i].x-vs[j].x,vs[i].x
                +vs[i].y-vs[j].x-vs[j].y)%MOD;
            (D[i]+=MOD)%=MOD;
        }
    }
    cout<<D[k]<<'\n';
    return 0;
}
