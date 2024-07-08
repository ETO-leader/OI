#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int a,b,c;cin>>a>>b>>c;
        cout<<(a+(c&1)>b?"First":"Second")<<'\n';
    }
    return 0;
}
