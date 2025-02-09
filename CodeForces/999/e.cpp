#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxb=30;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m,k;cin>>n>>m>>k;
        vector<lint> a(n),b(m);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i,i=(((1<<maxb)-1)^i);
        vector<int> contains(maxb);
        cir(x,0,maxb) cir(i,0,m) if((b[i]>>i)&1) contains[i]|=(1<<i);
        vector<lint> x(1<<m);
        cir(s,0,(1<<m)) cir(i,0,m) if((s>>i)&1) x[s]|=b[i];
        vector bk(n,vector<lint>(m));
        cir(s,1,(1<<m)){
            const auto cs=popcount((unsigned)(s));
            cir(i,0,n){
                bk[i][cs-1]=max(bk[i][cs-1],a[i]&x[s]);
            }
        }
        cir(i,0,n) for(auto c=m-1;c;--c) bk[i][c]-=bk[i][c-1];
        priority_queue<tuple<lint,int,int>> q;
        cir(i,0,n) q.emplace(bk[i][0],i,0);
        auto ans=accumulate(a.begin(),a.end(),0ll);
        cir(i,0,k){
            const auto[w,p,c]=q.top();q.pop();
            ans-=w;
            if(c+1>m-1) continue;
            q.emplace(bk[p][c+1],p,c+1);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
