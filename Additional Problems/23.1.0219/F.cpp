#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct gcd_tag{
    T operator()(T a,T b) const{
        return __gcd(a,b);
    }
};
template<typename T,class calc>
struct sparsetable{
private:
    vector<vector<T>> ST;
    void init(vector<T>&v){
        int n=v.size();
        int _lg=log2(n);
        calc __calc;
        ST.assign(n,vector<T>(_lg+1));
        cir(i,0,n) ST[i][0]=v[i];
        cir(j,1,_lg+1) cir(i,0,n-(1<<j)+1)
            ST[i][j]=__calc(ST[i][j-1]
                ,ST[i+(1<<(j-1))][j-1]);
    }
public:
    T operator()(int l,int r){
        if(r<l) return 0;
        int _lg=log2(r-l+1);
        calc __calc;
        return __calc(ST[l][_lg],ST[r-(1<<_lg)+1][_lg]);
    }
    sparsetable(vector<T>&v){init(v);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    vector<int> A(n),B(n),Ax(n),Bx(n);
    for(auto&i:A) cin>>i;
    for(auto&i:B) cin>>i;
    cir(i,1,n) Ax[i]=A[i]-A[i-1],Bx[i]=B[i]-B[i-1];
    cir(i,1,n) Ax[i]=abs(Ax[i]),Bx[i]=abs(Bx[i]);
    sparsetable<int,gcd_tag<int>> a(Ax),b(Bx);
    cir(i,0,q){
        int l1,l2,r1,r2;
        cin>>l1>>l2>>r1>>r2;
        cout<<__gcd(b(r1,r2-1),__gcd(a(l1,l2-1),
            A[l1-1]+B[r1-1]))<<'\n';
    }
    return 0;
}
