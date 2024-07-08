#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n);
    for(auto&i:a) cin>>i;
    vector<vector<vector<vector<VI>>>>
        D(2,vector<vector<vector<VI>>>(n+7,
        vector<vector<VI>>(n+7,
        vector<VI>(n+7,VI(n+7)))));
    int stp=0;
    D[stp][0][a[0]][0][0]=1;
    cir(i,0,n-1){
        cir(p,i,n) cir(nxt,0,n){
            if(p+nxt>n-1) break;
            cir(c1,0,n) cir(c2,0,n){
                auto&d=D[stp][p][nxt][c1][c2];
                if(!d) continue;
                if(a[i+1]==2){
                    if(i<p){
                        (D[stp^1][p][nxt+1][c1][c2]+=d*(nxt+1))%=MOD;
                        (D[stp^1][p][nxt][c1+1][c2]+=d)%=MOD;
                        if(c1){
                            (D[stp^1][p][nxt][c1-1][c2]+=d*c1)%=MOD;
                        }
                        if(c2){
                            (D[stp^1][p][nxt][c1+1][c2-1]+=d*c2)%=MOD;
                        }
                    }else if((!c1)&&(!c2)&&nxt){
                        (D[stp^1][p+nxt][1][0][0]+=d)%=MOD;
                        (D[stp^1][p+nxt][0][1][0]+=d)%=MOD;
                    }
                }else{
                    if(i<p){
                        if(c1){
                            (D[stp^1][p][nxt+1][c1-1][c2]+=d*c1%MOD*(nxt+1))%=MOD;
                            (D[stp^1][p][nxt][c1][c2]+=d*c1)%=MOD;
                            if(c1>1){
                                (D[stp^1][p][nxt][c1-2][c2]+=d*
                                    ((lint)(c1)*(c1-1)/2%MOD))%=MOD;
                            }
                        }
                        if(c2){
                            (D[stp^1][p][nxt+1][c1+1][c2-1]+=d*c2%MOD*(nxt+1))%=MOD;
                            (D[stp^1][p][nxt][c1+2][c2-1]+=d*c2)%=MOD;
                            if(c2>1){
                                (D[stp^1][p][nxt][c1+2][c2-2]+=
                                    d*((lint)(c2)*(c2-1)/2%MOD))%=MOD;
                            }
                        }
                        if(c1&&c2){
                            (D[stp^1][p][nxt][c1][c2-1]+=d*c1%MOD*c2)%=MOD;
                        }
                        (D[stp^1][p][nxt+1][c1+1][c2]+=d*(nxt+1))%=MOD;
                        (D[stp^1][p][nxt][c1][c2+1]+=d)%=MOD;
                        (D[stp^1][p][nxt+2][c1][c2]+=d*
                            (((lint)(nxt+1)*(nxt+2)/2)%MOD))%=MOD;
                    }else if((!c1)&&(!c2)&&nxt){
                        (D[stp^1][p+nxt][0][0][1]+=d)%=MOD;
                        (D[stp^1][p+nxt][1][1][0]+=d)%=MOD;
                        (D[stp^1][p+nxt][2][0][0]+=d)%=MOD;
                    }
                }
                d=0;
            }
        }
        stp^=1;
    }
    cout<<(D[stp][n-1][0][0][0])<<'\n';
    return 0;
}
