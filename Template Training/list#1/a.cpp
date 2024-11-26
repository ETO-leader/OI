#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class segment{
private:
    vector<lint> tr,wx;
    constexpr auto ls(auto u){return u*2;}
    constexpr auto rs(auto u){return u*2+1;}
    auto maintain(int u){
        tr[u]=gcd(abs(tr[ls(u)]),abs(tr[rs(u)]));
    }
    auto build(int u,int l,int r,vector<lint>&a){
        if(l==r) return wx[u]=tr[u]=a[l],void();
        const auto mid=(l+r)/2;
        build(ls(u),l,mid,a);
        build(rs(u),mid+1,r,a);
        maintain(u);
    }
    auto update(int u,int l,int r,int p,lint w){
        if(l==r) return wx[u]+=w,tr[u]=abs(wx[u]),void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,w):update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return 0ll;
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=(l+r)/2;
        return gcd(abs(query(ls(u),l,mid,ql,qr)),abs(query(rs(u),mid+1,r,ql,qr)));
    }
    int n;
public:
    auto init(vector<lint> a){
        build(1,0,n-1,a);
    }
    auto update(int p,lint w){
        update(1,0,n-1,p,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):tr(_n<<2),wx(_n<<2),n(_n){}
};
class bit{
private:
    vector<lint> a;
    constexpr auto lowbit(auto u) const{return u&(-u);}
public:
    auto update(int u,lint w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=w;
    }
    auto query(int u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    segment sg(n);
    bit bx(n);
    for(auto i=n-1;i;--i) a[i]-=a[i-1];
    cir(i,0,n) bx.update(i,a[i]);
    sg.init(a);
    cir(i,0,q){
        string op;cin>>op;
        if(op=="C"){
            int l,r;lint d;cin>>l>>r>>d;--l;--r;
            sg.update(l,d);
            if(r+1<n) sg.update(r+1,-d);
            bx.update(l,d);
            if(r+1<n) bx.update(r+1,-d);
        }else{
            int l,r;cin>>l>>r;--l;--r;
            cout<<gcd(abs(bx.query(l)),sg.query(l+1,r))<<'\n';
        }
    }
    return 0;
}
