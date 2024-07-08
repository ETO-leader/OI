#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int U=63;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<int> F(n+1);
    vector<vector<int>> UP(n+1,vector<int>(U+1));
    cir(i,1,n+1) cin>>F[i],UP[i][0]=F[i];
    cir(step,1,U+1) cir(i,1,n+1){
        UP[i][step]=UP[UP[i][step-1]][step-1];
    }
    cir(i,0,m){
        lint p,q;cin>>p>>q;
        for(int i=U;i+1;--i) if(q&(1LL<<i)) p=UP[p][i];
        cout<<p<<endl;
    }
    return 0;
}