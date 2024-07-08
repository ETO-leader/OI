#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<int>> apl(n+1);
    cir(i,0,n) apl[a[i]].push_back(i);
    vector<int> vls,chs;
    cir(i,1,n+1) if(!apl[i].empty()){
        vls.push_back(apl[i].front());
        chs.push_back(apl[i].back());
    }
    sort(vls.begin(),vls.end());
    sort(chs.begin(),chs.end());
    lint ans=1;
    cir(i,0,n+1){
        if(!apl[i].empty()){
            if(apl[i].back()+1!=i) ans=0;
        }
    }
    cir(i,0,(int)(chs.size())){
        auto rk=upper_bound(vls.begin(),
            vls.end(),chs[i])-vls.begin();
        (ans*=(rk-i))%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
