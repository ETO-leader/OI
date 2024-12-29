#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class link_cut_tree{
private:
    struct node{
        int val,f,add;
        array<int,2> ch;
        bool rev;
        node(int _v=0):val(_v),f(0),ch({0,0}),rev(false),add(0){}
    };
    vector<node> tr;
    auto&ls(auto u){return tr[u].ch[0];}
    auto&rs(auto u){return tr[u].ch[1];}
    auto&f(auto u){return tr[u].f;}
    auto nrt(auto u){return ls(f(u))==u||rs(f(u))==u;}
    auto dir(auto u){return rs(f(u))==u;}
    auto rev(auto u){
        swap(ls(u),rs(u));
        tr[u].rev^=true;
    }
    auto add(auto u,int w){
        tr[u].val+=w;tr[u].add+=w;
    }
    auto push_down(int u){
        if(tr[u].rev) for(auto v:tr[u].ch) if(v) rev(v);
        for(auto v:tr[u].ch) if(v) add(v,tr[u].add);
        tr[u].rev=false;tr[u].add=0;
    }
    auto rotate(int u){
        const auto fu=f(u),gu=f(fu),c=(int)(dir(u));
        if(nrt(fu)) tr[gu].ch[dir(fu)]=u;
        f(u)=gu;
        tr[fu].ch[c]=tr[u].ch[!c];f(tr[u].ch[!c])=fu;
        tr[u].ch[!c]=fu;f(fu)=u;
    }
    auto down(int u)->void{
        if(nrt(u)) down(f(u));
        push_down(u);
    }
    auto splay(int u){
        for(down(u);nrt(u);rotate(u)){
            if(nrt(f(u))) rotate(dir(f(u))==dir(u)?f(u):u);
        }
    }
    auto access(int u){
        for(auto v=0;u;u=f(v=u)){
            splay(u);rs(u)=v;
        }
    }
    auto makeroot(int u){
        access(u);splay(u);rev(u);
    }
    auto split(int u,int v){
        makeroot(u);access(v);splay(u);
    }
public:
    auto link(int u,int v){
        ++u;++v;
        makeroot(u);makeroot(v);
        f(u)=v;
    }
    auto cut(int u,int v){
        ++u;++v;
        split(u,v);splay(v);
        assert(ls(v)==u);
        assert(f(u)==v);
        ls(v)=f(u)=0;
    }
    auto update(int u,int v,int w){
        ++u;++v;
        split(u,v);add(u,w);
    }
    auto query(int u){
        ++u;
        split(u,u);
        return tr[u].val;
    }
    link_cut_tree(int n):tr(n+1){}
};
template<const int alpha>
class ext_suffixam{
private:
    vector<array<int,alpha>> ch;
    vector<int> len,fail;
    link_cut_tree lct;
    lint curans;
    vector<vector<pair<int,char>>> ctr;
    unordered_set<int> clc;
    int clcnt;
    auto clone(int u,int v){
        const auto res=++clcnt;
        ch[res]=ch[v];
        len[res]=len[u]+1;
        fail[res]=fail[v];
        lct.link(res,fail[res]);
        clc.insert(res);
        return res;
    }
    auto appendc(int f,int u,int c){
        auto ux=f;len[u]=len[f]+1;
        while(ux>-1&&(!ch[ux][c])) ch[ux][c]=u,ux=fail[ux];
        if(ux==-1) return fail[u]=0,lct.link(u,fail[u]),lct.update(0,u,1),void();
        const auto v=ch[ux][c];
        if(len[v]==len[ux]+1){
            fail[u]=v;lct.link(u,v);
        }else{
            const auto cl=clone(ux,v);
            while(ux>-1&&ch[ux][c]==v) ch[ux][c]=cl,ux=fail[ux];
            const auto wx=lct.query(v);
            lct.update(0,v,-wx);
            lct.cut(v,fail[v]);
            fail[v]=fail[u]=cl;
            lct.link(u,cl);lct.link(v,cl);
            lct.update(0,v,wx);
        }
        lct.update(0,u,1);
    }
    auto append(int f,int u,int c){
        appendc(f,u,c);
        curans+=len[u]-len[fail[u]];
    }
public:
    auto emplace_tree(int rt,vector<tuple<int,int,char>> ex){
        ctr[rt].clear();
        for(auto&[u,v,w]:ex){
            ctr[u].emplace_back(v,w-'a');
            ctr[v].emplace_back(u,w-'a');
        }
        auto dfs=[&](auto __self,int u,int f)->void {
            for(auto&[v,w]:ctr[u]) if(v!=f){
                append(u,v,w);__self(__self,v,u);
            }
        };
        dfs(dfs,rt,-1);
    }
    auto diffsub(){return curans;}
    auto strsum(string s){
        auto u=0;
        for(auto&c:s) if(ch[u][c-'a']){
            u=ch[u][c-'a'];
        }else{
            return 0;
        }
        return lct.query(u);
    }
    ext_suffixam(int _n):
        ch((_n<<1)+7),ctr((_n<<1)+7),
        len((_n<<1)+7),fail((_n<<1)+7,-1),
        lct((_n<<1)+7),
        curans(0),clcnt(_n+2){}
};
static constexpr auto maxn=(int)(1e5+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int id,n;cin>>id>>n;
    vector<tuple<int,int,char>> ax;
    cir(i,0,n-1){
        int u,v;char c;cin>>u>>v>>c;
        --u;--v;
        ax.emplace_back(u,v,c);
    }
    ext_suffixam<3> sam(maxn);
    sam.emplace_tree(0,ax);
    int q;cin>>q;
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            cout<<sam.diffsub()<<'\n';
        }else if(op==2){
            ax.clear();
            int rt,s;cin>>rt>>s;--rt;
            cir(i,0,s-1){
                int u,v;char c;cin>>u>>v>>c;--u;--v;
                ax.emplace_back(u,v,c);
            }
            sam.emplace_tree(rt,ax);
        }else{
            string s;cin>>s;
            cout<<sam.strsum(s)<<'\n';
        }
    }
    return 0;
}
