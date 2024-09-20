#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class link_cut_tree{
private:
    struct node{
        lint w,siz,sum,tag;
        auto upd(lint nt){
            sum+=nt*siz;tag+=nt;w+=nt;
        }
        node():w(0),siz(1),sum(0),tag(0){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f,rev;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u){return rs(f[u])==u;}
    auto push_down(int u){
        if(tr[u].tag){
            tr[ls(u)].upd(tr[u].tag);
            tr[rs(u)].upd(tr[u].tag);
            tr[u].tag=0;
        }
        if(!rev[u]) return;
        for(auto v:{ls(u),rs(u)}) rev[v]^=true;
        swap(ls(u),rs(u));
        rev[u]=false;
    }
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+1;
        tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum+tr[u].w;
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu],c=(int)(getch(u));
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
        down(u);
        for(int fx;fx=f[u],nrt(u);rotate(u)){
            if(nrt(fx)) rotate(getch(fx)==getch(u)?fx:u);
        }
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);rs(u)=v;maintain(u);
        }
    }
    auto mkrt(int u){
        access(u);splay(u);
        rev[u]^=true;push_down(u);
    }
    auto split(int u,int v){
        mkrt(v);access(u);splay(u);
    }
public:
    auto link(int u,int v){
        ++u;++v;
        mkrt(u);mkrt(v);
        f[u]=v;
    }
    auto update(int u,int v,int c){
        ++u;++v;
        split(u,v);splay(u);
        tr[u].upd(c);
    }
    auto query(int u,int v){
        ++u;++v;
        split(u,v);splay(u);
        return tr[u].sum;
    }
    link_cut_tree(int _n):tr(_n+1),ch(_n+1),f(_n+1),rev(_n+1){
        tr[0].siz=0;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;lint w;cin>>n>>w;
        link_cut_tree lct(n*2);
        vector<vector<int>> gr(n);
        vector<int> px;
        cir(i,1,n){
            int v;cin>>v;--v;
            gr[i].push_back(v);
            gr[v].push_back(i);
            lct.link(i,n+i-1);
            lct.link(v,n+i-1);
        }
        vector<int> submx(n);
        auto dfs=[&](auto __self,int u,int f=0)->int {
            submx[u]=u;
            for(auto&i:gr[u]) if(i!=f) submx[u]=max(submx[u],__self(__self,i,u));
            return submx[u];
        };
        dfs(dfs,0);
        cir(i,n,n*2-1) lct.update(i,i,1);
        auto pans=0ll,cnt=(lint)(n);
        cir(i,0,n-1){
            int id;lint x;cin>>id>>x;id-=2;
            lct.update(id+n,id+n,-1);
            pans+=x*2;w-=x;
            const auto u=id+1;
            const auto lasu=(u+n-1)%n,mxu=submx[u],nmx=(submx[u]+1)%n;
            if(!lct.query(lasu,u)) --cnt;
            if(!lct.query(mxu,nmx)) --cnt;
            // clog<<"C="<<cnt<<' '<<u<<' '<<lct.update(lasu,u,0,lct.calc)<<' ';
            cout<<cnt*w+pans<<' ';
        }
        cout<<'\n';// clog<<'\n';
    }
    return 0;
}
