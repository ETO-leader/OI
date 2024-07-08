#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        if(k>(n-1)*4){
            cout<<n*2-2+(k-(n-1)*4)<<'\n';
        }else{
            cout<<(k+1)/2<<'\n';
        }
    }
    return 0;
}
