#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI flg(n),lim(n);
    try{
        [&](){
            cir(i,0,n) cir(j,i,n){
                int x;cin>>x;
                if(x==1){
                    fill(flg.begin()+i+1,
                        flg.begin()+j+1,true);
                }else if(x){
                    if(i==j) throw -114514;
                    lim[j]=i+1;
                }
            }
            vector<VI> D(n,VI(n));
            D[0][0]=1;
            cir(i,1,n){
                if(!flg[i]) cir(j,0,i)
                    (D[i][i]+=D[i-1][j])%=MOD;
                cir(j,lim[i],i) D[i][j]=D[i-1][j];
            }
            cout<<accumulate(D[n-1].begin(),
                D[n-1].end(),(lint)(0))*2%MOD<<'\n';
        }();
    }catch(int){
        cout<<0<<'\n';
    }
    return 0;
}
