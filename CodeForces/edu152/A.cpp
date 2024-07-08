#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int a,b,c;cin>>a>>b>>c;
        cout<<min(a*2-1,(b+c)*2+1)<<'\n';
    }
    return 0;
}
