#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class segment{
private:
    struct node{
        lint sum,add;
        int len;
        auto addnum(auto x){sum+=len*x;add+=x;}
        node():sum(0),add(0),len(0){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto push_down(int u){
        tr[ls(u)].addnum(tr[u].add);
        tr[rs(u)].addnum(tr[u].add);
        tr[u].add=0;
    }
    auto maintain(int u){
        tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum;
    }
    auto build(int u,int l,int r){
        tr[u].len=r-l+1;
        if(l==r) return;
        const auto mid=(l+r)/2;
        build(ls(u),l,mid);
        build(rs(u),mid+1,r);
    }
    auto update(int u,int l,int r,int ql,int qr,lint x){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return tr[u].addnum(x);
        push_down(u);
        const auto mid=(l+r)/2;
        push_down(u);
        update(ls(u),l,mid,ql,qr,x);
        update(rs(u),mid+1,r,ql,qr,x);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return 0ll;
        if(ql-1<l&&r-1<qr) return tr[u].sum;
        const auto mid=(l+r)/2;
        push_down(u);
        return query(ls(u),l,mid,ql,qr)+query(rs(u),mid+1,r,ql,qr);
    }
    int n;
public:
    auto update(int l,int r,lint x){
        update(1,0,n-1,l,r,x);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n):n(_n),tr(_n<<2){build(1,0,_n-1);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    segment tr(n);
    cir(i,0,n){
        int w;cin>>w;tr.update(i,i,w);
    }
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r,x;cin>>l>>r>>x;--l;--r;
            tr.update(l,r,x);
        }else{
            int l,r;cin>>l>>r;--l;--r;
            cout<<tr.query(l,r)<<'\n';
        }
    }
    return 0;
}
