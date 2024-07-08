#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e8+7;
template<typename T>
class bit{
private:
    vector<T> a;
    static auto lowbit(int n){
        return n&(-n);
    }
    struct qryk{int p;T x;};
    vector<vector<qryk>> qx;
public:
    auto add(int p,T x){
        qx.push_back(vector<qryk>());
        for(++p;p<a.size();p+=lowbit(p)){
            qx.back().push_back({p,a[p]});
            (a[p]+=x)%=MOD;
        }
    }
    auto qry(int p){
        lint res=0;
        for(++p;p;p-=lowbit(p))
            (res+=(a[p]+MOD))%=MOD;
        return res;
    }
    auto rvk(){
        for(auto&[p,x]:qx.back()){
            a[p]=x;
        }
        qx.pop_back();
    }
    bit(int _n):a(_n+7){}
};
struct qry{lint t,id;};
vector<VI> G;
vector<vector<qry>> qx,tgs;
VI ans;
bit<lint>*bx;
static constexpr auto qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
static constexpr auto inv(lint x){
    return qpow(x,MOD-2);
}
auto dfs(int u,lint a,lint hx=0,int f=0)->void{
    for(auto&[x,y]:tgs[u]){
        if(y>hx) bx->add(x,qpow(a,y-hx));
        else bx->add(x,qpow(inv(a),hx-y));
    }
    const auto wx=qpow(a,hx);
    for(auto&[t,id]:qx[u])
        ans[id]=((bx->qry(t)*wx)%MOD+MOD)%MOD;
    for(auto&i:G[u]) if(i!=f) dfs(i,a,hx+1,u);
    for(auto&[x,y]:tgs[u]) bx->rvk();
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q,a;cin>>n>>q>>a;G.resize(n+1);
    if(a<0) a+=MOD;
    tgs.resize(n+1);qx.resize(n+1);
    ans.resize(q);bx=new bit<lint>(q+7);
    cir(i,2,n+1){
        int f;cin>>f;
        G[f].push_back(i);G[i].push_back(f);
    }
    VI qt;
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int u,x;cin>>u>>x;
            tgs[u].push_back({i,x});
        }else{
            int u;cin>>u;
            qx[u].push_back({i,i});
            qt.push_back(i);
        }
    }
    dfs(1,a);
    for(auto&i:qt) cout<<(ans[i]+MOD)%MOD<<'\n';
    delete bx;
    return 0;
}
