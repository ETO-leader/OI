#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=998244353;
using VI=vector<int>;
struct person{int p,q;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    vector<vector<VI>> D(2,
        vector<VI>(k+1,VI(n+1)));
    vector<person> P(n);
    //Inputing
    for(auto&i:P) cin>>i.p,--i.p;
    for(auto&i:P) cin>>i.q,--i.q;
    sort(P.begin(),P.end(),
        [](person&a,person&b){return a.p<b.p;});
    //DP and print
    cout<<[&](){
        int step=0,mn=n;
        D[0][0][mn]=1;
        cir(i,0,n){
            step^=1;
            cir(i,0,n+1) D[step][0][i]=0;
            D[step][0][(mn=min(mn,P[i].q))]=1;
            cir(v,1,k+1) cir(j,0,n+1){
                auto&d=D[step][v][j];d=0;
                if(j<P[i].q){
                    (d+=D[step^1][v][j])%=MOD;
                }else if(j==P[i].q){
                    cir(p,j+1,n+1)
                        (d+=D[step^1][v][p])%=MOD;
                }else{
                    (d+=D[step^1][v-1][j])%=MOD;
                }
            }
        }
        int res=0;
        cir(i,0,n+1) (res+=D[step][k][i])%=MOD;
        return res;
    }()<<'\n';
    return 0;
}
