#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct seg{int l,r;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<seg> v(n);
    for(auto&[l,r]:v) cin>>l>>r;
    sort(v.begin(),v.end(),
        [](seg&a,seg&b){return a.l<b.l;});
    vector<int> F(n),D(n);
    [&](){
        int p=n-1;
        for(int i=n-1;~i;--i){
            while(v[p].l-v[i].r+1>k) --p;
            F[i]=p;
        }
    }();
    deque<int> qx;qx.push_back(0);
    cir(i,1,n){
        while(!qx.empty()&&F[qx.front()]<i-1)
            qx.pop_front();
        D[i]=D[qx.front()]+1;
        while(!qx.empty()&&D[qx.back()]>=D[i])
            qx.pop_back();
        qx.push_back(i);
    }
    while(!qx.empty()&&F[qx.front()]<n-1)
        qx.pop_front();
    cout<<D[qx.front()]+1<<'\n';
    return 0;
}
