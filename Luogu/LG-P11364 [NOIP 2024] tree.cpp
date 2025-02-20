#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f,lef,rig;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        lef[v]=min(lef[v],lef[u]);
        rig[v]=max(rig[v],rig[u]);
        f[u]=v;
    }
    auto range(int u){
        u=findset(u);
        return pair(lef[u],rig[u]);
    }
    dsu(int _n):f(_n),lef(_n),rig(_n){
        iota(f.begin(),f.end(),0);
        iota(lef.begin(),lef.end(),0);
        iota(rig.begin(),rig.end(),0);
    }
};
class tree{
private:
    vector<vector<int>> gr,pl;
    vector<vector<pair<int,int>>> vl;
    vector<int> dfn,rdfn,siz,dep;
    dsu st;
    auto init(int u,auto&cnt,int f=-1)->int{
        dfn[u]=++cnt;
        siz[u]=1;dep[u]=(f>-1?dep[f]:0)+1;
        for(auto&i:gr[u]) if(i!=f) siz[u]+=init(i,cnt,u);
        rdfn[u]=cnt;
        return siz[u];
    }
    auto isancestor(int u,int v){
        return dfn[u]<dfn[v]+1&&rdfn[v]<rdfn[u]+1;
    }
    auto uprange(int u,int v){
        const auto n=(int)(gr.size());
        const auto[lef,rig]=st.range(v);
        auto res=false;
        if(lef&&isancestor(u,lef-1)) res=true,st.merge(lef-1,v);
        if(rig+1<n&&isancestor(u,rig+1)) res=true,st.merge(rig+1,v);
        return res;
    }
    auto dfs(int u,int f=-1){
        if(f>-1) assert(ranges::find(gr[u],f)!=gr[u].end()),gr[u].erase(ranges::find(gr[u],f));
        ranges::sort(gr[u],[&](auto u,auto v){
            return siz[u]>siz[v];
        });
        auto emplace=[&](int v){
            auto ok=false;
            pl[u].emplace_back(v);
            while(uprange(u,v)) ok=true;
            if(!ok) return;
            const auto[l,r]=st.range(v);
            vl[u].emplace_back(l,r);
        };
        auto check=[&]{
            emplace(u);
            auto nw=false;
            for(auto&[l,r]:vl[u]) nw|=(l-1<u&&u-1<r);
            if(!nw) vl[u].emplace_back(u,u);
        };
        if(gr[u].empty()) return check();
        dfs(gr[u][0],u);
        swap(pl[u],pl[gr[u][0]]);
        for(auto&i:gr[u]) if(i!=gr[u][0]) dfs(i,u);
        for(auto&i:gr[u]) if(i!=gr[u][0]){
            for(auto&v:pl[i]) emplace(v);
        }
        check();
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){
        auto cnt=-1;
        init(0,cnt);dfs(0);
        vector<tuple<int,int,int>> res;
        const auto n=(int)(gr.size());
        cir(u,0,n) for(auto&[l,r]:vl[u]) res.emplace_back(l,r,dep[u]);
        return res;
    }
    tree(int _n):gr(_n),pl(_n),vl(_n),dfn(_n),rdfn(_n),siz(_n),dep(_n),st(_n){}
};
class segment{
private:
    vector<int> mx;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto maintain(int u){
        mx[u]=max(mx[ls(u)],mx[rs(u)]);
    }
    auto update(int u,int l,int r,int p,int w){
        if(l==r) return mx[u]=max(mx[u],w),void();
        const auto mid=midpoint(l,r);
        p-1<mid?update(ls(u),l,mid,p,w):update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return 0;
        if(ql-1<l&&r-1<qr) return mx[u];
        const auto mid=midpoint(l,r);
        return max(query(ls(u),l,mid,ql,qr),query(rs(u),mid+1,r,ql,qr));
    }
    const int n;
public:
    auto update(int p,int w){
        update(1,0,n-1,p,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):mx(_n<<2),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree tr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        tr.link(u,v);
    }
    const auto rng=tr.init();
    int q;cin>>q;
    vector<tuple<int,int,int>> qry(q);
    for(auto&[l,r,k]:qry) cin>>l>>r>>k,--l,--r;
    vector<int> ans(q);
    // TYPE #1: l \le ql \le qr \le r
    [&]{
        vector<vector<pair<int,int>>> rq(n),vw(n);
        for(auto&[l,r,w]:rng) vw[l].emplace_back(r,w);
        for(auto c=-1;auto&[l,r,k]:qry) rq[l].emplace_back(r,++c);
        segment sg(n);
        cir(l,0,n){
            for(auto&[r,w]:vw[l]) sg.update(r,w);
            for(auto&[r,id]:rq[l]) ans[id]=max(ans[id],sg.query(r,n-1));
        }
    }();
    // TYPE #2: |[l,r] \cap [ql,qr]| ] \ge k \land r \le qr
    [&]{
        vector<vector<pair<int,int>>> vw(n);
        vector<vector<tuple<int,int,int>>> rq(n);
        for(auto&[l,r,w]:rng) vw[r-l].emplace_back(r,w);
        segment sg(n);
        for(auto c=-1;auto&[l,r,k]:qry) rq[k-1].emplace_back(l+k-1,r,++c);
        for(auto i=n-1;~i;--i){
            for(auto&[r,w]:vw[i]) sg.update(r,w);
            for(auto&[l,r,id]:rq[i]) ans[id]=max(ans[id],sg.query(l,r));
        }
    }();
    // TYPE #3: |[l,r] \cap [ql,qr]| ] \ge k \land l \ge ql
    [&]{
        vector<vector<pair<int,int>>> vw(n);
        vector<vector<tuple<int,int,int>>> rq(n);
        for(auto&[l,r,w]:rng) vw[r-l].emplace_back(l,w);
        segment sg(n);
        for(auto c=-1;auto&[l,r,k]:qry) rq[k-1].emplace_back(l,r-k+1,++c);
        for(auto i=n-1;~i;--i){
            for(auto&[l,w]:vw[i]) sg.update(l,w);
            for(auto&[l,r,id]:rq[i]) ans[id]=max(ans[id],sg.query(l,r));
        }
    }();
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
