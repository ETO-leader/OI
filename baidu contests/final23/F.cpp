#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,abm,mmx")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr lint _inf=1e18+7;
vector<VI> G;
template<class comp>
class matrix{
private:
    array<array<lint,107>,107> mat;
    int nx,mx;
    static auto&gmin(lint&a,const lint b){
        return a=min(a,b,comp());
    }
public:
    auto&operator[](size_t x){return mat[x];}
    auto operator*(matrix m) const{
        assert(mx==m.nx);
        matrix res(nx,m.mx);
        if(comp()(-1,0)==true) cir(i,0,nx){
            cir(j,0,m.mx){
                res[i][j]=_inf;
            }
        }
        cir(k,0,mx) cir(i,0,nx) cir(j,0,m.mx){
            if(mat[i][k]>_inf-1||m[k][j]>_inf-1)
                continue;
            gmin(res[i][j],mat[i][k]+m[k][j]);
        }
        return res;
    }
    auto&operator*=(matrix m){
        return (*this)=(*this)*m;
    }
    auto operator^(lint x){
        auto res=*this,k=*this;--x;
        while(x){
            if(x&1) res*=k;
            k*=k;x>>=1;
        }
        return res;
    }
    matrix(int _n,int _m):nx(_n),mx(_m){
        memset(mat.begin(),0,sizeof(mat));
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    matrix<less<lint>> mna(n,n);
    matrix<greater<lint>> mxa(n,n);
    cir(i,0,n) cir(j,0,n) mna[i][j]=_inf;
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        if(!mxa[u-1][v-1]){
            mxa[u-1][v-1]=mna[u-1][v-1]=w;
        }
        mxa[u-1][v-1]=max<lint>(mxa[u-1][v-1],w);
        mna[u-1][v-1]=min<lint>(mna[u-1][v-1],w);
    }
    cir(i,0,n) cir(j,0,n){
        mxa[i][j]=max(mxa[i][j],mxa[j][i]);
        mna[i][j]=min(mna[i][j],mna[j][i]);
    }
    cir(i,0,q){
        int u,v,k;cin>>u>>v>>k;--u,--v;
        matrix<less<lint>> stx(n,n);
        matrix<greater<lint>> stk(n,n);
        cir(i,0,n) cir(j,0,n) stx[i][j]=_inf;
        cir(i,0,n) cir(j,0,n) stk[i][j]=-_inf;
        stx[u][u]=stk[u][u]=0;
        auto ans1=[&](){
            auto r=stx*(mna^k);
            auto res=numeric_limits<lint>::max();
            cir(i,0,n) res=min(res,r[i][v]);
            return res;
        }(),ans2=[&](){
            auto r=stk*(mxa^k);
            auto res=(lint)(0);
            cir(i,0,n) res=max(res,r[i][v]);
            return res;
        }();
        if(ans1>_inf-1) cout<<"-1 -1\n";
        else cout<<ans1<<' '<<ans2<<'\n';
    }
    return 0;
}
