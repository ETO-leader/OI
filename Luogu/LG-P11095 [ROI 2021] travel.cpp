#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class segment{
private:    
    struct node{
        int mn,ckmn;
        node():mn(_inf),ckmn(_inf){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto push_down(int u){
        tr[ls(u)].mn=min(tr[ls(u)].mn,tr[u].mn);
        tr[ls(u)].ckmn=min(tr[ls(u)].ckmn,tr[u].ckmn);
        tr[rs(u)].mn=min(tr[rs(u)].mn,tr[u].mn);
        tr[rs(u)].ckmn=min(tr[rs(u)].ckmn,tr[u].ckmn);
    }
    auto maintain(int u){
        tr[u].mn=min(tr[ls(u)].mn,tr[rs(u)].mn);
    }
    auto update(int u,int l,int r,int ql,int qr,int w){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return tr[u].mn=min(tr[u].mn,w),tr[u].ckmn=min(tr[u].ckmn,w),void();
        const auto mid=(l+r)/2;
        push_down(u);
        update(ls(u),l,mid,ql,qr,w);
        update(rs(u),mid+1,r,ql,qr,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return _inf;
        if(ql-1<l&&r-1<qr) return tr[u].mn;
        const auto mid=(l+r)/2;
        push_down(u);
        return min(query(ls(u),l,mid,ql,qr),query(rs(u),mid+1,r,ql,qr));
    }
    const int n;
public:
    auto update(int l,int r,int w){
        update(1,0,n-1,l,r,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):n(_n),tr(_n<<2){}
};
class dsu{
private:
    vector<int> f;
public:
    auto findset(auto u)->int{
        return u==f[u]?u:f[u]=findset(f[u]);
    }
    auto merge(auto u,auto v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<tuple<int,int,int>> es(m);
    for(auto&[w,u,v]:es) cin>>u>>v>>w,--u,--v;
    sort(es.begin(),es.end());
    vector<vector<int>> gr(n);
    vector<int> dfn(n),rdfn(n),dep(n),uf(n);
    dsu qwq(n);
    for(auto&[w,u,v]:es) if(qwq.findset(u)!=qwq.findset(v)){
        qwq.merge(u,v);
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto dfs=[&](auto __self,int u,auto&c,int f)->void {
        dfn[u]=++c;dep[u]=dep[f]+1;uf[u]=f;
        for(auto&i:gr[u]) if(i!=f) __self(__self,i,c,u);
        rdfn[u]=c;
    };
    dsu qaq(n),tat(n);
    segment sga(n),sgb(n);
    auto ins=[&](auto __self,int u,int w)->void {
        if(qaq.findset(u)==qaq.findset(1)){
            sgb.update(dfn[u],dfn[u],sga.query(dfn[u],dfn[u])+w);
            for(auto&i:gr[u]) __self(__self,i,w);
        }
    };
    [&]{
        auto cnt=-1;
        dfs(dfs,0,cnt,0);
    }();
    for(auto&[w,u,v]:es){
		if(qaq.findset(u)!=qaq.findset(v)){
			if(uf[u]==v) swap(u,v);
			sga.update(dfn[v],dfn[v],w);
            ins(ins,u,w);
		}else{
			u=tat.findset(u);
            v=tat.findset(v);
            w=min({w,sga.query(dfn[u],dfn[u]),sga.query(dfn[v],dfn[v])});
			while(u!=v){
				if(dep[u]<dep[v]) swap(u,v);
				tat.merge(u,uf[u]);
                u=tat.findset(u);
			}
			sga.update(dfn[u],rdfn[u],w);
            sgb.update(dfn[u],rdfn[u],w*2);
		}
	}
    cir(i,1,n) cout<<sgb.query(dfn[i],dfn[i])<<'\n';
    return 0;
}
