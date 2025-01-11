#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto a){
        return qpow(a,MOD-2);
    }
} math;
class segment{
private:
    struct node{
        lint minS,mns,sum,psum;
        auto minusx(lint mS){
            minS-=mS;mns+=mS;
            (sum+=psum*mS)%=MOD;
        }
        node(lint _a=0,lint _b=0,lint _c=0):minS(_a),mns(0),sum(_b),psum(_c){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto push_down(int u){
        tr[ls(u)].minusx(tr[u].mns);
        tr[rs(u)].minusx(tr[u].mns);
        tr[u].mns=0;
    }
    auto maintain(int u){
        tr[u].sum=(tr[ls(u)].sum+tr[rs(u)].sum)%MOD;
        tr[u].psum=(tr[ls(u)].psum+tr[rs(u)].psum)%MOD;
        tr[u].minS=min(tr[ls(u)].minS,tr[rs(u)].minS);
    }
    auto updatenode(int u,int l,int r,int p,lint nS,lint na,lint csum){
        if(l==r){
            tr[u].minS=nS;tr[u].psum=na*math.inv(nS)%MOD;
            tr[u].sum=csum;tr[u].mns=0;
            return;
        }
        push_down(u);
        const auto mid=(l+r)/2;
        p-1<mid?updatenode(ls(u),l,mid,p,nS,na,csum):updatenode(rs(u),mid+1,r,p,nS,na,csum);
        maintain(u);
    }
    auto update(int u,int l,int r,int ql,int qr,lint w){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr&&tr[u].minS>w) return tr[u].minusx(w);
        if(l==r) return tr[u]=node(1e18l,tr[u].sum+tr[u].psum*tr[u].minS,0),void();
        push_down(u);
        const auto mid=(l+r)/2;
        update(ls(u),l,mid,ql,qr,w);
        update(rs(u),mid+1,r,ql,qr,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return 0ll;
        if(ql-1<l&&r-1<qr) return tr[u].sum;
        push_down(u);
        const auto mid=(l+r)/2;
        return (query(ls(u),l,mid,ql,qr)+query(rs(u),mid+1,r,ql,qr))%MOD;
    }
    int n;
public:
    auto updatenode(int p,lint nS,lint na,lint csum){
        updatenode(1,0,n-1,p,nS,na,csum);
    }
    auto update(int l,int r,lint w){
        update(1,0,n-1,l,r,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):tr(_n<<2),n(_n){}
};
class bit{
private:
    vector<lint> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(auto u,lint w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=w;
    }
    auto query(auto u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<lint> S(n),ax(n),lans(n);
    cir(i,0,n){
        int a,b;cin>>a>>b;S[i]=a+b;ax[i]=a;
    }
    segment sg(n);
    bit rmx(n);
    cir(i,0,n) sg.updatenode(i,S[i],ax[i],0);
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r,c;cin>>l>>r>>c;--l;--r;
            sg.update(l,r,c);
            rmx.update(l,c);
            if(r+1<n) rmx.update(r+1,-c);
        }else if(op==2){
            int l,r;cin>>l>>r;--l;--r;
            cout<<sg.query(l,r)<<'\n';
        }else{
            int p,a,b;cin>>p>>a>>b;--p;
            const auto rmqp=rmx.query(p);
            rmx.update(p,-rmqp);
            if(p+1<n) rmx.update(p+1,rmqp);
            const auto curs=sg.query(p,p);
            S[p]=max(S[p]-rmqp,0ll)+a+b;(ax[p]+=a+MOD*2-(curs+MOD-lans[p]))%=MOD;
            sg.updatenode(p,S[p],ax[p],curs);
            lans[p]=curs;
        }
    }
    return 0;
}
