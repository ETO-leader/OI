#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
struct matrix{
    vector<vector<T>> mat;T MOD;int x,y;
    matrix<T>(int _x=1,int _y=1,T _MOD=1):
        mat(_x,vector<T>(_y)),x(_x),y(_y),MOD(_MOD){}
    auto&operator[](lint x){return mat[x];}
    auto operator*(const matrix<T>&mt) const{
        matrix<T> ret(x,mt.y,MOD);
        cir(i,0,x) cir(j,0,y) cir(k,0,mt.y){
            (ret[i][k]+=(mat[i][j]*mt.mat[j][k]))%=MOD;
        }
        return ret;
    }
    auto operator^(T tms) const{
        tms--;
        matrix<T> ret=*this,a=*this;
        while(tms){
            if(tms&1) ret=ret*a;
            a=a*a;tms>>=1;
        }
        return ret;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint d,n,m;
    while(cin>>d>>n>>m&&d&&n&&m){
        vector<lint> v(d);
        matrix<lint> D(d,1,m),A(d,d,m);
        cir(i,0,d){
            cin>>v[i],v[i]%=m;A[0][i]=v[i];
            if(i) A[i][i-1]=1;
        }
        cir(i,0,d) cin>>D[d-i-1][0];
        if(n<=d){
            cout<<D[d-n][0]<<endl;
            continue;
        }
        matrix<lint> ans=(A^(n-d))*D;
        cout<<ans[0][0]<<endl;
    }
    return 0;
}