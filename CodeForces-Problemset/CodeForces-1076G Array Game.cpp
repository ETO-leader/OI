#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class segment{
private:
    struct node{
        vector<vector<int>> f;
        bool rev;
        auto swap(){
            rev^=true;
            std::swap(f[0],f[1]);
        }
        node(int _m):f(2,vector<int>(_m)),rev(false){}
    };
    vector<node> tr;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto mrgn(vector<int> a,vector<int> b){
        vector<int> res(m+1);
        cir(i,0,m+1) res[i]=a[b[i]];
        return res;
    }
    auto push_down(int u){
        if(tr[u].rev){
            tr[ls(u)].swap();tr[rs(u)].swap();
        }
        tr[u].rev=false;
    }
    auto maintain(int u){
        cir(i,0,2){
            tr[u].f[i]=mrgn(tr[ls(u)].f[i],tr[rs(u)].f[i]);
        }
    }
    auto build(int u,int l,int r,vector<int>&wi){
        if(l==r){
            cir(i,0,m) tr[u].f[0][i]=tr[u].f[1][i]=i+1;
            tr[u].f[wi[l]][m]=0;
            tr[u].f[wi[l]^1][m]=m;
            return;
        }
        const auto mid=(l+r)/2;
        build(ls(u),l,mid,wi);
        build(rs(u),mid+1,r,wi);
        maintain(u);
    }
    auto update(int u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return tr[u].swap();
        push_down(u);
        const auto mid=(l+r)/2;
        if(ql-1<mid) update(ls(u),l,mid,ql,qr);
        if(mid<qr) update(rs(u),mid+1,r,ql,qr);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return tr[u].f[0];
        push_down(u);
        const auto mid=(l+r)/2;
        if(qr<mid+1) return query(ls(u),l,mid,ql,qr);
        if(mid<ql) return query(rs(u),mid+1,r,ql,qr);
        return mrgn(query(ls(u),l,mid,ql,qr),
            query(rs(u),mid+1,r,ql,qr));
    }
    int n,m;
public:
    auto update(int l,int r){
        update(1,0,n-1,l,r);
    }
    auto query(int l,int r){
        return !query(1,0,n-1,l,r)[m];
    }
    auto init(vector<int> wi){
        build(1,0,n-1,wi);
    }
    segment(int _n,int _m):
        n(_n),m(_m),tr(_n<<2,node(_m+1)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    segment sg(n,m);
    sg.init([&](){
        vector<long long> res(n);
        for(auto&i:res) cin>>i,i=(!(i&1));
        return vector<int>(res.begin(),res.end());
    }());
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r;long long x;cin>>l>>r>>x;--l;--r;
            if(x&1) sg.update(l,r);
        }else{
            int l,r;cin>>l>>r;--l;--r;
            cout<<sg.query(l,r)+1<<'\n';
        }
    }
    return 0;
}
