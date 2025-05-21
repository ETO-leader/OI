#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("partial.in");
ofstream ouf("partial.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
class link_cut_tree{
    private:
    vector<int> sum,val,rev,f;
    vector<array<int,2>> ch;
    auto&ls(auto u){return ch[u][0];}
    auto&rs(auto u){return ch[u][1];}
    auto nrt(auto u){return ls(f[u])==u||rs(f[u])==u;}
    auto chid(auto u){return rs(f[u])==u;}
    auto reverse(auto u){
        rev[u]^=true;
        swap(ls(u),rs(u));
    }
    auto push_down(int u){
        if(!rev[u]) return;
        reverse(ls(u));reverse(rs(u));
        rev[u]=false;
    }
    auto maintain(int u){
        sum[u]=sum[ls(u)]+sum[rs(u)]+val[u];
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu],c=(int)(chid(u));
        if(nrt(fu)) ch[gu][chid(fu)]=u;
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
        for(down(u);nrt(u);rotate(u)){
            const auto fu=f[u];
            if(nrt(fu)){
                if(chid(fu)==chid(u)) rotate(fu);
                else rotate(u);
            }
        }
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);rs(u)=v;maintain(u);
        }
    }
    auto makeroot(int u){
        access(u);splay(u);
        reverse(u);
    }
    auto split(int u,int v){
        makeroot(u);access(v);splay(v);
    }
    public:
    auto link(int u,int v){
        ++u;++v;
        makeroot(u);makeroot(v);
        f[v]=u;
    }
    auto chgnode(int u,int w){
        ++u;
        split(u,u);
        splay(u);
        val[u]=w;maintain(u);
    }
    auto getsum(int u,int v){
        ++u;++v;
        split(u,v);splay(u);
        return sum[u];
    }
    link_cut_tree(int _n):sum(_n+1),val(_n+1),rev(_n+1),f(_n+1),ch(_n+1){}
};
class bit{
    private:
    vector<int64_t> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
    public:
    auto update(int u,int64_t w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=w;
    }
    auto query(int u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int n):a(n+1){}
};
class flower{
    public:
    flower(const int n,const int q,string s){
        int cx=0;
        cir(i,1,n) cx+=(s[i]=='1'||s[i]=='?');
        cir(i,0,q){
            int u;char c;inf>>u>>c;--u;
            if(u){
                cx-=(s[u]=='1'||s[u]=='?');
                s[u]=c;
                cx+=(s[u]=='1'||s[u]=='?');
            }else{
                s[u]=c;
            }
            ouf<<(s[0]!='1')*cx<<'\n';
        }
    }
};
class noqry{
    public:
    vector<vector<int>> gr;
    vector<int> dfn,rdfn;
    bit sub;
    link_cut_tree fp;
    int64_t ans;
    auto init(int u,auto&cnt,int f=-1)->void{
        dfn[u]=++cnt;
        for(auto&i:gr[u]) if(i!=f){
            init(i,cnt,u);
        }
        rdfn[u]=cnt;
    }
    auto rmv_col(int u,int c){
        if(c){
            sub.update(dfn[u],-1);
            ans-=fp.getsum(0,u);
        }else{
            fp.chgnode(u,0);
            ans-=(sub.query(rdfn[u])-sub.query(dfn[u]-1));
        }
    }
    auto ins_col(int u,int c){
        if(c){
            sub.update(dfn[u],1);
            ans+=fp.getsum(0,u);
        }else{
            fp.chgnode(u,1);
            ans+=(sub.query(rdfn[u])-sub.query(dfn[u]-1));
        }
    }
    public:
    noqry(int n,int q,vector<int> f,string s):gr(n),dfn(n),rdfn(n),sub(n),fp(n),ans(0){
        cir(i,1,n){
            gr[f[i]].emplace_back(i);
            gr[i].emplace_back(f[i]);
            fp.link(f[i],i);
        }
        auto cnt=-1;init(0,cnt);
        cir(i,0,n) ins_col(i,s[i]-'0');
        cir(i,0,q){
            int u;char c;inf>>u>>c;--u;
            rmv_col(u,s[u]-'0');
            s[u]=c;
            ins_col(u,s[u]-'0');
            ouf<<ans<<'\n';
        }
    }
};
static constexpr auto _infl=(int64_t)(1e16l);
class tree{
private:
    vector<int> siz;
    vector<vector<int>> gr;
    vector<vector<int64_t>> fx;
    vector<int64_t> nf;
    string col;
    auto dfs(int u,int f=-1)->int{
        siz[u]=1;
        for(auto&i:gr[u]) if(i!=f) siz[u]+=dfs(i,u);
        fx[u].resize(siz[u]+1);
        return siz[u];
    }
    // f(u,c): u 子树里的 '1' 数量是 c
    auto check(int u,int f=-1)->void{
        auto csiz=1;
        fill(fx[u].begin(),fx[u].end(),-_infl);
        fx[u][0]=0;
        for(auto&i:gr[u]) if(i!=f){
            check(i,u);
            fill(nf.begin(),nf.begin()+siz[i]+csiz+1,-_infl);
            cir(nx,0,siz[i]+1) cir(uw,0,csiz){
                nf[nx+uw]=max(nf[nx+uw],fx[u][uw]+fx[i][nx]);
            }
            copy(nf.begin(),nf.begin()+siz[i]+csiz+1,fx[u].begin());
            csiz+=siz[i];
        }
        if(col[u]=='0'){
            cir(i,0,siz[u]+1) fx[u][i]+=i;
        }else if(col[u]=='1'){
            fx[u].emplace(fx[u].begin(),-_infl);
            fx[u].pop_back();
        }else{
            cir(i,1,siz[u]+1) nf[i]=max(fx[u][i]+i,fx[u][i-1]);
            copy(nf.begin()+1,nf.begin()+siz[u]+1,fx[u].begin()+1);
        }
    }
public:
    tree(const int n,const int q,vector<int> fr,string s):siz(n),gr(n),fx(n),nf(n+1),col(s){
        cir(i,1,n) gr[fr[i]].emplace_back(i),gr[i].emplace_back(fr[i]);
        dfs(0);
        cir(i,0,q){
            int u;char c;inf>>u>>c;--u;
            col[u]=c;
            check(0);
            ouf<<*max_element(fx[0].begin(),fx[0].end())<<'\n';
        }
    }
};
class chain{
private:
    bit cf,ct;
    int64_t ans;
    int st;
    auto rmv_col(int u,char c){
        ans-=(c=='0'?st-ct.query(u):cf.query(u-1));
        st-=(c!='0');
        (c=='0'?cf:ct).update(u,-1);
    }
    auto ins_col(int u,char c){
        ans+=(c=='0'?st-ct.query(u):cf.query(u-1));
        st+=(c!='0');
        (c=='0'?cf:ct).update(u,1);
    }
public:
    chain(const int n,const int q,string s):cf(n),ct(n),ans(0),st(0){
        auto check=[&](int l,int r){
            auto res=ans;
            const auto crg=count(s.begin()+l,s.begin()+r+1,'?');
            auto c0=cf.query(l-1),c1=st-ct.query(l-1);
            auto cur=ans;
            auto pos=l-1;
            cir(i,l,r+1) if(s[i]=='?'){
                --c1;
                cur-=c0;
                cur+=c1;
                ++c0;
                if(res<cur) pos=i;
                res=max(res,cur);
            }else if(s[i]=='0'){
                ++c0;
            }else{
                --c1;
            }
            return make_pair(res,pos);
        };
        cir(i,0,n) ins_col(i,s[i]);
        const auto mid=check(0,n-1).second;
        cerr<<"MID = "<<mid<<'\n';
        cir(i,0,n) rmv_col(i,s[i]);
        const auto l=max(mid-5000,0),r=min(mid+5000,n-1);
        cir(i,0,n){
            if(i<l&&s[i]=='?') s[i]='0';
            if(i>r&&s[i]=='?') s[i]='1';
            ins_col(i,s[i]);
        }
        cir(i,0,q){
            int u;char c;inf>>u>>c;--u;
            if(u<l&&c=='?') c='0';
            if(u>r&&c=='?') c='1';
            rmv_col(u,s[u]);
            ins_col(u,(s[u]=c));
            ouf<<check(l,r).first<<'\n';
        }
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q;inf>>n>>q;string s;inf>>s;
    vector<int> f(n);
    cir(i,1,n) inf>>f[i],--f[i];
    if(n<1007&&q<1007){
        tree(n,q,f,s);
        exit(0);
    }
    if(!(*max_element(f.begin(),f.end()))){
        flower(n,q,s);
        exit(0);
    }
    if(!count(s.begin(),s.end(),'?')){
        noqry(n,q,f,s);
        exit(0);
    }
    chain(n,q,s);
    return 0;
}
