#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=1234567;
class matrix:public vector<vector<lint>>{
public:
    auto operator*(matrix x) const{
        const auto n=(int)(this->size());
        auto res=matrix(n);
        cir(k,0,n) cir(i,0,n) cir(j,0,n) (res[i][j]+=(*this)[i][k]*x[k][j])%=MOD;
        return res;
    }
    auto pow(auto k) const{
        const auto n=(int)(this->size());
        auto res=matrix(n,1),pw=*this;
        while(k){
            if(k&1) res=res*pw;
            pw=pw*pw;k>>=1;
        }
        return res;
    }
    matrix(int _n,lint _v=0){
        this->resize(_n,vector<lint>(_n));
        cir(i,0,_n) (*this)[i][i]=_v;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    matrix f(1<<n);
    cir(s,0,(1<<n)){
        auto dfs=[&](auto __self,int p,int cur){
            if(p==n){
                ++f[s][cur];
                return;
            }
            if((s>>p)&1) return __self(__self,p+1,cur);
            __self(__self,p+1,cur|(1<<p));
            if(p+1<n&&(!((s>>(p+1))&1))) __self(__self,p+2,cur);
        };
        dfs(dfs,0,0);
    }
    cout<<f.pow(m)[0][0]<<'\n';
    return 0;
}
