#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using uqint=__uint128_t;
class segment{
private:
    struct node{
        uqint wf,wt;bool rev;
        auto flip(){
            swap(wf,wt);rev^=true;
        }
    };
    vector<node> tr;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto push_down(int u){
        if(tr[u].rev){
            tr[ls(u)].flip();
            tr[rs(u)].flip();
        }
        tr[u].rev=false;
    }
    auto maintain(int u){
        tr[u].wf=tr[ls(u)].wf+tr[rs(u)].wf;
        tr[u].wt=tr[ls(u)].wt+tr[rs(u)].wt;
    }
    auto build(int u,int l,int r,vector<uqint>&a){
        if(l==r) return tr[u].wf=a[l],void();
        const auto mid=(l+r)/2;
        build(ls(u),l,mid,a);
        build(rs(u),mid+1,r,a);
        maintain(u);
    }
    auto flip(int u,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return;
        if(ql-1<l&&r-1<qr) return tr[u].flip();
        const auto mid=(l+r)/2;
        flip(ls(u),l,mid,ql,qr);
        flip(rs(u),mid+1,r,ql,qr);
        maintain(u);
    }
    int n;
public:
    auto flip(int l,int r){
        flip(1,0,n-1,l,r);
    }
    auto query(){return tr[1].wt;}
    segment(vector<uqint> a):n(a.size()-1),
        tr(a.size()<<2){build(1,0,n-1,a);}
};
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int n):f(n){iota(f.begin(),f.end(),0);}
};
class graph{
private:
    vector<vector<int>> gr;
    vector<int> dfn,fnl;
    auto dfs(int u,int&cnt,int f=0)->void{
        dfn[u]=++cnt;
        for(auto&i:gr[u]) if(i!=f) dfs(i,cnt,u);
        fnl[u]=cnt;
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto init(){auto c=-1;dfs(0,c);}
    auto info(int u){
        return pair(dfn[u],fnl[u]);
    }
    graph(int n):gr(n),dfn(n),fnl(n){}
};
using point=complex<long double>;
using vector_t=complex<long double>;
ostream&operator<<(ostream&os,uqint x){
    if(x>9) os<<x/10<<'\n';
    return os<<(int)(x%10);
}
auto crossabs(vector_t a,vector_t b){
    return (uqint)(fabs(roundl((a*conj(b)).real())));
}
auto area(vector<point> ps){
    const auto n=(int)(ps.size());
    auto res=uqint(0);
    cir(i,1,n-1){
        res+=crossabs(ps[i]-ps[0],ps[i+1]-ps[0]);
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    vector<point> ps(n);
    for(auto&i:ps){
        int x,y;cin>>x>>y;
        i=point(x,y)*point(2,0);
    }
    vector<vector<tuple<long double,int,int>>> gr(n);
    vector<tuple<int,int,long double,long double>> es;
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr[u].push_back({arg(ps[v]-ps[u]),v,i*2});
        gr[v].push_back({arg(ps[u]-ps[v]),u,i*2+1});
        es.push_back({u,v,arg(ps[v]-ps[u]),arg(ps[u]-ps[v])});
        es.push_back({v,u,arg(ps[u]-ps[v]),arg(ps[v]-ps[u])});
    }
    cir(u,0,n) sort(gr[u].begin(),gr[u].end());
    map<pair<int,int>,vector<int>> ex;
    vector<uqint> wx(m*2);
    auto cnt=0;
    vector<int> nxt(m*2);
    for(auto c=-1;auto&[u,v,argi,rargi]:es){
        clog<<u<<' '<<v<<' '<<argi<<' '<<rargi<<'\n';
        ++c;
        auto nxtlb=lower_bound(
            gr[v].begin(),gr[v].end(),tuple(rargi,-1,-1));
        if(nxtlb==gr[v].begin()) nxtlb=gr[v].end();
        nxtlb=prev(nxtlb);
        nxt[c]=nxtlb-gr[v].begin();
    }
    vector<bool> vis(m*2);
    function<void(int,vector<int>&)> dfs=[&](int u,vector<int>&vise){
        const auto v=nxt[u];
        vis[u]=true;
        vise.push_back(u);
        if(vis[get<2>(gr[get<1>(es[u])][v])]) return;
        dfs(get<2>(gr[get<1>(es[u])][v]),vise);
    };
    cir(i,0,m*2){
        if(!vis[i]){
            vector<int> vise;
            dfs(i,vise);
            vector<point> pq;
            for(auto&i:vise){
                auto&[u,v,argi,rargi]=es[i];
                ex[{u,v}].push_back(cnt);
                ex[{v,u}].push_back(cnt);
                pq.push_back(ps[u]);
            }
            ++cnt;
            wx[cnt]=area(pq);
        }
    }
    const auto rt=max_element(wx.begin(),wx.end());
    //graph tr(cnt+1);
    //dsu ds(cnt+1);
    //wx.resize(cnt+1);
    //auto rooted=false;
    //set<pair<int,int>> chs;
    //for(auto&[a,b]:ex){
    //    if(a.first>a.second) continue;
    //    if(b.size()>1){
    //        const auto u=b[0],v=b[1];
    //        if(ds.findset(u)!=ds.findset(v)){
    //            tr.insert(u,v);ds.merge(u,v);
    //            chs.insert({u,v});
    //            chs.insert({v,u});
    //        }
    //    }else if(!rooted){
    //        ex[a].push_back(0);
    //        ex[{a.second,a.first}].push_back(0);
    //        tr.insert(0,b[0]);
    //        chs.insert({0,b[0]});
    //        chs.insert({b[0],0});
    //    }
    //}
    //tr.init();
    //vector<uqint> ux(cnt+1);
    //cir(i,0,cnt+1) ux[tr.info(i).first]=wx[i];
    //segment sg(ux);
    //auto change=[&](int u,int v){
    //    const auto[du,ru]=tr.info(u);
    //    const auto[dv,rv]=tr.info(v);
    //    if(du<dv) sg.flip(dv,rv);
    //    else sg.flip(du,ru);
    //};
    //uqint las=0;
    //cir(i,0,k){
    //    int c;cin>>c;(c+=(las%n))%=n;
    //    vector<int> p(c);
    //    for(auto&i:p) cin>>i,(i+=(las%n))%=n;
    //    cir(i,0,c){
    //        if(ex[{p[i],p[(i+1)%n]}].size()>1){
    //            change(ex[{p[i],p[(i+1)%n]}][0],ex[{p[i],p[(i+1)%n]}][1]);
    //        }
    //    }
    //    const auto qx=sg.query();
    //    const auto g=gcd(qx,16);
    //    cout<<(las=qx/g)<<' '<<16/g<<'\n';
    //}
    return 0;
}
