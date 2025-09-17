#pragma GCC optimize("O2","O3")
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int n,a1,a2,maxdep;
int zd[200010],cd[200010];
int father[200010];
vector<int>g[200010];
int dep[200010];
int jc[110],ny[110];
int ch[110],c,T;
int f[110][110][110];
void dfs(int x,int fa){
    dep[x]=dep[fa]+1;
    if(dep[x]>dep[maxdep]) maxdep=x;
    father[x]=fa;
    zd[x]=dep[x];
    for(int y:g[x]){
        if(y==fa) continue;
        dfs(y,x);
        if(zd[y]>zd[x]){
            cd[x]=zd[x];
            zd[x]=zd[y];
        }else if(zd[y]>cd[x]){
            cd[x]=zd[y];
        }
        // if(cd[y]>zd[x]){
        //     cd[x]=zd[x];
        //     zd[x]=cd[y];
        // }else if(cd[y]>cd[x]){
        //     cd[x]=cd[y];
        // }
    }
}
int pp(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return res;
}
void init(){
    jc[0]=ny[0]=1;
    for(int i=1;i<=105;i++){
        jc[i]=jc[i-1]*i%mod;
        ny[i]=ny[i-1]*pp(i,mod-2)%mod;
    }
}
int C(int x,int y){
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
signed main(){
    freopen("recall.in","r",stdin);
    freopen("recall.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    init();
    cin>>c>>T;
    while(T--){
        //cout<<T<<endl;
        cin>>n;
        maxdep=0;
        for(int i=1;i<n;i++){
            cin>>a1>>a2;
            g[a1].push_back(a2);
            g[a2].push_back(a1);
        }
        dfs(1,0);
        int now=maxdep;
        while(now!=0){
            ch[dep[now]]=now;
            now=father[now];
        }
        int len=dep[maxdep];
        for(int i=1;i<=len;i++){
            for(int j=0;j<=len;j++){
                f[i][i][j]=1;
            }
        }
        for(int i=1;i<=len;i++){
            for(int j=1;j<=len-i+1;j++){
                for(int k=0;k<=len-i;k++){
                    f[j][j+i][k]=f[j][j+i-1][k+1];
                    int maxx=0;
                    for(int x=j+1;x<j+i;x++){
                        maxx=max(maxx,cd[ch[x-1]]);
                        if(maxx-dep[ch[x]]+1<=k){
                            f[j][j+i][k]=(f[j][j+i][k]+f[j][x][k]*f[x][j+i-1][k+1]%mod*C(i-1,x-j)%mod)%mod;
                        }
                    }
                }
            }
        }
        cout<<len<<" "<<f[1][len+1][0]<<'\n';
        for(int i=1;i<=n;i++){
            g[i].clear();
            zd[i]=cd[i]=0;
            father[i]=0;
        }
        for(int i=0;i<=len;i++){
            ch[i]=0;
        }
        for(int i=0;i<=len;i++){
            for(int j=1;j<=len-i+1;j++){
                for(int k=0;k<=len-i;k++){
                    f[j][j+i][k]=0;
                }
            }
        }
    }
}