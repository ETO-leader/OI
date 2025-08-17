#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class graph{
private:
    vector<vector<int>> gr;
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto bfs(vector<int> a,vector<int> b){
        queue<int> q;
        const auto n=(int)(gr.size());
        vector<int> dis(n,MOD);
        for(auto&i:a) q.emplace(i),dis[i]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            for(auto&i:gr[u]) if(dis[i]>dis[u]+1){
                dis[i]=dis[u]+1;
                q.emplace(i);
            }
        }
        auto mn=numeric_limits<int>::max();
        for(auto&i:b) mn=min(mn,dis[i]);
        return mn;
    }
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    int p;cin>>p;
    vector<int> x(p);
    for(auto&i:x) cin>>i;
    int q;cin>>q;
    vector<int> y(q);
    for(auto&i:y) cin>>i;
    vector<__uint128_t> prex,prey;
    static constexpr auto c=(__uint128_t)(512251);
    auto w=(__uint128_t)(0);
    for(auto&i:x) prex.emplace_back((w*=c)+=i);
    w=0;
    for(auto&i:y) prey.emplace_back((w*=c)+=i);
    auto l=1,r=min(p,q),ans=0;
    auto check=[&](int mid){
        set<__uint128_t> v;
        auto pw=(__uint128_t)(1);
        cir(i,0,mid) pw*=c;
        cir(i,mid-1,p) v.emplace(prex[i]-(i>mid-1?prex[i-mid]:0)*pw);
        cir(i,mid-1,q) if(v.contains(prey[i]-(i>mid-1?prey[i-mid]:0)*pw)) return true;
        return false;
    };
    while(l-1<r){
        const auto mid=midpoint(l,r);
        check(mid)?((l=mid+1),(ans=mid)):(r=mid-1);
    }
    if(ans){
        cout<<p+q-ans*2<<'\n';
    }else{
        auto sx=set(x.begin(),x.end()),sy=set(y.begin(),y.end());
        graph gr(n+7);
        cir(i,0,n-1) gr.link(a[i],a[i+1]);
        cout<<p+q-2+gr.bfs(vector(sx.begin(),sx.end()),vector(sy.begin(),sy.end()))*2<<'\n';
    }
    return 0;
}
