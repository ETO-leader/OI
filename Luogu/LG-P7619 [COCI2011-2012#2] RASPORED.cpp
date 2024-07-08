#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int maxk=1e5+7;
template<typename _Ty>
class bit{
private:
    vector<_Ty> a;
    constexpr auto lowbit(int x){
        return x&(-x);
    }
public:
    auto update(int p,_Ty x){
        for(++p;p<(int)(a.size());p+=lowbit(p)){
            a[p]+=x;
        }
    }
    auto query(int p){
        _Ty res=0;
        for(++p;p;p-=lowbit(p)) res+=a[p];
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<lint> w(n),t(n);
    lint ans=0;
    bit<lint> sum(maxk);bit<int> cnt(maxk);
    auto upd=[&](int p,int nl,int nt){
        ans-=w[p];sum.update(t[p],-t[p]);
        cnt.update(t[p],-1);
        const auto cx=cnt.query(t[p]);
        const auto wx=sum.query(t[p]);
        ans+=t[p]*(n-cx)+wx;
        w[p]=nl;t[p]=nt;
        ans+=w[p];
        const auto cxn=cnt.query(t[p]);
        const auto wxn=sum.query(t[p]);
        ans-=t[p]*(n-cxn)+wxn;
        sum.update(t[p],t[p]);
        cnt.update(t[p],1);
    };
    cnt.update(0,n);
    cir(i,0,n){
        int wi,ti;cin>>wi>>ti;upd(i,wi,ti);
    }
    cout<<ans<<'\n';
    cir(i,0,q){
        int p,nl,nt;cin>>p>>nl>>nt;
        upd(p-1,nl,nt);
        cout<<ans<<'\n';
    }
    return 0;
}
