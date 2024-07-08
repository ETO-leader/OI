#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using __int=__int128_t;
istream&operator>>(istream&is,__int&t){
    string s;is>>s;t=0;
    for(auto&i:s) (t*=10)+=(i-'0');
    return is;
}
ostream&operator<<(ostream&os,__int t){
    if(t>9) os<<(t/10);
    return (os<<(int)(t%10));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    __int n,l;cin>>n>>l;
    priority_queue<__int
        ,vector<__int>,greater<__int>> pq;
    __int cnx=0,ans=0;
    cir(i,0,n){
        __int p;cin>>p;cnx+=p;
        pq.push(p);
    }
    if(cnx<l) pq.push(l-cnx);
    while(pq.size()>1){
        auto t1=pq.top();pq.pop();
        auto t2=pq.top();pq.pop();
        ans+=(t1+t2);pq.push(t1+t2);
    }
    cout<<ans<<'\n';
    return 0;
}
