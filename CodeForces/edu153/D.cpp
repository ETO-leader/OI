#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
auto getmin(int&a,int b){
    return a=min(a,b);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;cin>>s;
    const int n=s.size();
    int stp=0;
    vector<vector<VI>> D(2,
        vector<VI>(n+1,VI(n*n+1,n)));
    D[0][0][0]=0;
    cir(i,0,n){
        D[stp^1]=vector<VI>(n+1,VI(n*n+1,n));
        cir(j,0,n+1) cir(k,0,n*n+1){
            if(j<n){
                getmin(D[stp^1][j+1][k],
                    D[stp][j][k]+(s[i]=='1'));
            }
            if(j+k<n*n+1){
                getmin(D[stp^1][j][j+k],
                    D[stp][j][k]+(s[i]=='0'));
            }
        }
        stp^=1;
    }
    const int c0=count(s.begin(),s.end(),'0');
    cout<<D[stp][c0][c0*(n-c0)/2]/2<<'\n';
    return 0;
}