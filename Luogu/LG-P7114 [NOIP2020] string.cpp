#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
typedef unsigned long long ull;
const ull hashc=127;
vector<ull> Hash,P;
void init(string&s){
    Hash.clear();P.clear();
    int n=s.size();P.resize(n);
    Hash.resize(n);
    P[0]=1;Hash[0]=s.front();
    cir(i,1,n) P[i]=P[i-1]*hashc,Hash[i]=Hash[i-1]*hashc+s[i];
}
inline ull has(int l,int r){
    return Hash[r]-(l?Hash[l-1]:0)*P[r-l+1];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        string s;cin>>s;init(s);
        int n=s.size();
        vector<vector<int>> hx(n,vector<int>(27));
        map<char,bool> Aps;
        vector<int> hk(n),hw(n);
        cir(i,0,n){
            hk[i]=(i?hk[i-1]:0)+((Aps[s[i]]^=1)==1?1:-1);
            cir(j,0,27) hx[i][j]=(i?hx[i-1][j]:0)+(j>=hk[i]);
        }
        Aps.clear();
        for(int i=n-1;i+1;--i){
            hw[i]=(i==n-1?0:hw[i+1])+((Aps[s[i]]^=1)==1?1:-1);
        }
        ull ans=0;
        cir(i,1,n-1){
            const int A=i+1,F=n-1,FX=i-1;
            for(int j=i;j<F;j+=A){
                if(has(0,i)!=has(j-i,j)) break;
                ans+=hx[FX][hw[j+1]];
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}