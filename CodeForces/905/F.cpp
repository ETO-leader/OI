#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
template<typename T>
class bit{
private:
    vector<T> a;
    int lowbit(int x){return x&(-x);}
public:
    void update(int x,T w){
        ++x;
        for(;x<a.size();x+=lowbit(x)) a[x]+=w;
    }
    T operator()(int x){
        T res=0;++x;
        for(;x;x-=lowbit(x)) res+=a[x];
        return res;
    }
    bit(int _x):a(_x+1){}
};
struct qry{int l,r,w;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;VI a(n);
        for(auto&i:a) cin>>i;
        int q;cin>>q;vector<qry> qx(q);
        for(auto&[l,r,x]:qx)
            cin>>l>>r>>x,--l,--r;
        bit<lint> b(n+1);set<int> sx;
        int ans=0;
        cir(i,0,q){
            auto&[l,r,x]=qx[i];
            b.update(l,x);b.update(r+1,-x);
            sx.insert(l);sx.insert(r+1);
            while((!sx.empty())&&(!b(*sx.begin())))
                sx.extract(sx.begin());
            while((!sx.empty())&&b(*sx.begin())<0){
                cir(p,ans,i+1){
                    b.update(qx[p].l,-qx[p].w);
                    b.update(qx[p].r+1,qx[p].w);
                }
                ans=i+1;sx.clear();
            }
            
        }
        bit<lint> ansi(n);
        cir(i,0,n)
            ansi.update(i,a[i]-(i?a[i-1]:0));
        cir(i,0,ans){
            ansi.update(qx[i].l,qx[i].w);
            ansi.update(qx[i].r+1,-qx[i].w);
        }
        cir(i,0,n) cout<<ansi(i)<<' ';
        cout<<'\n';
    }
    return 0;
}
