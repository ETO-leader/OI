#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
using extvector=unordered_map<int,T>;
const int MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k,st=0;cin>>n>>k;vector<int> v(n),ex;
    if(k==1){cout<<0<<'\n';exit(0);}
    vector<extvector<lint>> D(2);
    for(auto&i:v) cin>>i;ex=v;
    ex.insert(ex.begin(),ex.back());ex.pop_back();
    D[st][0]=1;
    cir(i,0,n){
        st^=1;
        cir(j,-n,n+1){
            if(v[i]==ex[i]) D[st][j]=(D[st^1][j]*k)%MOD;
            else D[st][j]=(D[st^1][j-1]+
                D[st^1][j+1]+D[st^1][j]*(k-2))%MOD;
        }
        D[st^1].clear();
    }
    lint ans=0;
    cir(i,1,n+1) (ans+=D[st][i])%=MOD;
    cout<<ans<<endl;
    return 0;
}