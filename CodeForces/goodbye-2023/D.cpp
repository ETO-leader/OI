#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        if(n==1) return cout<<1<<'\n',void();
        cir(i,1,n/2+1){
            cout<<1;
            cir(x,0,i-1) cout<<0;
            cout<<6;
            cir(x,0,i-1) cout<<0;
            cout<<9;
            cir(x,i*2,n-1) cout<<0;
            cout<<'\n';
        }
        cout<<196;
        cir(i,0,n-3) cout<<0;
        cout<<'\n';
        cir(i,1,n/2+1){
            cout<<9;
            cir(x,0,i-1) cout<<0;
            cout<<6;
            cir(x,0,i-1) cout<<0;
            cout<<1;
            cir(x,i*2,n-1) cout<<0;
            cout<<'\n';
        }
    }();
    return 0;
}
