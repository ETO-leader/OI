#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(lint)(1e15+7);
class segment{
private:
    vector<lint> a;
    function<lint(lint)> qry;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto maintain(int u){
        a[u]=a[ls(u)]+a[rs(u)];
    }
    auto update(int u,int l,int r,int p,lint w,lint sign){
        if(l==r) return a[u]+=qry(w)*sign,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,w,sign):
            update(rs(u),mid+1,r,p,w,sign);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return a[u];
        const auto mid=(l+r)/2;
        auto res=0ll;
        if(ql-1<mid) res+=query(ls(u),l,mid,ql,qr);
        if(mid<qr) res+=query(rs(u),mid+1,r,ql,qr);
        return res;
    }
    int n;
public:
    auto update(int p,lint w,lint sign){
        update(1,0,n-1,p,w,sign);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n,function<lint(lint)> _q):
        n(_n),a(_n<<2),qry(_q){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    vector<lint> a(n),b(m),da(n),db(m);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    auto sumq=[](lint x){return x;};
    auto sumsaq=[](lint x){return -x*(x+1)/2+x*x;};
    auto sumatq=[](lint x){return x*(x+1)*(x*2+1)/6-x*x*(x+1)/2;};
    segment sqa(n+m,sumq),sqb(n+m,sumq),
        cqa(n+m,sumq),cqb(n+m,sumq),
        ssqa(n+m,sumsaq),ssqb(n+m,sumsaq),
        stqa(n+m,sumatq),stqb(n+m,sumatq);
    auto opera=[&](int len,int tag){
        sqa.update(len,len,tag);
        ssqa.update(len,len,tag);
        stqa.update(len,len,tag);
        cqa.update(len,1,tag);
    };
    auto operb=[&](int len,int tag){
        sqb.update(len,len,tag);
        ssqb.update(len,len,tag);
        stqb.update(len,len,tag);
        cqb.update(len,1,tag);
    };
    const auto maxr=n+m+7;
    auto ans=1ll*n*m;
    auto querya=[&](int len,int tag){
        opera(len,tag);
        ans+=(ssqb.query(0,len)*len+stqb.query(0,len))*tag;
        ans+=(sqb.query(len+1,maxr)*sumsaq(len)+cqb.query(len+1,maxr)*sumatq(len))*tag;
    };
    auto queryb=[&](int len,int tag){
        operb(len,tag);
        ans+=(ssqa.query(0,len)*len+stqa.query(0,len))*tag;
        ans+=(sqa.query(len+1,maxr)*sumsaq(len)+cqa.query(len+1,maxr)*sumatq(len))*tag;
    };
    set az={-1,n},bz={-1,m};
    auto insa=[&](int p,lint x){
        const auto rx=*az.upper_bound(p),lx=*prev(az.upper_bound(p));
        if((!da[p])&&x){
            querya(rx-max(lx,0),-1);
            az.erase(p);da[p]=x;
            const auto nlx=*prev(az.upper_bound(p));
            querya(p-max(nlx,0),-1);
            querya(rx-max(nlx,0),1);
            return;
        }
        if(da[p]&&(!x)){
            querya(rx-max(lx,0),-1);
            az.insert(p);da[p]=x;
            querya(p-max(lx,0),1);querya(rx-p,1);
            return;
        }
        da[p]=x;
    };
    auto insb=[&](int p,lint x){
        const auto rx=*bz.upper_bound(p),lx=*prev(bz.upper_bound(p));
        if((!db[p])&&x){
            queryb(rx-max(lx,0),-1);
            bz.erase(p);db[p]=x;
            const auto nlx=*prev(bz.upper_bound(p));
            queryb(p-max(nlx,0),-1);
            queryb(rx-max(nlx,0),1);
            return;
        }
        if(db[p]&&(!x)){
            queryb(rx-max(lx,0),-1);
            bz.insert(p);db[p]=x;
            queryb(p-max(lx,0),1);queryb(rx-p,1);
            return;
        }
        db[p]=x;
    };
    [&](){
        cir(i,0,n) da[i]=a[i]-(i?a[i-1]:-_inf);
        cir(i,0,m) db[i]=b[i]-(i?b[i-1]:-_inf);
        auto las=0;
        cir(i,0,n) if(!da[i]) querya(i-las,1),las=i,az.insert(i);
        querya(n-las,1);
        las=0;
        cir(i,0,m) if(!db[i]) queryb(i-las,1),las=i,bz.insert(i);
        queryb(m-las,1);
    }();
    cout<<ans<<'\n';
    cir(i,0,q){
        int t,l,r,x;cin>>t>>l>>r>>x;--l;--r;
        if(t==1){
            insa(l,da[l]+x);
            if(r+1<n) insa(r+1,da[r+1]-x);
        }else{
            insb(l,db[l]+x);
            if(r+1<m) insb(r+1,db[r+1]-x);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
