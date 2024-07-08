#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
vector<ull> H,P;
const ull hashc=127;
void init(const string&s){
    H.clear(),P.clear();
    int n=s.size();
    H.resize(n),P.resize(n);
    H[0]=s.front();P[0]=1;
    cir(i,1,n) H[i]=H[i-1]*hashc+s[i],P[i]=P[i-1]*hashc;
}
inline bool comp(const ull&u,const int l,const int r){
    return u==(H[r]-((l?H[l-1]:0)*P[r-l+1]));
}
const int alpha_sum=27;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        string s;cin>>s;init(s);
        const int n=s.size();
        vector<char> GL(n),GR(n);
        vector<vector<char>> AT(n,vector<char>(alpha_sum));
        map<char,int> cnts;
        cir(i,0,n){
            GL[i]=(i?GL[i-1]:0)+((cnts[s[i]]^=1)?1:-1);
            cir(j,0,alpha_sum) AT[i][j]=(i?AT[i-1][j]:0)+(j>=GL[i]);
        }
        cnts.clear();
        for(int i=n-1;(i+1);--i) GR[i]=(i==n-1?0:GR[i+1])+
            ((cnts[s[i]]^=1)?1:-1);
        ull ans=0;
        cir(i,1,n-1){
            const ull hashs=H[i];
            for(int j=i;j<n-1;(j+=(i+1))){
                if(!comp(hashs,j-i,j)) break;
                ans+=AT[i-1][GR[j+1]];
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}