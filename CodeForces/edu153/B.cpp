#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int m,k,k1,k2;cin>>m>>k>>k1>>k2;
        const int use=m/k;
        const int need1=m-use*k;
        if(need1>k1-1){
            cout<<max(use-k2,0)+need1-k1<<'\n';
            continue;
        }
        k1-=need1;
        const int usx=use-k2;
        cout<<max(0,usx-(k1/k))<<'\n';
        continue;
    }
    return 0;
}
