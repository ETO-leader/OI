#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;const int sqr=sqrt(n)+1;
    vector<vector<lint>> ax(
        sqr,vector<lint>(sqr));
    vector<lint> f(n);f[0]=1;
    cir(i,0,n){
        int x;cin>>x;
        (f[i]+=[&](){
            auto res=0ll;
            cir(w,1,sqr) (res+=ax[w][i%w])%=MOD;
            return res;
        }())%=MOD;
        if(x<sqr){
            (ax[x][i%x]+=f[i])%=MOD;
        }else{
            int nx=i;
            while((nx+=x)<n){
                (f[nx]+=f[i])%=MOD;
            }
        }
    }
    cout<<accumulate(f.begin(),
        f.end(),(lint)(0))%MOD<<'\n';
    return 0;
}
