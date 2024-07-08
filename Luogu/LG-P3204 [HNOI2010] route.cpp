#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T,const T MOD>
class matrix{
private:
    vector<vector<T>> mat;
    using lint=long long;
    int x,y;
public:
    auto&operator[](lint x){return mat[x];}
    auto operator*(const matrix<T,MOD>&mt) const{
        matrix<T,MOD> res(x,mt.y);
        cir(i,0,x) cir(j,0,y) cir(k,0,mt.y){
            (res[i][k]+=(mat[i][j]*mt.mat[j][k]))%=MOD;
        }
        return res;
    }
    auto operator^(lint p) const{
        matrix<T,MOD> res(x,y),a=*this;
        cir(i,0,min(x,y)) res[i][i]=1;
        while(p){
            if(p&1) res=res*a;
            a=a*a;p>>=1;
        }
        return res;
    }
    matrix<T,MOD>(int _x=1,int _y=1):x(_x),y(_y),
        mat(_x,vector<T>(_y)){}
};
using lint=long long;
const lint MOD=30031;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k,p;cin>>n>>k>>p;
    vector<int> cx;
    const int _sz=1<<p;
    cir(i,(1<<(p-1)),_sz) if(__builtin_popcount(i)==k){
        cx.push_back(i);
    }
    int idx=cx.size();
    matrix<lint,MOD> C(idx,1),D(idx,idx);
    cir(i,0,idx) cir(j,0,idx){
        auto i1=cx[i],i2=cx[j];
        if(__builtin_popcount(i1^(i2>>1))<=2)
            D[j][i]=1;
    }
    C[idx-1][0]=1;
    cout<<((D^(n-k))*C)[idx-1][0]<<'\n';
    return 0;
}
