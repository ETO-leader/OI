#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static const int nk=2e5+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n);
    for(auto&i:a) cin>>i;
    bitset<nk> D,res;D[0]=true;
    cir(i,0,n){
        D|=(D<<a[i]);
        res[i]=D[i];
        D[i]=false;
    }
    cir(i,n,(n<<1)) res[i]=D[i];
    lint ans=0,sum=0;
    cir(i,0,(n<<1)){
        if(i<n) sum+=a[i];
        if(res[i]) ans=max(ans,sum-i);
    }
    cout<<ans<<'\n';
    return 0;
}
