#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
class segment{
private:
    vector<pair<int,int>> mn;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    inline auto maintain(int u){
        mn[u]=min(mn[ls(u)],mn[rs(u)]);
    }
    auto update(int u,int l,int r,int p,auto info){
        if(l==r) return mn[u]=info,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,info):update(rs(u),mid+1,r,p,info);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr) const{
        if(qr<l||r<ql) return make_pair(_inf,-1);
        if(ql-1<l&&r-1<qr) return mn[u];
        const auto mid=(l+r)/2;
        return min(query(ls(u),l,mid,ql,qr),query(rs(u),mid+1,r,ql,qr));
    }
    const int n;
public:
    auto update(int p,auto info){
        update(1,0,n-1,p,info);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):n(_n),mn(_n<<2){}
};
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> siz,ban;
    segment sg;
    auto dfssz(int u,int f=-1)->int{
        siz[u]=1;
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])) siz[u]+=dfssz(v,u);
        return siz[u];
    }
    auto dfsrt(int u,const int tsiz,int f=-1)->int{
        auto umx=-1;
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])){
            const auto vw=dfsrt(v,tsiz,u);
            if(vw>-1) return vw;
            umx=max(umx,siz[v]);
        }
        if(max(umx,tsiz-siz[u])<tsiz/2+1) return u;
        return -1;
    }
    int pcnt;
    // (value, node-dep, p-node, left, right)
    priority_queue<tuple<lint,lint,int,int,int>,vector<tuple<lint,lint,int,int,int>>,greater<tuple<lint,lint,int,int,int>>> q;
    auto dfsht(int u,lint c,int l,int r,int f=-1)->void{
        ++pcnt;
        sg.update(pcnt,make_pair(c,pcnt));
        const auto[xw,xu]=sg.query(l,r);
        q.emplace(c+xw,c,xu,l,r);
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])) dfsht(v,c+w,l,r,u);
    }
    auto divide(int u){
        const auto tsiz=dfssz(u);
        if(tsiz==1) return;
        const auto rt=dfsrt(u,tsiz);
        ban[rt]=true;
        ++pcnt;
        const auto ul=pcnt;
        sg.update(pcnt,make_pair(0,pcnt));
        for(auto&[v,w]:gr[rt]) if(!ban[v]){
            const auto ur=pcnt;
            dfsht(v,w,ul,ur,rt);
        }
        for(auto&[v,w]:gr[rt]) if(!ban[v]) divide(v);
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,-w);
        gr[v].emplace_back(u,-w);
    }
    auto count(const int m){
        divide(0);
        vector<lint> ans;
        cir(i,0,m){
            const auto[w,udep,xw,l,r]=q.top();q.pop();
            ans.emplace_back(-w);
            if(xw!=l){
                const auto[wl,ul]=sg.query(l,xw-1);
                q.emplace(udep+wl,udep,ul,l,xw-1);
            }
            if(xw!=r){
                const auto[wr,ur]=sg.query(xw+1,r);
                q.emplace(udep+wr,udep,ur,xw+1,r);
            }
        }
        return ans;
    }
    tree(int _n):gr(_n),siz(_n),ban(_n),sg(_n*30),pcnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;tree gr(n);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    const auto ans=gr.count(m);
    for(auto&x:ans) cout<<x<<'\n';
    return 0;
}
