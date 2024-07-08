#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=1e9+7;
class dp{
private:
    vector<VI> D;
    VI states;
    int slv(){
        int stp=0;
        D[stp][0]=1;
        for(auto&i:states){
            stp^=1;
            cir(s,0,(1<<3)){
                D[stp][s]=(D[stp^1][s]+
                    D[stp^1][s^i])%MOD;
            }
        }
        return stp;
    }
public:
    auto join(){return D[slv()][(1<<3)-1];}
    dp(VI st):states(st),D(2,VI(1<<3)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    int n,m;cin>>n>>m;
    vector<vector<bool>> s(m,vector<bool>(n));
    for(auto&i:s){
        int k;cin>>k;
        cir(c,0,k){
            int p;cin>>p;--p;
            i.at(p)=true;
        }
    }
    lint ans=0;
    cir(i,0,n) cir(j,0,n) cir(k,0,n){
        VI vs;
        for(auto&x:s){
            vs.push_back((x[i])+
                (x[j]<<1)+(x[k]<<2));
        }
        (ans+=dp(vs).join())%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
