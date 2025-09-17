#include<bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define mid ((l+r)>>1)
using namespace std;
bool mtd;
const int N=2e5+5;
const int CL=10;
int f[N],cl[N],tot;
vector<int>G[N];
int tp,lst,n,m,k,ans;
void dfs1(int u,int c){
    cl[u]=c;
    c++;
    if(c==k+1)c=1;
    for(auto v:G[u])dfs1(v,c);
}
void dfs2(int u,int c){
    ans+=(cl[u]==c);
    for(auto v:G[u])dfs2(v,c);
}
bool mtt;
signed main(){
    freopen("grandiloquence.in","r",stdin);
    freopen("grandiloquence.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int stt=clock();
    cin>>tp;
    cin>>n>>m>>k;
    tot=n;
    for(int i=1;i<=n;i++)cin>>f[i],G[f[i]].pb(i);
    while(m--){
        int op,u,c;cin>>op>>u;
        if(tp)u^=lst;
        if(op==1){
            cin>>c;
            if(tp)c^=lst;
            dfs1(u,c);
        }else if(op==2){
            cin>>c;
            if(tp)c^=lst;
            ans=0;
            dfs2(u,c);
            cout<<ans<<'\n';
            lst=ans;
        }else{
            G[u].pb(++tot);
        }
    }
	cerr<<'\n'<<fixed<<setprecision(3)<<"memory:"<<(&mtd-&mtt)/1024./1024<<"MB\n";
	cerr<<"time:"<<1.*(clock()-stt)/CLOCKS_PER_SEC<<"s";
	return 0;
}
/*
0
10 8 3
0 1 2 3 4 5 6 7 8 9
1 2 3
1 5 2
2 3 1
2 1 2
3 4
3 7
1 2 1
2 1 3
*/