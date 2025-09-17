#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int NN=998244353;
int n;
vector<int>g[100100];
int ans,dep[100100];
int xu;
int p[100100],ni[100100];
int fa[100100],b[100100],a[100100];
// int f[110][110][110];
pair<int,int>f[110][110][110];
int ff[100100];
int mi(int x,int y){
    int sum=1;
    for (;y;y>>=1,x=x*x%NN)
    if(y&1)sum=sum*x%NN;
    return sum;
}
int c(int x,int y){
    if(x<0||y<0||x<y)return 0;
    return p[x]*ni[y]%NN*ni[x-y]%NN;
}
pair<int,int>add(pair<int,int>x,pair<int,int>y){
    return {x.first+y.first,x.second*y.second%NN};
}
void get(pair<int,int>&x,pair<int,int>y){
    if(x.first>y.first)x=y;
    else if(x.first==y.first)x.second=(x.second+y.second)%NN;
}
void dfs(int x,int pa){
    dep[x]=dep[pa]+1;fa[x]=pa;
    ans=max(ans,dep[x]);
    ff[x]=dep[x];
    if(ans==dep[x])xu=x;
    for (auto y:g[x])
    if(y!=pa)dfs(y,x),ff[x]=max(ff[x],ff[y]);
}
void solve(){
    cin>>n;ans=0;xu=0;
    for (int i=1;i<=n;i++)g[i].clear(),b[i]=0;
    for (int i=1,x,y;i<n;i++)
    cin>>x>>y,g[x].push_back(y),g[y].push_back(x);
    dfs(1,0);cout<<ans<<" ";
    int tot=ans;a[tot]=xu;
    while(tot>1)tot--,xu=fa[xu],a[tot]=xu;
    tot=ans;
    // for (int i=1;i<=tot;i++)cout<<a[i]<<" ";cout<<"!!!!\n";
    for (int i=1;i<tot;i++)
    for (auto j:g[a[i]])
    if(dep[j]>i&&a[i+1]!=j)b[i]=max(b[i],ff[j]);
    // for (int i=1;i<=tot;i++)cout<<b[i]<<" ";cout<<"!!!!\n";
    for (int i=1;i<=ans;i++)
    for (int j=1;j<=ans;j++){
        for (int t=0;t<=ans;t++)
        f[i][j][t]={n+1,0};
        // for (int t=max(0ll,j-i+1);t<=ans;t++)
        // f[i][j][t]={0,1};
    }
    for (int i=1;i<=ans+1;i++){
        f[i][i][0]={1,1},f[i][i-1][0]={0,1};
        for (int j=1;j<=ans;j++)
        f[i][i][j]={1,1},f[i][i-1][j]={0,1};
    }
    
    for (int len=2;len<=ans;len++){
        for (int l=1;l+len-1<=ans;l++){
            int r=l+len-1;
            for (int t=0;t<=ans;t++){
                // if(t>=len){
                //     bool pd=1;
                //     for (int i=l;i<=r;i++)
                //     if(b[i]-l+1>t)pd=0;
                //     if(pd)f[l][r][t]={0,1};
                // }
                int mx=0;
                for (int i=l;i<=r;i++){
                    bool pd=(mx-t<i);
                    // for (int j=l;j<i;j++)
                    // if(b[j]-t>=i)pd=0;
                    // if(b[r]-t>r)pd=0;
                    mx=max(mx,b[i]);
                    if(!pd){continue;}
                    // cout<<add(f[l][i-1],f[i][r-1]).first<<"~~~"<<l<<" "<<r<<" "<<i<<"\n";
                    int t1=f[l][i-1][t].first+f[i][r-1][t+1].first+1;
                    int t2=f[l][i-1][t].second*f[i][r-1][t+1].second%NN*
                    c(f[l][i-1][t].first+f[i][r-1][t+1].first,f[l][i-1][t].first)%NN;
                    get(f[l][r][t],{t1,t2});
                }
            }
            // cout<<l<<"~~"<<r<<" "<<f[l][r].first<<" "<<f[l][r].second<<"\n";
        }
    }
    // cout<<f[1][ans][0].first<<"\n";
    cout<<f[1][ans][0].second<<"\n";
    // for (int i=1;i<=tot;i++)cout<<b[i]<<" ";cout<<"!!!!\n";
    // memset(f,0,sizeof(f));
    // f[0][0][0]=1;
    // int as=0;
    // for (int i=1;i<=ans;i++){
    //     for (int j=0;j<=ans;j++)
    //     for (int k=0;k<=j;k++)
    //     if(f[i-1][j][k]){
    //         cout<<i-1<<"~~~"<<j<<" "<<k<<" "<<f[i-1][j][k]<<"\n";
    //         if(k>=max(1ll,b[i]-i+1)&&k+ans-j>=ans-i+1)add(f[i][j][k],f[i-1][j][k]);
    //         for (int kk=0;kk<=k;kk++)
    //         if(kk+ans-j==ans-i+1&&j-kk>=i-1){
    //             for (int t=1;j+t<=ans;t++)
    //             if(kk+t>=max(1ll,b[i]-i+1)){
    //                 if(kk==k)add(f[i][j+t][kk+t],f[i-1][j][k]*c(j-kk+t,t));
    //                 else add(f[i][j+t][kk+t],f[i-1][j][k]*c(j-kk+t-1,t-1));
    //             }
    //         }
    //     }   
    // } 
    // for (int j=0;j<=ans;j++)cout<<j<<"##"<<f[ans][ans][j]<<"\n",add(as,f[ans][ans][j]);
    // cout<<as<<"\n";
}
signed main(){
    freopen("recall.in","r",stdin);
    freopen("recall.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int id,T;cin>>id>>T;
    p[0]=1;
    int N=100000;
    for (int i=1;i<=N;i++)p[i]=p[i-1]*i%NN;
    ni[N]=mi(p[N],NN-2);
    for (int i=N;i>=1;i--)ni[i-1]=ni[i]*i%NN;
    while(T--)solve();
}