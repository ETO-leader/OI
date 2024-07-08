#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint _inf=1e18+7;
struct attack{lint l,r,c;};
int success(int k,attack x,lint bul,lint&usx){
    if(x.c<=bul) return bul-x.c;
    x.c-=bul;
    if((x.r-x.l)*k<x.c) return -1;
    usx=(!(x.c%k))?(x.c/k):(x.c/k+1);
    return (!(x.c%k))?0:((x.c/k+1)*k-x.c);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    vector<attack> va(n);
    for(auto&[l,r,c]:va) cin>>l>>r>>c;
    VI D(n+1,_inf);D[0]=0;
    lint ans=_inf;
    cir(i,0,n){
        lint bul=k,cnx=0,usx=0;
        cir(j,i+1,n+1){
            if((bul=success(k,va[j-1],bul,usx))<0)
                break;
            cnx+=va[j-1].c;
            if(j&&j<n&&va[j-1].r==va[j].l
                &&usx==va[j-1].r-va[j-1].l) continue;
            D[j]=min(D[j],D[i]+cnx+bul);
            if(j==n) ans=min(ans,D[i]+cnx);
        }
    }
    cout<<(ans==_inf?-1:ans)<<'\n';
    return 0;
}
