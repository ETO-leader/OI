#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
typedef long long lint;
const int MOD=998244353;
const int MM=107,NN=37;
lint D[MM][NN][NN][NN],C[NN][NN];
void init(){
    cir(i,0,NN){
        C[i][0]=1;
        cir(j,1,i+1) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
    }
}
lint qpow(lint a,lint b){
    lint ret=1;
    while(b){
        if(b&1) (ret*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return ret;
}
int N,M,K;vector<lint> v;
lint dfs(int u,int k,int x,int y){
    auto&d=D[u][k][x][y];
    if(u==M+1) return d=(!k)&&(__builtin_popcount(x)+y<=K);
    if(d>-1) return d;d=0;
    cir(i,0,k+1){
        (d+=dfs(u+1,k-i,(x+i)/2,((x+i)&1)+y)*C[k][i]%MOD*qpow(v[u],i))%=MOD;
    }
    return d;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>N>>M>>K;v.resize(M+1);init();
    for(auto&i:v) cin>>i;
    memset(D,-1,sizeof(D));
    cout<<dfs(0,N,0,0)<<endl;
	return 0;
}