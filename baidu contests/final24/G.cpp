#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using qint=__int128_t;
using poly=vector<lint>;
ostream&operator<<(ostream&os,qint x){
    if(x>9) os<<x/10;
    return os<<(int)(x%10);
}
class link_cut_tree{
private:
    struct node{
        int val,tag;bool rev;
        auto upd(int w){
            val+=w;tag+=w;
        }
        node():val(0),tag(0),rev(false){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto push_down(int u){
        if(ls(u)) tr[ls(u)].upd(tr[u].tag);
        if(rs(u)) tr[rs(u)].upd(tr[u].tag);
        if(ls(u)) tr[ls(u)].rev^=tr[u].rev;
        if(rs(u)) tr[rs(u)].rev^=tr[u].rev;
        if(tr[u].rev) swap(ls(u),rs(u));
        tr[u].rev=false;tr[u].tag=0;
    }
    auto nrt(int u){
        return ls(f[u])==u||rs(f[u])==u;
    }
    auto getch(int u){
        return rs(f[u])==u;
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu];
        const auto c=getch(u);
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        push_down(fu);push_down(u);
    }
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto splay(int u){
        down(u);
        for(int fx;fx=f[u],nrt(u);rotate(u)){
            if(nrt(fx)) rotate(getch(fx)==getch(u)?fx:u);
        }
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]) splay(u),rs(u)=v;
    }
    auto mkrt(int u){
        access(u);splay(u);
        tr[u].rev^=true;push_down(u);
    }
    auto split(int u,int v){
        mkrt(u);access(v);splay(v);
    }
public:
    auto link(int u,int v){
        ++u;++v;
        mkrt(u);mkrt(v);f[u]=v;
    }
    auto cut(int u,int v){
        ++u;++v;
        split(u,v);ls(v)=f[u]=0;
    }
    auto update(int u,int v,int w){
        ++u;++v;
        split(u,v);splay(u);
        tr[u].upd(w);
    }
    auto query(int u){
        ++u;
        split(u,u);splay(u);
        return tr[u].val;
    }
    link_cut_tree(int n):tr(n+1),ch(n+1),f(n+1){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return ++cnt;}
    nodegen(int _n):cnt(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    link_cut_tree lct(n*2+7);
    vector<int> eid(n-1);
    vector<lint> ew(n-1);
    nodegen ngen(n);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        eid[i]=ngen();ew[i]=w;
        lct.link(u,eid[i]);
        lct.link(eid[i],v);
    }
    auto las=1;
    cir(i,0,m){
        int u;cin>>u;
        lct.update(las,u,1);
        las=u;
    }
    priority_queue<pair<lint,int>> q;
    vector<lint> aps(n-1);
    auto ans=qint(0);
    cir(i,0,n-1){
        const auto w=lct.query(eid[i]);
        aps[i]=w;
        ans+=w*ew[i];
        q.emplace(w*(ew[i]-ew[i]/2),i);
    }
    cir(i,0,k){
        if(q.empty()) break;
        const auto[w,u]=q.top();q.pop();
        ans-=w;
        ew[u]/=2;
        if(ew[u]-ew[u]/2) q.emplace(aps[u]*(ew[u]-ew[u]/2),u);
    }
    cout<<ans<<'\n';
    return 0;
}
