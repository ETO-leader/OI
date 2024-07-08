#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
template<typename T>
struct hashing{
    const T hashc=127;
    vector<T> H,P;
    void initP(int n){cir(i,1,n) P[i]=P[i-1]*hashc;}
    hashing(string s):H(s.size()),P(s.size(),1){
        H[0]=s[0];initP(s.size());
        cir(i,1,s.size()) H[i]=H[i-1]*hashc+s[i];
    }
    T range(int l,int r){return H[r]-(l?H[l-1]*P[r-l+1]:0);}
    T hash(){return H.back();}
};
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;int n,m;cin>>s>>m;n=s.size();
    hashing<ull> H(s);vector<int> D(n+1),S(m);
    vector<ull> Hv(m);D[0]=1;
    cir(i,0,m) cin>>s,Hv[i]=
        hashing<ull>(s).hash(),S[i]=s.size();
    cir(i,1,n+1) cir(j,0,m){
        if(S[j]<=i&&H.range(i-S[j],i-1)==Hv[j])
            (D[i]+=D[i-S[j]])%=MOD;
    }
    cout<<D[n]<<'\n';
    return 0;
}