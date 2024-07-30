#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class link_cut_tree{
private:
    struct node{
        lint col,vcnt,cnt,vans,lans,rans,w,sum;
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f,rev;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u){return rs(f[u])==u;}
    auto revn(int u){
        swap(tr[u].lans,tr[u].rans);rev[u]^=true;
    }
    auto push_down(int u){
        if(!rev[u]) return;
        for(auto x:{ls(u),rs(u)}) revn(x);
        swap(ls(u),rs(u));
        rev[u]=false;
    }
    auto maintain(int u){
        tr[u].cnt=tr[u].col+tr[u].vcnt+tr[ls(u)].cnt+tr[rs(u)].cnt;
        tr[u].lans=
            tr[u].vans+
            tr[ls(u)].lans+tr[rs(u)].lans+
            (tr[u].col+tr[u].vcnt+tr[rs(u)].cnt)*(tr[u].w+tr[ls(u)].sum);
        tr[u].rans=
            tr[u].vans+
            tr[ls(u)].rans+tr[rs(u)].rans+
            (tr[u].col+tr[u].vcnt+tr[ls(u)].cnt)*(tr[u].w+tr[rs(u)].sum);
        tr[u].sum=tr[u].w+tr[ls(u)].sum+tr[rs(u)].sum;
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
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto splay(int u){
        for(down(u);nrt(u);rotate(u));
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);
            tr[u].vans+=tr[rs(u)].lans;
            tr[u].vans-=tr[v].lans;
            tr[u].vcnt+=tr[rs(u)].cnt;
            tr[u].vcnt-=tr[v].cnt;
            rs(u)=v;
            maintain(u);
        }
    }
    auto mkrt(int u){
        access(u);splay(u);
        revn(u);push_down(u);
    }
    auto split(int u,int v){
        mkrt(u);access(v);splay(v);
    }
public:
    auto link(int u,int v){
        mkrt(u);mkrt(v);
        f[u]=v;
        tr[v].vans+=tr[u].lans;
        tr[v].vcnt+=tr[u].cnt;
        maintain(v);
    }
    auto cut(int u,int v){
        split(u,v);
        ls(v)=f[u]=0;
        maintain(v);maintain(u);
    }
    auto flip(int u){
        mkrt(u);tr[u].col^=true;maintain(u);
    }
    auto static_initnode(int u,lint w){
        tr[u].w=tr[u].sum=w;
    }
    auto query(int u){
        mkrt(u);
        return tr[u].lans;
    }
    link_cut_tree(int n):tr(n+1),ch(n+1),f(n+1),rev(n+1){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return cnt++;}
    nodegen(int n=0):cnt(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;nodegen ngen(n+1);
    link_cut_tree lct(n+m+k+7);
    map<pair<int,int>,int> enid;
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;
        if(u>v) swap(u,v);
        const auto ex=ngen();
        enid[{u,v}]=ex;
        lct.static_initnode(ex,w);
        lct.link(u,ex);lct.link(v,ex);
    }
    cir(i,0,k){
        string op;cin>>op;
        if(op[0]=='L'){
            int u,v;lint w;cin>>u>>v>>w;
            if(u>v) swap(u,v);
            const auto ex=ngen();
            enid[{u,v}]=ex;
            lct.static_initnode(ex,w);
            lct.link(u,ex);lct.link(v,ex);
        }else if(op[0]=='C'){
            int u,v;cin>>u>>v;
            if(u>v) swap(u,v);
            const auto ex=enid[{u,v}];
            lct.cut(u,ex);lct.cut(v,ex);
        }else if(op[0]=='F'){
            int u;cin>>u;lct.flip(u);
        }else{
            int u;cin>>u;
            cout<<lct.query(u)<<'\n';
        }
    }
    return 0;
}
