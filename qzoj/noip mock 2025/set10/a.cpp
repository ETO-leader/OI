#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,t;cin>>n>>m>>t;
    if(n>m) swap(n,m);
    vector<int> a;
    while(n&&m){
        for(auto w=0;w+n<m+1;w+=n){
            cir(i,0,n) a.emplace_back(n); 
        }
        m%=n;
        swap(n,m);
    }
    cout<<a.size()<<'\n';
    if(t){
        for(auto&x:a) cout<<x<<' ';
        cout<<'\n';
    }
    return 0;
}
