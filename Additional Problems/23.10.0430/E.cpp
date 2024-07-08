#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;string s;cin>>n>>s;
    vector<VI> D(n,VI(n,_inf));
    cir(i,0,n){
        D[i][i]=1;
        if(i) D[i][i-1]=0;
    }
    cir(len,1,n) cir(i,0,n-len){
        const int j=i+len;
        auto&d=D[i][j];
        d=min(D[i+1][j],D[i][j-1])+1;
        cir(p,i,j+1){
            if(p!=i&&s[i]==s[p])
                d=min(d,D[i+1][p-1]+D[p][j]);
            if(p!=j&&s[j]==s[p])
                d=min(d,D[i][p]+D[p+1][j-1]);
        }
    }
    cout<<D[0][n-1]<<'\n';
    return 0;
}
