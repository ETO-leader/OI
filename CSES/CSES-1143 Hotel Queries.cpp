#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T,class comp=less<T>, 
    const T _inf=(T)(1e9+7)>
class segment{
private:
    vector<int> val;int _n;
    T change(int u,int l,int r,int s,int v){
        if(l==s&&r==s){val[u]=v;/*cout<<u<<' '<<l<<' '<<r<<' '<<val[u]<<'\n';*/return val[u];}
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        val[u]=min((mid<s?change(rs,mid+1,r,s,v):
            change(ls,l,mid,s,v)),(mid<s?val[ls]:val[rs]),comp());
        //cout<<u<<' '<<l<<' '<<r<<' '<<val[u]<<' '<<_inf<<'\n';
        return val[u];
    }
    int quary(int u,int l,int r,T k){
        if(l==r) return l;
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        return (min(val[ls],k,comp())==val[ls]?quary(ls,l,mid,k):quary(rs,mid+1,r,k));
    }
public:
    segment(int __n):val(4*__n,_inf),_n(__n){}
    void change(int s,int v){change(1,1,_n,s,v);}
    int quary(int k){return quary(1,1,_n,k);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q,ki;cin>>n>>q;vector<int> v(n);
    segment<int,greater<int>,0> seg(n+1);
    cir(i,0,n) cin>>v[i],seg.change(i+1,v[i]);
    cir(i,0,q){
        cin>>ki;auto q=seg.quary(ki);
        cout<<(q==n+1?0:q)<<' '<<flush;
        if(q!=n+1) v[q-1]-=ki;
        seg.change(q,v[q-1]);
    }
    cout<<'\n';
    return 0;
}