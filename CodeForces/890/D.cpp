#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct answer{
    int w;
    answer(int _w):w(_w){}
};
struct query{
    int l,r;
    query(int _l,int _r):l(_l),r(_r){}
};
ostream&operator<<(ostream&os,answer a){
    return os<<"! "<<a.w;
}
ostream&operator<<(ostream&os,query q){
    return os<<"? "<<q.l<<' '<<q.r;
}
int bound(int l,int r){
    if(l==r) return l;
    const int mid=(l+r)/2;
    const int ml=bound(l,mid);
    const int mr=bound(mid+1,r);
    return [&](){
        int w1;(ml!=mr-1)?[&](){
            cout<<query(ml,mr-1)<<'\n'<<flush;
            cin>>w1;
        }():((w1=0),void());
        cout<<query(ml,mr)<<'\n'<<flush;
        int w2;cin>>w2;
        return w1==w2;
    }()?mr:ml;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        cout<<answer(bound(1,n))<<'\n'<<flush;
    }
    return 0;
}
