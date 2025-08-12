#include<bits/stdc++.h>
using namespace std;
#define N 4000010
#define LL long long
int T,n,m,tot=0,Mod=1;
int pri[N],mu[N];
LL F[N],C[N];
bool mark[N]={0};
void init(){
    for(int i=1;i<=30;i++)Mod*=2;
    mu[1]=1;
    for(int i=2;i<N;i++){
        if(!mark[i])pri[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&i*pri[j]<N;j++){
            mark[i*pri[j]]=1;
            if(i%pri[j]==0)mu[i*pri[j]]=0;
            else mu[i*pri[j]]=-mu[i];
        }
    }
    for(int i=1;i<N;i++)
        for(int j=1;i*j<N;j++)
            if(mu[j])F[i*j]+=mu[i]*i;
    for(int i=1;i<N;i++)F[i]=(1ll*F[i]*i+F[i-1]+Mod)%Mod;
    for(int i=1;i<N;i++)C[i]=(1ll*(i+1)*i/2)%Mod;
}
int main(){
    init();
    scanf("%d",&T);
    for(int i=1;i<21;++i) clog<<F[i]<<' ';
    clog<<'\n';
    while(T--){
        scanf("%d%d",&n,&m);
        LL ans=0;
        int up=min(n,m);
        for(int i=1,j;i<=up;i=j+1){
            j=min(n/(n/i),m/(m/i));
            ans=(ans+(F[j]-F[i-1])*C[n/i]*C[m/i]%Mod+Mod)%Mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}