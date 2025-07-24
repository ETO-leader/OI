#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto ups=23;
template<typename _val_type>
class dsu{
private:
    vector<int> f,siz;
    vector<tuple<int,int,_val_type>> info;
    vector<_val_type> mxw;
public:
    auto findset(int u)->int{
        return f[u]==u?u:findset(f[u]);
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        if(siz[u]>siz[v]) swap(u,v);
        info.emplace_back(u,v,mxw[v]);
        if(u==v) return;
        siz[v]+=siz[u];
        mxw[v]=max(mxw[v],mxw[u]);
        f[u]=v;
    }
    auto revoke(){
        auto[u,v,w]=info.back();info.pop_back();
        if(u==v) return;
        siz[v]-=siz[u];
        mxw[v]=w;
        f[u]=u;
    }
    auto value(int x){return mxw[findset(x)];}
    dsu(int _n,vector<_val_type> x):f(_n),siz(_n,1),mxw(x){ranges::iota(f,0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int h,w,l;cin>>h>>w>>l;
    vector<pair<int,int>> a;
    a.reserve(h*w);
    vector id(h,vector<int>(w)),ht(h,vector<int>(w));
    vector<pair<int,int>> rid(h*w);
    map<int,vector<int>> ids;
    [&]{
        auto cnt=-1;
        cir(i,0,h) cir(j,0,w){
            int x;cin>>x;
            ht[i][j]=x;
            id[i][j]=++cnt;
            rid[cnt]={i,j};
            a.emplace_back(x,cnt);
            ids[x+l].emplace_back(cnt);
        }
    }();
    auto va=a;
    ranges::sort(va);
    auto emplace=[&](auto&qwq,int x,int y){
        static auto mx=vector{1,-1,0,0};
        static auto my=vector{0,0,1,-1};
        cir(i,0,4){
            const auto nx=x+mx[i],ny=y+my[i];
            if(nx<0||ny<0||nx>h-1||ny>w-1) continue;
            if(ht[nx][ny]>ht[x][y]) continue;
            qwq.merge(id[x][y],id[nx][ny]);
        }
    };
    auto revoke=[&](auto&qwq,int x,int y){
        static auto mx=vector{1,-1,0,0};
        static auto my=vector{0,0,1,-1};
        cir(i,0,4){
            const auto nx=x+mx[i],ny=y+my[i];
            if(nx<0||ny<0||nx>h-1||ny>w-1) continue;
            if(ht[nx][ny]>ht[x][y]) continue;
            qwq.revoke();
        }
    };
    vector<pair<int,int>> nxt(h*w);
    [&]{
        auto p=-1;
        dsu info(h*w,a);
        for(auto&[uh,x]:ids){
            // clog<<"QwQ: "<<uh<<'\n';
            while(p+1<h*w&&va[p+1].first<uh+1){
                ++p;
                const auto[x,y]=rid[va[p].second];
                emplace(info,x,y);
            }
            for(auto&i:x) nxt[i]=info.value(i);
        }
    }();
    int qc;cin>>qc;
    vector<tuple<int,int,int>> q(qc);
    for(auto c=-1;auto&[u,v,uid]:q){
        int ux,uy,vx,vy;cin>>ux>>uy>>vx>>vy;
        --ux;--uy;--vx;--vy;
        u=id[ux][uy];
        v=id[vx][vy];
        uid=++c;
    }
    vector<int> req(qc);
    [&]{
        dsu qwq(h*w,vector<int>(h*w));
        auto epos=-1;
        auto divide=[&](auto __self,vector<tuple<int,int,int>> uq,int l,int r){
            if(l>r) return;
            const auto mid=midpoint(l,r);
            const auto[wmid,umid]=va[mid];
            while(epos<mid-1) ++epos,emplace(qwq,rid[va[epos].second].first,rid[va[epos].second].second);
            while(epos>mid-1) revoke(qwq,rid[va[epos].second].first,rid[va[epos].second].second),--epos;
            vector<tuple<int,int,int>> ql,qr;
            for(auto&[u,v,id]:uq){
                if(qwq.findset(u)!=qwq.findset(v)) qr.emplace_back(u,v,id),req[id]=wmid;
                else ql.emplace_back(u,v,id);
            }
            __self(__self,ql,l,mid-1);
            __self(__self,qr,mid+1,r);
        };
        divide(divide,q,0,h*w-1);
    }();
    // cir(i,0,h){
    //     cir(j,0,w) clog<<nxt[id[i][j]].first<<' ';
    //     clog<<'\n';
    // }
    vector up(ups,vector<pair<int,int>>(h*w));
    [&]{
        up[0]=nxt;
        cir(i,1,ups) cir(u,0,h*w){
            up[i][u]=up[i-1][up[i-1][u].second];
        }
    }();
    // for(auto&x:req) clog<<x<<' ';
    // clog<<'\n';
    cir(i,0,qc) [&]{
        auto[u,v,id]=q[i];
        if(u==v) return cout<<0<<'\n',void();
        if(up[ups-1][u].first<req[i]) return cout<<-1<<'\n',void();
        auto ans=1;
        for(auto c=ups-1;~c;--c) if(up[c][u].first<req[i]){
            ans+=(1<<c);
            u=up[c][u].second;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
