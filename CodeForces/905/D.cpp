#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;
        VI a(n-1),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        sort(a.begin(),a.end());
        priority_queue<int,VI,
            greater<int>> pq;
        for(auto&i:b) pq.push(i);
        lint cnx=0,mx=0;
        for(auto&i:a){
            while((!pq.empty())&&pq.top()<i+1)
                mx=max<lint>(mx,pq.top()),pq.pop();
            if(pq.empty()){
                ++cnx;continue;
            }
            pq.pop();
        }
        if(!pq.empty()) mx=max<lint>(mx,pq.top());
        if(mx>m) cout<<cnx*m<<'\n';
        else cout<<cnx*(mx-1)+(cnx+1)*(m-mx+1)<<'\n';
    }
    return 0;
}
