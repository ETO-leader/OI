#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int lcmx=720720;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    cir(i,0,n){
        int xi;
        cir(j,0,m){
            cin>>xi;
            cout<<((i&1)^(j&1)?lcmx:lcmx-xi*xi*xi*xi)<<' ';
        }
        cout<<'\n';
    }
    return 0;
}