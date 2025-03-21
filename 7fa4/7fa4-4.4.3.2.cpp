#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class segment{
private:
    struct node{
        lint sum,mul,add;
        int len;
        auto addnum(auto x){(sum+=len*x)%=MOD;(add+=x)%=MOD;}
        auto mulnum(auto x){(sum*=x)%=MOD;(mul*=x)%=MOD;(add*=x)%=MOD;}
        node():sum(0),mul(1),add(0),len(0){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    enum updtype{addtag,multag};
    auto push_down(int u){
        tr[ls(u)].mulnum(tr[u].mul);
        tr[rs(u)].mulnum(tr[u].mul);
        tr[ls(u)].addnum(tr[u].add);
        tr[rs(u)].addnum(tr[u].add);
        tr[u].mul=1;tr[u].add=0;
    }
    auto maintain(int u){
        tr[u].sum=(tr[ls(u)].sum+tr[rs(u)].sum)%MOD;
    }
    auto build(int u,int l,int r){
        tr[u].len=r-l+1;
        if(l==r) return;
        const auto mid=(l+r)/2;
        build(ls(u),l,mid);
        build(rs(u),mid+1,r);
    }
    template<updtype tp>
    auto update(int u,int l,int r,int ql,int qr,lint x){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return (tp==addtag?tr[u].addnum(x):tr[u].mulnum(x));
        push_down(u);
        const auto mid=(l+r)/2;
        push_down(u);
        update<tp>(ls(u),l,mid,ql,qr,x);
        update<tp>(rs(u),mid+1,r,ql,qr,x);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return 0ll;
        if(ql-1<l&&r-1<qr) return tr[u].sum;
        const auto mid=(l+r)/2;
        push_down(u);
        return (query(ls(u),l,mid,ql,qr)+query(rs(u),mid+1,r,ql,qr))%MOD;
    }
    int n;
public:
    auto add(int l,int r,lint x){
        update<addtag>(1,0,n-1,l,r,x);
    }
    auto mul(int l,int r,lint x){
        update<multag>(1,0,n-1,l,r,x);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):n(_n),tr(_n<<2){build(1,0,_n-1);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;segment sg(n);
    cir(i,0,n){
        int w;cin>>w;sg.add(i,i,w);
    }
    cir(i,0,m){
        int op;cin>>op;
        if(!op){
            int l,r;cin>>l>>r;--l;--r;
            cout<<sg.query(l,r)<<'\n';
        }else if(op==1){
            int l,r;lint w;cin>>l>>r>>w;--l;--r;
            sg.add(l,r,w);
        }else if(op==2){
            int l,r;lint w;cin>>l>>r>>w;--l;--r;
            sg.mul(l,r,w);
        }
    }
    return 0;
}
