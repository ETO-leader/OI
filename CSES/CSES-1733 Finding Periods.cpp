#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
const ull MOD=1e9+7;
template<typename T,T MODx=MOD>
struct hashing{
    const T hashc=127;
    vector<T> H,P;
    void initP(int n){cir(i,1,n) P[i]=P[i-1]*hashc%MODx;}
    hashing(string s):H(s.size()),P(s.size(),1){
        if(!s.empty()) H[0]=s[0];initP(s.size());
        cir(i,1,s.size()) H[i]=(H[i-1]*hashc+s[i])%MODx;
    }
    T range(int l,int r){
        return (H[r]-(l?H[l-1]*P[r-l+1]:0)+MODx*MODx)%MODx;
    }
    T hash(){return H.back();}
    void push_back(char c){
        H.push_back(H.empty()?c:(H.back()*hashc+c)%MODx);
        P.push_back(P.empty()?1:P.back()*hashc%MODx);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;cin>>s;hashing<ull> H(s),sub("");
    cir(i,0,s.size()){
        int j=0;sub.push_back(s[i]);
        for(;j+i<s.size();j+=(i+1)){
            if(H.range(j,j+i)!=sub.hash()) goto goes;
        }
        if(j==s.size()) cout<<i+1<<' ';
        else if(sub.range(0,s.size()-j-1)
            ==H.range(j,s.size()-1)) cout<<i+1<<' ';
        goes:;
    }
    return 0;
}
