#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,w,e;cin>>n>>w>>e;
        int nxmke=0;
        cir(i,0,n-1){
            int wi,ei;cin>>wi>>ei;
            if(wi>w-1) nxmke=max(nxmke,ei);
        }
        cout<<(nxmke>e-1?-1:w)<<'\n';
    }
    return 0;
}
