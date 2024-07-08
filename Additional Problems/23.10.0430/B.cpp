#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,k;cin>>n>>k;
    vector<lint> v(n);
    priority_queue<lint,
        vector<lint>,greater<lint>> pq;
    for(auto&i:v) cin>>i,pq.push(i);
    lint lastap=0,cnx=0;
    while(cnx<k){
        const lint ad=(pq.top()-lastap)*pq.size();
        if(cnx+ad>=k) break;
        lastap=pq.top();
        pq.pop();cnx+=ad;
    }
    lastap+=(k-cnx)/pq.size();
    const lint adone=(k-cnx)%pq.size();
    int cx=0;
    for(auto&i:v){
        if(i<=lastap) cout<<0<<' ';
        else cout<<i-lastap-
            ((cx+=(i>lastap))<=adone)<<' ';
    }
    cout<<'\n';
    return 0;
}
