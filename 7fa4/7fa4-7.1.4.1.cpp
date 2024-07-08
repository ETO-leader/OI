#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr int maxlen=6e5+7;
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
        for(down(u);nrt(u);rotate(u));
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
class suffixam{
private:
    static constexpr auto alpha=26;
    vector<array<int,alpha>> tr;
    vector<int> len,fail,linked;
    link_cut_tree lct;
    int cur,cnt;
    auto allocm(const int valu){
        const auto u=++cnt;
        lct.update(u,u,valu);
        return u;
    }
    auto setfail(int u,int fl){
        if(linked[u]){
            lct.cut(fail[u],u);
            lct.update(fail[u],0,-lct.query(u));
        }
        fail[u]=fl;linked[u]=true;
        lct.link(fail[u],u);
        lct.update(fail[u],0,lct.query(u));
    }
    auto copy(const int fr,const int u){
        const auto cl=allocm(0);
        len[cl]=len[fr]+1;
        tr[cl]=tr[u];setfail(cl,fail[u]);
        return cl;
    }
    auto insert(const char c){
        const auto u=allocm(1);
        len[u]=len[cur]+1;
        auto ux=cur;
        while(ux>-1&&(!tr[ux][c])){
            tr[ux][c]=u;ux=fail[ux];
        }
        if(ux==-1) return setfail(cur=u,0);
        const auto vx=tr[ux][c];
        if(len[vx]-1==len[ux]){
            setfail(u,vx);
        }else{
            const auto cl=copy(ux,vx);
            while(ux>-1&&tr[ux][c]==vx){
                tr[ux][c]=cl;ux=fail[ux];
            }
            setfail(u,cl);setfail(vx,cl);
        }
        cur=u;
    }
#if defined(__DEBUG__)
    array<int,114514> ans;
    auto dfs(int u)->int{
        //vector<int> ans(cnt+1);
        //cir(i,0,cnt+1) ans[i]=lct.query(i),clog<<i<<":"<<ans[i]<<' '<<fail[i]<<'\n';
        //for(int i=cnt;i;--i) ans[fail[i]]+=ans[i];
        //return ans[u];
        auto res=lct.query(u);
        for(int i=0;i<cnt+1;++i) if(fail[i]==u) clog<<u<<"->"<<i<<'\n',res+=dfs(i);
        clog<<u<<' '<<res<<'\n';
        return ans[u]=res;
    }
#endif
public:
    auto insert(const string s){
        for(const auto&c:s) insert(c-'A');
    }
    auto calc(const string s){
        auto u=0;
        for(const auto&c:s){
            if(!tr[u][c-'A']) return 0;
            u=tr[u][c-'A'];
        }
        return lct.query(u);
    }
    suffixam(int maxn):tr(maxn<<1),len(maxn<<1),lct(maxn<<1),
        linked(maxn<<1),fail(maxn<<1,-1),cur(0),cnt(0){}
};
class iostream_t{
private:
    unsigned mask;
    bool nexted;
    auto decodewithmask(string s){
        if(!nexted) return (nexted=true),s;
        const auto lm=mask;
#if not defined(__DEBUG__)
        cir(j,0,(int)(s.size())){
            mask=(mask*131+j)%s.size();
            swap(s[j],s[mask]);
        }
#endif
        mask=lm;
        return s;
    }
public:
    auto nextint(){
        int x;cin>>x;return x;
    }
    auto nextop(){
        string s;cin>>s;return s;
    }
    auto nextstr(){
        string s;cin>>s;
        return decodewithmask(s);
    }
    auto tell(int ans){
        mask^=ans;cout<<ans<<'\n';
    }
    iostream_t():mask(0),nexted(false){}
} usr;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    const auto n=usr.nextint();
    suffixam sam(maxlen);
    sam.insert(usr.nextstr());
    cir(i,0,n){
        auto op=usr.nextop();
        if(op=="ADD"){
            sam.insert(usr.nextstr());
        }else{
            usr.tell(sam.calc(usr.nextstr()));
        }
    }
    return 0;
}
