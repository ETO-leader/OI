#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
constexpr int chs=50;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n);
    mt19937 rnd(time(NULL));
    for(auto&i:a) cin>>i;
    unordered_set<lint> prs;
    auto gpr=[&](lint x){
        for(lint i=2;i*i<x+1;++i){
            if(!(x%i)) prs.insert(i);
            while(!(x%i)) x/=i;
        }
        if(x>1) prs.insert(x);
    };
    auto calc=[&](lint p){
        lint ans=0;
        for(auto&i:a){
            const lint k=(i%p);
            ans+=min((i-k?k:p-k),p-k);
        }
        return ans;
    };
    lint ans=n;
    cir(i,0,chs){
        int p=rnd()%n;
        if(a[p]) gpr(a[p]-1);
        gpr(a[p]);gpr(a[p]+1);
    }
    for(auto&i:prs) ans=min(ans,calc(i));
    cout<<ans<<'\n';
    return 0;
}
