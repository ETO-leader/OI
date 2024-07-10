#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
template<typename _Ty,typename _Tp>
class hashpair{
public:
    constexpr auto operator()(const pair<_Ty,_Tp>&x) const{
        return (static_cast<size_t>(x.first)<<16)^
            static_cast<size_t>(x.second);
    }
};
class link_cut_tree{
private:
    struct edge_t{
        int delt,id;
        edge_t():delt(_inf),id(-1){}
        edge_t(int dt,int idx):delt(dt),id(idx){}
    };
    vector<edge_t> tr,mn;
    vector<array<int,2>> ch;
    vector<int> f,rev;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u){return rs(f[u])==u;}
    auto maintain(int u){
        mn[u]=min({mn[ls(u)],mn[rs(u)],tr[u]},[&](auto&a,auto&b){
            return a.delt<b.delt;
        });
    }
    auto push_down(int u){
        if(rev[u]){
            swap(ls(u),rs(u));
            rev[ls(u)]^=rev[u];
            rev[rs(u)]^=rev[u];
            rev[u]=false;
        }
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu],c=(int)(getch(u));
        if(nrt(fu)) ch[gu][getch(fu)]=u;
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
        for(down(u);nrt(u);rotate(u));
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);rs(u)=v;maintain(u);
        }
    }
    auto mkrt(int u){
        access(u);splay(u);
        rev[u]^=true;push_down(u);
    }
    auto split(int u,int v){
        mkrt(v);access(u);splay(u);
    }
    auto fndroot(int u){
        for(access(u),splay(u);ls(u);u=ls(u));
        return u;
    }
public:
    auto link(int u,int v){
        mkrt(u);mkrt(v);f[v]=u;
    }
    auto cut(int u,int v){
        split(u,v);ls(u)=f[v]=0;
    }
    auto fndedge(int u,int v){
        split(u,v);splay(u);
        return mn[u];
    }
    auto connected(int u,int v){
        return fndroot(u)==fndroot(v);
    }
    auto initnd(int u,int delt){
        tr[u]={delt,u};
        maintain(u);
    }
    link_cut_tree(int n):tr(n+1,edge_t()),
        mn(n+1,edge_t()),ch(n+1),f(n+1),rev(n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    link_cut_tree lct(n+m+7);
    unordered_map<pair<int,int>,queue<int,list<int>>,hashpair<int,int>> nxtop;
    ostringstream data;
    cir(i,0,m){
        int op,u,v;cin>>op>>u>>v;
        if(u>v) swap(u,v);
        data<<op<<' '<<u<<' '<<v<<'\n';
        if(op!=2) nxtop[{u,v}].push(i);
    }
    istringstream rcin(data.str());
    vector<int> eid(m);
    iota(eid.begin(),eid.end(),n+1);
    vector<pair<int,int>> esi(m);
    vector<int> rm(m);
    unordered_map<pair<int,int>,int,hashpair<int,int>> las;
    for(auto&[a,b]:nxtop) b.push(_inf-7);
    cir(i,0,m){
        int op,u,v;rcin>>op>>u>>v;
        esi[i]={u,v};
        if(!op){
            nxtop[{u,v}].pop();
            lct.initnd(eid[i],nxtop[{u,v}].front());
            las[{u,v}]=eid[i];
            if(u==v) continue;
            if(lct.connected(u,v)) [&](){
                const auto[wx,id]=lct.fndedge(u,v);
                if(wx<nxtop[{u,v}].front()){
                    lct.cut(esi[id-n-1].first,id);
                    lct.cut(esi[id-n-1].second,id);
                    rm[id-n-1]=true;
                }
            }();
            if(!lct.connected(u,v)){
                lct.link(u,eid[i]);
                lct.link(v,eid[i]);
            }else rm[i]=true;
        }else if(op==1){
            nxtop[{u,v}].pop();
            if(u==v) continue;
            const auto lasid=las[{u,v}];
            if(rm[lasid-n-1]) continue;
            lct.cut(u,lasid);
            lct.cut(v,lasid);
        }else{
            cout<<(lct.connected(u,v)?'Y':'N')<<'\n';
        }
    }
    return 0;
}
