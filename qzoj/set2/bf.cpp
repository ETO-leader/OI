#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
auto Rorate(vector<int>&A,int r){
    vector<int> B=A;
    for(auto&i:A) B.emplace_back(i);
    cir(i,0,(int)(A.size())) A[i]=B[(int)(A.size())-r+i];
}
auto SolveII(vector<int> A,vector<int> ID,int R){
    const auto n=(int)(A.size());
    auto ans=0ll;
    cir(i,0,n){
        ans += A[(min(ID[i], ID[i+1]) - R * i % n + n) % n] - A[(max(ID[i], ID[i+1]) + 1 - R * i % n + n) % n];
    }
    return ans;
}
auto solve(vector<int> A,vector<int> ID,int r){
    // for(auto&i:A) clog<<i<<' ';
    const auto n=(int)(A.size());
    auto sum=0ll;
    cir(i,0,n){
        auto index = min(ID[i], ID[i+1]);
        sum = sum + A[index];
        Rorate(A, r);
    }
    // clog<<"--> ";
    // for(auto&i:A) clog<<i<<' ';
    // clog<<'\n';
    for(auto&i:A) i=-i;
    cir(i,0,n){
        auto index = max(ID[i], ID[i+1]);
        index = index + 1;
        sum = sum + A[index];
        Rorate(A, r);
    }
    // clog<<sum<<": "<<SolveII(A,ID,r)<<": ";
    // for(auto&i:ID) clog<<i<<' ';
    // clog<<'\n'<<'\n';
    return sum;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,r;cin>>n>>r;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<int> ID(n+1);
    auto dfs=[&](auto __self,int p){
        if(p==n+1) return solve(a,ID,r);
        auto res=-_infl;
        cir(i,0,n-1){
            ID[p]=i;
            res=max(res,__self(__self,p+1));
        }
        return res;
    };
    // clog<<"!! "<<solve(a,{0,0,1,0},r)<<'\n';
    cout<<dfs(dfs,0)<<'\n';
    return 0;
}
