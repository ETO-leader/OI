#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    cir(i,0,n){
        int x;
        cir(j,0,m){
            cin>>x;
            cout<<(char)((!x)?'.':'A'+(x-1));
        }
        cout<<'\n';
    }
    return 0;
}
