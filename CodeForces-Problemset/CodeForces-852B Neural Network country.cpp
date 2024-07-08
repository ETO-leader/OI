#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=1e9+7;
template<int mod>
class matrix{
private:
    vector<VI> mat;
    int nx,mx;
public:
    auto&operator[](size_t x){return mat[x];}
    auto operator*(matrix m) const{
        matrix<mod> res(nx,m.mx);
        cir(k,0,mx) cir(i,0,nx) cir(j,0,m.mx)
            (res[i][j]+=mat[i][k]*m[k][j]%mod)%=mod;
        return res;
    }
    auto operator^(lint x){
        auto res=*this,k=*this;--x;
        while(x){
            if(x&1) res=res*k;
            k=k*k;x>>=1;
        }
        return res;
    }
    matrix(int _n,int _m):
        mat(_n,VI(_m)),nx(_n),mx(_m){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,l,m;cin>>n>>l>>m;
    matrix<MOD> beg(1,m),D(m,m);
    VI w1(n),wx(n),cnx(m),w2(n);
    for(auto&i:w1) cin>>i,i%=m;
    for(auto&i:wx){
        cin>>i;++cnx[i%m];
    }
    for(auto&i:w2) cin>>i,i%=m;
    for(auto&i:w1) ++beg[0][i];
    cir(i,0,m) cir(j,0,m){
        D[i][(i+j)%m]=cnx[j];
    }
    auto rst=(l>2?beg*(D^(l-2)):beg);
    lint ans=0;
    cir(i,0,n){
        const int usx=(wx[i]+w2[i])%m;
        (ans+=rst[0][(m-usx)%m])%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
