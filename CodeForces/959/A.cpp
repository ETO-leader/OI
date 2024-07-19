#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;
        vector a(n,vector<int>(m));
        for(auto&i:a) for(auto&j:i) cin>>j;
        if(n==1&&m==1) return cout<<"-1\n",void();
        for(auto&i:a){
            for(auto&j:i) cout<<(j%(n*m))+1<<' ';
            cout<<'\n';
        }
    }();
    return 0;
}
