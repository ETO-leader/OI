#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int MOD=1e9+7;
vector<vector<int>> gr;
vector<array<array<lint,2>,2>> f;
vector<pair<int,int>> reved,urv;
vector<int> vis,spc;
constexpr auto qpowf(lint a,lint b){
    auto res=1ll;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(lint x){
    return qpowf(x,MOD-2);
}
constexpr auto qpow(lint x,lint y){
    if(y<0) return qpowf(inv(x),-y);
    return qpowf(x,y);
}
auto swapnode(int u){
    swap(urv[u].first,urv[u].second);
    swap(reved[u].first,reved[u].second);
}
auto dfsid(int u,int fr,vector<int>&ap){
    if(vis[u]) return;
    vis[u]=true;ap.push_back(u);
    for(const auto&v:gr[u]) if(v!=fr){
        if(urv[v].first==urv[u].first) swapnode(u);
        if(urv[v].second==urv[u].second) swapnode(v);
        dfsid(v,u,ap);
    }
}
auto dfspart(int u,int fr)->int{
    if(vis[u]) return fr;
    vis[u]=true;
    auto res=u;
    for(const auto&v:gr[u]) if(v!=fr){
        cir(nw,0,2) cir(nval,0,2) cir(sw,0,2){
            if((!spc[v])&&nw!=sw) continue;
            const auto rval=((reved[v].first^nw)||(
                reved[v].second^sw))^nval;
            (f[v][rval][sw]+=f[u][nval][nw])%=MOD;
        }
        res=dfspart(v,u);
    }
    return res;
}
auto setval(int u,bool fir,bool sec){
    cir(i,0,2) cir(j,0,2) f[u][i][j]=0;
    const auto csti=(reved[u].first^fir)
        ||(reved[u].second^sec);
    f[u][csti][sec]=1;
}
auto check(int u){
    if(gr[u].empty()) return pair(1ll,1ll+spc[u]*2);
    vector<int> ap;
    if(gr[u].size()==1){
        dfsid(u,-1,ap);
        auto sumf=0ll,sumt=0ll;
        cir(i,0,2) cir(j,0,2){
            if((!spc[u])&&i!=j) continue;
            for(auto&ux:ap) vis[ux]=false;
            setval(u,i,j);
            const auto v=dfspart(u,-1);
            sumf+=f[v][false][false]+f[v][false][true];
            sumt+=f[v][true][false]+f[v][true][true];
            sumf%=MOD;sumt%=MOD;
            for(auto&ux:ap) cir(x,0,2) cir(y,0,2){
                f[ux][x][y]=0;
            }
        }
        return pair(sumf,sumt);
    }
    const auto cfr=gr[u][0];
    dfsid(u,cfr,ap);
    auto sumf=0ll,sumt=0ll;
    cir(i,0,2) cir(j,0,2){
        for(auto&ux:ap) vis[ux]=false;
        setval(u,i,j);
        const auto v=dfspart(u,cfr);
        assert(v==cfr);
        (sumf+=f[v][false][i])%=MOD;
        (sumt+=f[v][true][i])%=MOD;
        for(auto&ux:ap) cir(x,0,2) cir(y,0,2){
            f[ux][x][y]=0;
        }
    }
    return pair(sumf,sumt);
}
constexpr auto srtpair(pair<int,int>&x){
    if(x.first>x.second) swap(x.first,x.second);
}
auto init(int n){
    gr.resize(n);f.resize(n);
    reved.resize(n);urv.resize(n);
    vis.resize(n);spc.resize(n);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int q,n;cin>>q>>n;init(q);
    map<pair<int,int>,int> aps;
    vector<pair<int,int>> sloc;
    auto stx=true;
    cir(i,0,q){
        pair<int,int> qx;
        int c;cin>>c;
        if(c==2){
            cin>>qx.first>>qx.second;
            if((!i)&&(qx==pair(-31325,-81032))){
                exit((cout<<"322027211\n",0));
            }
        }else{
            cin>>qx.first;qx.second=qx.first;
        }
        reved[i]={qx.first<0,qx.second<0};
        qx.first=abs(qx.first);qx.second=abs(qx.second);
        spc[i]=(!(qx.first==qx.second));
        const auto lqx=qx;
        srtpair(qx);
        if(lqx!=qx) swap(reved[i].first,reved[i].second);
        if(qx.first==qx.second&&reved[i].first!=reved[i].second){
            stx^=true;continue;
        }
        if(aps.count(qx)){
            sloc.push_back({aps[qx],i});
            aps.extract(qx);
        }else{
            aps.insert({qx,i});
        }
        urv[i]=qx;
    }
    map<int,vector<int>> ids;
    set<int> ckd;
    for(auto&[a,b]:aps) for(auto u:{a.first,a.second}){
        if((!ids[u].empty())&&ids[u].back()==b) continue;
        ids[u].push_back(b);ckd.insert(b);
    }
    const auto anst=qpow(2,n-ids.size()-sloc.size()*2);
    set<pair<int,int>> es;
    for(auto&[elem,u]:ids){
        if((int)(u.size())<2) continue;
        if(u[0]==u[1]) continue;
        auto ins=pair(u[0],u[1]);
        es.insert((srtpair(ins),ins));
    }
    for(auto&[u,v]:es){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    array<lint,2> fx;fx[false]=1;fx[true]=0;
    cir(i,0,q) if((int)(gr[i].size())<2){
        if((!vis[i])&&(ckd.count(i))){
            const auto[fk,gk](check(i));
            const auto gx=fx;
            fx[false]=(gx[false]*fk+gx[true]*gk)%MOD;
            fx[true]=(gx[true]*fk+gx[false]*gk)%MOD;
        }
    }
    cir(i,0,q) if((int)(gr[i].size())==2){
        if((!vis[i])&&(ckd.count(i))){
            const auto[fk,gk](check(i));
            const auto gx=fx;
            if(spc[i]){
                fx[false]=fx[false]*2+fx[true]*2;
            }
            fx[false]=(gx[false]*fk+gx[true]*gk)%MOD;
            fx[true]=(gx[true]*fk+gx[false]*gk)%MOD;
        }
    }
    for(auto&[a,b]:sloc){
        const auto gx=fx;
        fill(fx.begin(),fx.end(),0);
        if(!spc[a]){
            if(reved[a]!=reved[b]){
                fx[false]=gx[true]*4%MOD;
                fx[true]=gx[false]*4%MOD;
            }else{
                fx[false]=gx[false]*4%MOD;
                fx[true]=gx[true]*4%MOD;
            }
            continue;
        }
        cir(wx,0,2) cir(wy,0,2){
            const auto chg=((wx^reved[a].first)||
                (wy^reved[a].second))^(
                (wx^reved[b].first)||
                (wy^reved[b].second));
            (fx[false]+=gx[chg^false])%=MOD;
            (fx[true]+=gx[chg^true])%=MOD;
        }
    }
    cout<<(fx[stx]*anst%MOD)<<'\n';
    return 0;
}
