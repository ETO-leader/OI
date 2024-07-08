#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    cir(i,0,n){
        int x;cin>>x;
        if(!(x&1)) cout<<x<<' ';
    }
    cout<<'\n';
    return 0;
}
