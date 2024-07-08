#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
istream&operator>>(istream&is,VI&v){
    for(auto&i:v) is>>i;sort(v.begin(),v.end());
    return is;
}
struct HeapNode{
    int v,x;
    bool operator<(const HeapNode&Hp) const{
        return v>Hp.v;
    }
};
VI merge(VI&A,VI&B,int k){
    priority_queue<HeapNode> pq;
    for(auto&i:A) pq.push({i+B.front(),0});
    VI ret;
    cir(i,0,k){
        auto f=pq.top();pq.pop();
        ret.push_back(f.v);
        if(f.x<k-1) pq.push({f.v+B[f.x+1]-B[f.x],f.x+1});
    }
    return ret;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;
    while(cin>>n){
        vector<int> A(n),B(n);
        cin>>A;
        cir(i,0,n-1) cin>>B,A=merge(A,B,n);
        cout<<A[0];cir(i,1,n) cout<<' '<<A[i];
        cout<<'\n';
    }
    return 0;
}