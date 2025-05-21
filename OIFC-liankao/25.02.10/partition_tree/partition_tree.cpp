#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("partition_tree.in");
ofstream ouf("partition_tree.out");
class fileio{
    public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
class link_cut_tree{
private:
    vector<int> mn,mx,rev,f;
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
        mn[u]=min({u,mn[ls(u)],mn[rs(u)]});
        mx[u]=max({u,mx[ls(u)],mx[rs(u)]});
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
    auto getinfo(int u,int v){
        ++u;++v;
        split(u,v);splay(u);
        return pair(mx[u]-1,mn[u]-1);
    }
    link_cut_tree(int _n):mx(_n+1,-1),mn(_n+1,_n+7),rev(_n+1),f(_n+1),ch(_n+1){}
};
static constexpr auto MOD=998244353;
class magicpowered{
private:
    class dsu{
    private:
        vector<int> f;
    public:
        auto findset(int u)->int{
            return u==f[u]?u:f[u]=findset(f[u]);
        }
        auto merge(int u,int v){
            f[findset(v)]=findset(u);
        }
        auto init(){iota(f.begin(),f.end(),0);}
        dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
    };
    vector<lint> pre;
    vector<int> pos;
    dsu qwq;
    int cnt;
public:
    auto emplace(int l,lint w){
        ++l;++cnt;
        pre[cnt]=w;
        auto cur=qwq.findset(cnt-1);
        vector<int> pos;
        while(cur>l-1){
            pos.emplace_back(cur);
            cur=qwq.findset(cur-1);
        }
        pre[cnt]+=pre[cur];
        for(auto&i:pos) qwq.merge(cur,i);
        pos.clear();
    }
    auto query(int l,int r){
        ++l;++r;
        return pre[qwq.findset(r)]-(l?pre[qwq.findset(l-1)]:0);
    }
    auto init(){
        fill(pre.begin(),pre.end(),0);
        qwq.init();cnt=0;
    }
    magicpowered(int _n):pre(_n+1),qwq(_n+1),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,k;inf>>n>>k;
    link_cut_tree lct(n);
    cir(i,0,n-1){
        int u,v;inf>>u>>v;--u;--v;
        lct.link(u,v);
    }
    vector<int> mn(n),mx(n);
    cir(i,1,n){
        const auto[mxx,mnx]=lct.getinfo(i-1,i);
        mn[i-1]=mnx;mx[i-1]=mxx;
    }
    mn[n-1]=n-1;mx[n-1]=-1;
    deque<pair<int,int>> suf;
    suf.emplace_back(MOD,-1);
    ++k;
    vector<lint> f(n);
    vector<int> px(n);
    cir(r,0,n){
        const auto pos=upper_bound(suf.begin(),suf.end(),pair(r+1,-1))->second;
        px[r]=pos;
        while((!suf.empty())&&suf.front().first<mx[r]+1) suf.pop_front();
        suf.emplace_front(mx[r],r);
    }
    magicpowered magic(n+7);
    cir(x,1,k+1){
        magic.init();
        magic.emplace(0,(x==1));
        cir(i,0,n){
            const auto fx=f[i];
            (f[i]=magic.query(px[i]+1,i))%=MOD;
            magic.emplace(mn[i]+1,fx);
        }
        ouf<<f[n-1]<<'\n';
    }
    return 0;
}
