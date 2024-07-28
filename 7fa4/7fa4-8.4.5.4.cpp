#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class link_cut_tree{
private:
    struct node{
        int mx,nw,lx,rx,sum;
        multiset<int,greater<int>> w,chm;
        node():mx(-_inf),lx(-_inf),rx(-_inf),sum(0),w({-_inf,-_inf}),chm({-_inf,-_inf}),nw(0){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u){return rs(f[u])==u;}
    auto maintain(int u){
        const auto wx=max(tr[u].nw,*tr[u].w.begin());
        const auto uw=max(wx,tr[ls(u)].rx+(u>1));
        const auto dw=max(wx,tr[rs(u)].lx)+(u>1);
        tr[u].lx=max(tr[ls(u)].lx,dw+tr[ls(u)].sum);
        tr[u].rx=max(tr[rs(u)].rx,uw+tr[rs(u)].sum);
        tr[u].mx=max({
            uw+tr[rs(u)].lx,
            dw+tr[ls(u)].rx,
            *tr[u].chm.begin(),
            *tr[u].w.begin()+*next(tr[u].w.begin()),
            tr[ls(u)].mx,
            tr[rs(u)].mx
        });
        if(tr[u].nw>-1) tr[u].mx=max({tr[u].mx,*tr[u].w.begin(),0});
        tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum+(u>1);
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu];
        const auto c=getch(u);
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        maintain(fu);maintain(u);
    }
    auto splay(int u){
        for(;nrt(u);rotate(u));
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);
            if(rs(u)) tr[u].w.insert(tr[rs(u)].lx);
            if(rs(u)) tr[u].chm.insert(tr[rs(u)].mx);
            if(v) tr[u].w.extract(tr[v].lx);
            if(v) tr[u].chm.extract(tr[v].mx);
            rs(u)=v;
            maintain(u);
        }
    }
public:
    auto static_link(int u,int v){
        f[v]=u;
        tr[u].w.insert(tr[v].lx);
        tr[u].chm.insert(tr[v].mx);
        maintain(u);
    }
    auto refresh(int u){maintain(u);}
    auto update(int u,int sw){
        access(u);splay(u);
        tr[u].nw=sw;
        maintain(u);
    }
    auto dist(){
        access(1);splay(1);
        return tr[1].mx;
    }
    link_cut_tree(int _n):tr(_n+1),ch(_n+1),f(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;link_cut_tree lct(n);
    vector<vector<int>> gr(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto dfs=[&](auto __self,int u,int f=-1)->void {
        for(auto&i:gr[u]) if(i!=f){
            __self(__self,i,u);lct.static_link(u,i);
        }
        lct.refresh(u);
    };
    dfs(dfs,1);
    vector<int> light(n+1);
    int q;cin>>q;
    cir(i,0,q){
        string op;cin>>op;
        if(op[0]=='G'){
            const auto ans=lct.dist();
            cout<<(ans<0?-1:ans)<<'\n';
        }else{
            int u;cin>>u;
            lct.update(u,(light[u]^=1)?-_inf:0);
        }
    }
    return 0;
}
