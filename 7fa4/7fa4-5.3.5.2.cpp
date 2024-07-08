#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
static constexpr int mxsiz=1e6+7;
template<typename _Ty,typename _Tc>
class hash_pair{
private:
    hash<_Ty> hf;hash<_Tc> hg;
public:
    auto operator()(const pair<_Ty,_Tc>&p) const{
        return (hf(p.first)<<8)^hg(p.second);
    }
};
class ac_automaton{
private:
    unordered_map<pair<int,int>,
        int,hash_pair<int,int>> tr;
    vector<VI> sx,id;VI fx;
    int cnt,rt;
    auto allocm(){return ++cnt;}
    auto check(int u,unordered_set<int>&s,
        unordered_set<int>&inq){
        while(u){
            if(inq.count(u)) return;
            inq.insert(u);
            for(auto&i:id[u]) s.insert(i);
            u=fx[u];
        }
    }
public:
    auto insert(const VI x,int sid){
        int u=rt;
        for(auto&i:x){
            if(!tr.count({u,i})){
                tr[{u,i}]=allocm();
                sx[u].push_back(i);
            }
            u=tr[{u,i}];
        }
        id[u].push_back(sid);
    }
    auto init(){
        queue<int> q;q.push(rt);
        while(!q.empty()){
            auto u=q.front();q.pop();
            for(auto&i:sx[u]){
                int v=fx[u];
                while(v&&(!tr.count({v,i}))) v=fx[v];
                if(u) fx[tr[{u,i}]]=tr[{v,i}];
                q.push(tr[{u,i}]);
            }
        }
    }
    auto check(const VI x){
        int u=rt;unordered_set<int> res,inq;
        for(auto&i:x){
            while(u&&(!tr.count({u,i}))) u=fx[u];
            u=tr[{u,i}];
            check(u,res,inq);
        }
        return res;
    }
    ac_automaton(int siz):sx(siz),
        fx(siz),id(siz),rt(0),cnt(0){}
};
auto strvec(string s){
    VI res;res.reserve(s.size());
    for(auto&i:s) res.push_back(i-'a');
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;ac_automaton ac(mxsiz);
    vector<VI> csc(n);
    cir(i,0,n){
        int c,x;cin>>c;
        cir(k,0,c) cin>>x,csc[i].push_back(x);
        cin>>c;csc[i].push_back(114514);
        cir(k,0,c) cin>>x,csc[i].push_back(x);
    }
    cir(i,0,q){
        int c;cin>>c;VI a(c);
        for(auto&x:a) cin>>x;
        ac.insert(a,i);
    }
    ac.init();
    VI cnt(n),ans(q);
    cir(i,0,n){
        auto cks=ac.check(csc[i]);
        cnt[i]=cks.size();
        for(auto&x:cks) ++ans[x];
    }
    for(auto&i:ans) cout<<i<<'\n';
    for(auto&i:cnt) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
