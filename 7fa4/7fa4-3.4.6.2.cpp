#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
template<typename T>
using arr=unordered_map<int,T>;
vector<arr<arr<int>>> D;
vector<arr<arr<bool>>> vis;
VI a,b;
int dfs(int p=0,int st1=0,int st2=0){
    int ac=p-__builtin_popcount(st1)-
        __builtin_popcount(st2)-1;
    if(p>=D.size()) return 0;
    auto&d=D[p][st1][st2];
    if(vis[p][st1][st2]) return d;
    vis[p][st1][st2]=true;
    //从队头加入
    d=max(d,dfs(p+1,st1|(1<<p),st2));
    //从队尾加入
    d=max(d,dfs(p+1,st1,st2|(1<<p)));
    //弹出
    auto update=[&](int s1,int s2){
        const int n=D.size();
        int px=0,ax=ac;
        for(int i=n-1;~i;--i) if(s1&(1<<i)){
            s1^=(1<<i);px+=b[(++ax)]*a[i];
            d=max(d,dfs(p+1,s1,s2)+px);
        }
        cir(i,0,n) if(s2&(1<<i)){
            s2^=(1<<i);px+=b[(++ax)]*a[i];
            d=max(d,dfs(p+1,s1,s2)+px);
        }
    };
    //从队尾加入且弹出
    update(st1,st2|(1<<p));
    //队头加入及弹出
    update(st1|(1<<p),st2);
    return d;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;a.resize(n),b.resize(n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    D.resize(n);vis.resize(n);
    cout<<dfs()<<'\n';
    return 0;
}
