#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class casereader{
private:
    union datatype{
        char*chr;
        int*i32;
        string*str;
        datatype(char*x):chr(x){}
        datatype(int*x):i32(x){}
        datatype(string*x):str(x){}
    };
    vector<datatype> data;
    int pos;
    template<typename _Ty>
    auto readarg(){
        _Ty x;cin>>x;data.emplace_back(new _Ty(x));
        return x;
    }
public:
    auto init(){
        const auto id=readarg<int>();
        const auto n=readarg<int>();
        cir(i,0,n-1){
            readarg<int>();readarg<int>();readarg<char>();
        }
        const auto q=readarg<int>();
        cir(i,0,q){
            const auto op=readarg<int>();
            if(op==1) continue;
            if(op==2){
                const auto rt=readarg<int>(),s=readarg<int>();
                cir(i,0,s-1) readarg<int>(),readarg<int>(),readarg<char>();
            }else if(op==3){
                readarg<string>();
            }
        }
    }
    auto readargs(char&x){
        x=*data[pos].chr;delete data[pos++].chr;
    }
    auto readargs(int&x){
        x=*data[pos].i32;delete data[pos++].i32;
    }
    auto readargs(string&x){
        x=*data[pos].str;delete data[pos++].str;
    }
    auto readargs(auto&...args){
        (readargs(args),...);
    }
    casereader():pos(0){}
};
using lint=long long;
class link_cut_tree{
private:
    struct node{
        int val,sum,f;
        array<int,2> ch;
        bool rev;
        node(int _v=0):val(_v),sum(_v),f(0),ch({0,0}),rev(false){}
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
    auto push_down(int u){
        if(tr[u].rev) for(auto v:tr[u].ch) if(v) rev(v);
        tr[u].rev=false;
    }
    auto maintain(int u){
        tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum+tr[u].val;
    }
    auto rotate(int u){
        const auto fu=f(u),gu=f(fu),c=(int)(dir(u));
        if(nrt(fu)) tr[gu].ch[dir(fu)]=u;
        f(u)=gu;
        tr[fu].ch[c]=tr[u].ch[c^1];f(tr[u].ch[c^1])=fu;
        tr[u].ch[c^1]=fu;f(fu)=u;
        maintain(fu);maintain(u);
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
        for(int v=0;u;v=u,u=f(u)){
            splay(u);rs(u)=v;maintain(u);
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
        makeroot(u);f(u)=v;
    }
    auto initval(int u,int w){
        ++u;
        split(u,u);tr[u]=node(w);
    }
    auto query(int u,int v){
        ++u;++v;
        split(u,v);
        return tr[u].sum;
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
    int clcnt;
    auto clone(int u,int v){
        const auto res=++clcnt;
        ch[res]=ch[v];
        len[res]=len[u]+1;
        fail[res]=fail[v];
        // lct.link(res,fail[res]);
        // lct.initval(res,1);
        return res;
    }
    auto appendc(int f,int u,int c){
        auto ux=f;len[u]=len[f]+1;
        while(ux>-1&&(!ch[ux][c])) ch[ux][c]=u,ux=fail[ux];
        // lct.initval(u,1);
        clog<<f<<' '<<u<<' '<<c<<" <--> "<<ux<<'\n';
        if(ux==-1) return fail[u]=0,lct.link(u,fail[u]),void();
        const auto v=ch[ux][c];
        if(len[v]==len[ux]+1){
            fail[u]=v;// lct.link(u,v);
        }else{
            const auto cl=clone(ux,v);
            while(ux>-1&&ch[ux][c]==v) ch[ux][c]=cl,ux=fail[ux];
            fail[v]=fail[u]=cl;
            // lct.link(u,cl);lct.link(v,cl);
        }
    }
    auto append(int f,int u,int c){
        cerr<<"A: "<<f<<' '<<u<<' '<<c<<'\n';
        appendc(f,u,c);
        curans+=len[u]-len[fail[u]];
        cerr<<"! "<<u<<' '<<fail[u]<<' '<<len[u]<<" <--> "<<len[fail[u]]<<' '<<len[u]-len[fail[u]]<<'\n';
    }
public:
    auto emplace_tree(int rt,vector<tuple<int,int,char>> ex){
        ctr[rt].clear();
        for(auto&[u,v,w]:ex){
            ctr[u].emplace_back(v,w-'a');
            ctr[v].emplace_back(u,w-'a');
                cerr<<u<<' '<<v<<' '<<w<<'\n';
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
        // return lct.query(0,u);
        return -1;
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
    casereader inf;inf.init();
    int id;inf.readargs(id);
    int n;inf.readargs(n);
    vector<tuple<int,int,char>> ax;
    cir(i,0,n-1){
        int u,v;char c;inf.readargs(u,v,c);
        --u;--v;
        ax.emplace_back(u,v,c);
    }
    ext_suffixam<3> sam(maxn);
    sam.emplace_tree(0,ax);
    int q;inf.readargs(q);
    cir(i,0,q){
        int op;inf.readargs(op);
        if(op==1){
            cout<<sam.diffsub()<<'\n';
        }else if(op==2){
            ax.clear();
            int rt,s;inf.readargs(rt,s);--rt;
            cir(i,0,s-1){
                int u,v;char c;inf.readargs(u,v,c);--u;--v;--c;
                ax.emplace_back(u,v,c);
            }
            sam.emplace_tree(rt,ax);
        }else{
            string s;inf.readargs(s);
            cout<<sam.strsum(s)<<'\n';
        }
    }
    return 0;
}
