#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct sum2D{
    vector<vector<T>> vT;int _n,_m;
    void add(int x,int y,T v){vT[x][y]+=v;}
    void calc(){
        cir(i,0,_n) cir(j,0,_m){
            if(i) vT[i][j]+=vT[i-1][j];
            if(j) vT[i][j]+=vT[i][j-1];
            if(i&&j) vT[i][j]-=vT[i-1][j-1];
        }
    }
    T get(int x,int y){return (x<0||y<0)?0:vT[x][y];}
    T solve(int l1,int r1,int l2,int r2){
        return get(l2,r2)+get(l1-1,r1-1)-get(l1-1,r2)-get(l2,r1-1);
    }
    sum2D(int __n,int __m):_n(__n),_m(__m),
        vT(__n,vector<T>(__m)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;char c;
    sum2D<int> s(n,n);
    cir(i,0,n) cir(j,0,n){
        cin>>c;
        if(c=='*') s.add(i,j,1);
    }
    s.calc();
    cir(i,0,q){
        int l1,r1,l2,r2;cin>>l1>>r1>>l2>>r2;
        --l1,--l2,--r1,--r2;
        cout<<s.solve(l1,r1,l2,r2)<<'\n';
    }
    return 0;
}