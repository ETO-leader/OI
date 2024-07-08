#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    const int k=(n*2+1)/3;
    int x=1;
    cir(i,0,k){
        if(x>k) x=2;
        cout<<i+1<<' '<<x<<'\n';
        x+=2;
    }
    return 0;
}
