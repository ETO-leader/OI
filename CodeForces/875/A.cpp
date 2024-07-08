#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        cir(i,0,n){
            int x;cin>>x;
            cout<<(n-x+1)<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
