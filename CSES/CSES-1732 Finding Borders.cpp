#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned __int128;
const ull MOD=1e17+7;
template<typename T>
struct hashing{
    const T hashc=127;
    vector<T> H,P;
    void initP(int n){cir(i,1,n) P[i]=P[i-1]*hashc%MOD;}
    hashing(string s):H(s.size()),P(s.size(),1){
        H[0]=s[0];initP(s.size());
        cir(i,1,s.size()) H[i]=(H[i-1]*hashc+s[i])%MOD;
    }
    T range(int l,int r){return (H[r]-(l?H[l-1]*P[r-l+1]:0)+MOD*MOD)%MOD;}
    T hash(){return H.back();}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;cin>>s;hashing<ull> H(s);
    cir(i,0,s.size()-1) if(H.range(0,i)==
        H.range(s.size()-i-1,s.size()-1)) cout<<i+1<<' ';
    cout<<'\n';
    return 0;
}
