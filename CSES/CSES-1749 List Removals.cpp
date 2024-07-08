#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T,const int HT=20>
struct BIT{
    vector<T> rk;int _n;
    static inline int lowbit(int x){return x&(-x);}
    void add(int u,T x){
        for(;u<=_n;u+=lowbit(u)) rk[u]+=x;
    }
    T rank(T rkp){
        T nrk=0;
        for(int i=HT;~i;--i){
            if(nrk+(1<<i)<=_n&&rk[nrk+(1<<i)]<rkp)
                nrk+=(1<<i),rkp-=rk[nrk];
        }
        return nrk+1;
    }
    T&operator[](int x){return rk[x];}
    void del(int k){add(k,-1);}
    BIT(int __n):_n(__n-1),rk(__n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    for(auto&i:v) cin>>i;
    BIT<int> B(n+1);
    cir(i,0,n) B[i+1]=BIT<int>::lowbit(i+1);
    cir(i,0,n){
        int pi;cin>>pi;
        auto rk=B.rank(pi);B.del(rk);
        cout<<v[rk-1]<<' '<<flush;
    }
    cout<<'\n';
    return 0;
}