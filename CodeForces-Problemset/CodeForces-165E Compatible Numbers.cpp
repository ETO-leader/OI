#include<bits/stdc++.h>
#define cirx(i,k,expr,cnx)\
    for(int i=k;expr;i+=cnx)
using namespace std;
const int MAXM=(1<<22)-1,hbit=22;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<int> D(MAXM+1,-1),v(n);
    for(auto&i:v) cin>>i,D[(~i)&MAXM]=i;
    cirx(i,MAXM,~i,-1){
        cirx(j,0,j<hbit,1)
            D[i]=[&](int p){return D[p]!=-1?
                D[p]:D[i];}(i|(1<<j));
    }
    for(auto&i:v) cout<<D[i]<<' ';
    cout<<'\n';
    return 0;
}