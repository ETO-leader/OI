#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct heapnode{
    lint len,w;
    lint calc_t(int wx) const{
        return (len/wx)*(len/wx)*(wx-(len%wx))
            +(len/wx+1)*(len/wx+1)*(len%wx);
    }
    lint calc() const{
        return calc_t(w)-calc_t(w+1);
    }
    bool operator<(const heapnode&hp) const{
        return calc()<hp.calc();
    }
    heapnode(lint _len,lint _w=1):
        len(_len),w(_w){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    priority_queue<heapnode> pq;
    cir(i,0,n){
        int x;cin>>x;pq.push(heapnode(x));
    }
    cir(i,0,k-n){
        auto f=pq.top();pq.pop();++f.w;
        pq.push(f);
    }
    lint ans=0;
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        ans+=f.calc_t(f.w);
    }
    cout<<ans<<'\n';
    return 0;
}
