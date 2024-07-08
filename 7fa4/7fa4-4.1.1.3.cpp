#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=1e9+7;
vector<int> P;
void init_pr(int n){
    vector<bool> isnp(n+1);
    cir(i,2,n+1){
        if(isnp[i]) continue;
        for(int j=i;j<=n;j+=i) isnp[j]=true;
        P.push_back(i);
    }
}
lint solve(int n){
    init_pr(n);lint ret=1;
    for(auto&i:P){
        int Nx=n;lint c=i,cnt=0;
        while(Nx>=c) cnt+=Nx/c,c*=i;
        (ret*=(2*cnt+1))%=MOD;
    }
    assert(ret>0);
    return ret;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;cout<<solve(n)<<'\n';
    return 0;
}