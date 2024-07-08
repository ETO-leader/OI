#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    vector<vector<VI>> D(n+1,
        vector<VI>(2,VI(n+1)));
    D[0][true][0]=1;
    cir(i,0,n) for(auto j:{false,true}){
        cir(w,0,i+1){
            //Choose true
            (D[i+1][true][w]+=
                D[i][j][w]*w)%=MOD;
            //choose false
            (D[i+1][false][w+j]+=
                D[i][j][w]*(k-w))%=MOD;
        }
    }
    cout<<accumulate(D[n][true].begin(),
        D[n][true].end(),(lint)(0))%MOD<<'\n';
    return 0;
}
