#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k,cnx=0;cin>>n>>k;
        vector<int> v(n);
        priority_queue<int> pq;
        for(auto&i:v) cin>>i;
        cir(i,1,n){
            cnx+=abs(v[i]-v[i-1]);
            pq.push(abs(v[i]-v[i-1]));
        }
        cir(i,0,k-1) cnx-=pq.top(),pq.pop();
        cout<<cnx<<'\n';
    }
    return 0;
}
