#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto ups=21;
vector<vector<int>> gr,up;
vector<int> ord,inx,oux;
auto dfs(int u,int f=0)->void{
    inx[u]=ord.size();
    ord.push_back(u);
    up[u][0]=f;
    cir(i,1,ups) up[u][i]=up[up[u][i-1]][i-1];
    for(auto&i:gr[u]) if(i!=f) dfs(i,u);
    oux[u]=ord.size();
    ord.push_back(u);
}
auto isancestor(int u,int v){
    return inx[u]<inx[v]+1&&oux[u]>oux[v]-1;
}
auto lca(int u,int v){
    if(isancestor(u,v)) return u;
    for(auto i=ups-1;~i;--i) if(up[u][i]){
        if(!isancestor(up[u][i],v)) u=up[u][i];
    }
    return up[u][0];
}
auto init(const int n){
    up.resize(n+1,vector<int>(ups));
    gr.resize(n+1);inx.resize(n+1);oux.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,q;cin>>n>>m>>q;init(n);
    vector<lint> v(m),w(n);
    for(auto&i:v) cin>>i;
    for(auto&i:w) cin>>i;
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    vector<int> c(n+1);
    cir(i,1,n+1) cin>>c[i],--c[i];
    dfs(1);
    struct qry{int l,r,t;};
    vector<qry> qs;
    vector<pair<int,int>> upd(q,{-1,-1});
    cir(i,0,q){
        int tp,u,v;cin>>tp>>u>>v;
        if(!tp) upd[i]={u,v-1};
        else if(isancestor(u,v)) qs.push_back({inx[u],inx[v],i});
        else if(isancestor(v,u)) qs.push_back({inx[v],inx[u],i});
        else if(oux[u]<inx[v]) qs.push_back({oux[u],inx[v],i});
        else qs.push_back({oux[v],inx[u],i});
    }
    const auto sqr=(int)(pow(n,0.667));
    sort(qs.begin(),qs.end(),[&](auto&a,auto&b){
        return a.l/sqr==b.l/sqr?
            (a.r/sqr==b.r/sqr?a.t<b.t:a.r<b.r)
            :a.l<b.l;
    });
    map<int,lint> ans;
    vector<int> cnt(n+1),cntc(m);
    auto ansi=0ll;
    auto updr=[&](int p){
        const auto idx=ord[p];
        cnt[idx]^=true;
        if(cnt[idx]){
            ansi+=v[c[idx]]*w[cntc[c[idx]]];
            ++cntc[c[idx]];
        }else{
            ansi-=v[c[idx]]*w[--cntc[c[idx]]];
        }
    };
    auto updt=[&](int p){
        auto&[u,cx]=upd[p];
        if(u<0) return;
        if(!cnt[u]) return swap(c[u],cx);
        ansi-=v[c[u]]*w[--cntc[c[u]]];
        swap(c[u],cx);
        ansi+=v[c[u]]*w[cntc[c[u]]];
        ++cntc[c[u]];
    };
    auto l=0,r=-1,id=-1;
    for(auto&[ql,qr,qid]:qs){
        while(id<qid) updt(++id);
        while(id>qid) updt(id--);
        while(r<qr) updr(++r);
        while(l>ql) updr(--l);
        while(r>qr) updr(r--);
        while(l<ql) updr(l++);
        const auto ux=ord[l],vx=ord[r];
        const auto lc=lca(ux,vx);
        auto ad=0ll;
        if(lc!=ux&&lc!=vx) ad=v[c[lc]]*w[cntc[c[lc]]];
        ans[qid]=ansi+ad;
    }
    for(auto&[a,b]:ans) cout<<b<<'\n';
    return 0;
}
