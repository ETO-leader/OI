#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct dsu{
    vector<T> F,siz,Mt;int Time;
    vector<pair<T,T>> ops;
    dsu(T n):F(n),Mt(n),siz(n,1),Time(0){
        iota(F.begin(),F.end(),0);
        iota(Mx.begin(),Mx.end(),0);
    }
    T findset(int x){return x==F[x]?x:findset(F[x]);}
    void merge()
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;dsu<int> ds(n+1);
    
    return 0;
}