#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x;cin>>n>>x;
    vector<int> D(x+1),p(n),m(n);
    for(auto&i:m) cin>>i;
    for(auto&i:p) cin>>i;
    cir(i,0,n){
        for(int v=x;v>=m[i];--v)
            D[v]=max(D[v],D[v-m[i]]+p[i]);
    }
    cout<<*max_element(D.begin(),D.end())<<'\n';
    return 0;
}