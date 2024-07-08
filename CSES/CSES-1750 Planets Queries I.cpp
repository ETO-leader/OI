#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int KK=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;int HT=log2(KK)+1;
    vector<VI> UP(HT+1,VI(n+1));
    cir(i,1,n+1) cin>>UP[0][i];
    cir(i,1,HT+1) cir(u,1,n+1)
        UP[i][u]=UP[i-1][UP[i-1][u]];
    cir(i,0,q){
        int u,x;cin>>u>>x;
        cir(i,0,HT+1) if(x&(1<<i)) u=UP[i][u];
        cout<<u<<'\n';
    }
    return 0;
}