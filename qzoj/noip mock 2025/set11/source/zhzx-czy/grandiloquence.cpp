#include<bits/stdc++.h>
using namespace std;
int col[200200];
vector<int>g[200200];
int fa[200200];
int n,m,k;
void dfs1(int x,int c,int dep){
    col[x]=(dep+c-1)%k+1;
    for (auto y:g[x])
    dfs1(y,c,dep+1);
}
int zong;
void dfs2(int x,int c){
    zong+=col[x]==c;
    for (auto y:g[x])
    dfs2(y,c);
}
int main(){
    freopen("grandiloquence.in","r",stdin);
    freopen("grandiloquence.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int id;cin>>id;
    cin>>n>>m>>k;
    for (int i=1;i<=n;i++)
    cin>>fa[i],g[fa[i]].push_back(i);
int pre=0;
    while(m--){
        int op,x,c;
        cin>>op;
        if(op==1){
            cin>>x>>c;
            if(id%2==0)
            x^=pre,c^=pre;
            dfs1(x,c,0);
        }else if(op==2){
            cin>>x>>c;
            if(id%2==0)
            x^=pre,c^=pre;
            // cout<<x<<"~~"<<c<<" "<<pre<<"\n";
            zong=0;dfs2(x,c);
            cout<<zong<<"\n";
            pre=zong;
        }else {
            cin>>x;
            if(id%2==0)
            x^=pre;
            fa[++n]=x;g[x].push_back(n);
        }
    }
}