#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=987654321;
static constexpr auto maxn=755,maxk=755;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    const auto f=[](){
        vector<vector<vector<int>>> f(2,
            vector<vector<int>>(
            maxk,vector<int>(maxn+1)));
        vector<vector<int>> ans(maxn,vector<int>(maxk));
        ans[0][0]=1;ans[1][0]=1;f[1][1][0]=1;
        cir(i,1,maxn-1){
            swap(f[0],f[1]);
            cir(j,0,maxk) cir(k,0,maxn){
                f[1][j][k]=0;
                if(j) (f[0][j][k]+=f[0][j-1][k])%=MOD;
            }
            cir(j,1,i+2) cir(k,0,maxn){
                if(k-j+2>-1){
                    f[1][j][k]+=f[0][j-1][k-j+2];
                }
                if(k-j+1>-1&&j<i+1){
                    (f[1][j][k]+=f[0][i][k-j+1])%=MOD;
                    (f[1][j][k]+=MOD-f[0][j-1][k-j+1])%=MOD;
                }
                (ans[i+1][k]+=f[1][j][k])%=MOD;
            }
        }
        return ans;
    }();
    while(T--){
        int n,k;cin>>n>>k;
        cout<<f[n][k]<<'\n';
    }
    return 0;
}
