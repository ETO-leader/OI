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
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s1,s2;cin>>s1>>s2;int ans=0;
    auto H1=hashing<ull>(s1);auto H2=hashing<ull>(s2).hash();
    cir(i,0,s1.size()-s2.size()+1)
        ans+=H1.range(i,i+s2.size()-1)==H2;
    cout<<ans<<'\n';
    return 0;
}
