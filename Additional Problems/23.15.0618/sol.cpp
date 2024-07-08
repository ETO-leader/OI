#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<int> v(n);
    for(auto&i:v) cin>>i;
    cir(i,0,m){
        int op,l,r;cin>>op>>l>>r;
        --l,--r;
        if(op==1){
            int x;cin>>x;
            cir(i,l,r+1) v[i]&=x;
        }else if(op==2){
            int x;cin>>x;
            cir(i,l,r+1) v[i]|=x;
        }else{
            int mn=numeric_limits<int>::max();
            cir(i,l,r+1) mn=min(mn,v[i]);
            cout<<mn<<'\n';
        }
    }
    return 0;
}
