#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    vector<lint> c(4);int q;
    for(auto&i:c) cin>>i;
    cin>>q;
    while(q--){
        vector<lint> d(4);
        for(auto&i:d) cin>>i;
        int s;cin>>s;
        vector<lint> D(s+1);
        D[0]=1;
        cir(i,0,4){
            cir(j,0,s+1)
                if(j>=c[i]) D[j]+=D[j-c[i]];
            for(int j=s;j>=(d[i]+1)*c[i];--j)
                D[j]-=D[j-(d[i]+1)*c[i]];
        }
        cout<<D[s]<<'\n';
    }
    return 0;
}
