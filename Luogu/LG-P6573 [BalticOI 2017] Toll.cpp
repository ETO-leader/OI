#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr int _inf=1e9+7;
class matrix{
private:
    vector<vector<int>> a;
    int n;
public:
    auto&operator[](size_t p){return a[p];}
    auto operator*(matrix m) const{
        matrix res(n);
        cir(k,0,n) cir(i,0,n) cir(j,0,n){
            res[i][j]=min(res[i][j],a[i][k]+m[k][j]);
        }
        return res;
    }
    matrix(int _n):a(_n,vector<int>(_n,_inf)),n(_n){}
};
class segment{
private:
    vector<matrix> tr;
    constexpr auto ls(int u) const{return u*2;}
    constexpr auto rs(int u) const{return u*2+1;}
    auto maintain(int u){
        tr[u]=tr[ls(u)]*tr[rs(u)];
    }
    auto update(int u,int l,int r,int p,const matrix&a){
        if(l==r) return tr[u]=a,void();
        const auto mid=(l+r)/2;
        (p-1<mid)?update(ls(u),l,mid,p,a):
            update(rs(u),mid+1,r,p,a);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr) const{
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=(l+r)/2;
        if(qr-1<mid) return query(ls(u),l,mid,ql,qr);
        if(mid<ql) return query(rs(u),mid+1,r,ql,qr);
        return query(ls(u),l,mid,ql,qr)*
            query(rs(u),mid+1,r,ql,qr);
    }
    int n;
public:
    auto update(int p,const matrix a){
        update(1,0,n-1,p,a);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n,int k):tr(_n<<2,matrix(k)),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int k,n,m,q;cin>>k>>n>>m>>q;
    const auto bcks=(n-1)/k;
    vector<matrix> chg(bcks,matrix(k));
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        chg[u/k][u%k][v%k]=min(chg[u/k][u%k][v%k],w);
    }
    segment sgm(bcks,k);
    cir(i,0,bcks) sgm.update(i,chg[i]);
    cir(i,0,q){
        int u,v;cin>>u>>v;
        if(v/k-1<u/k){
            cout<<"-1\n";continue;
        }
        const auto qx=sgm.query(u/k,v/k-1);
        matrix ans(k);ans[0][u%k]=0;
        const auto ansi=(ans*qx)[0][v%k];
        if(ansi>_inf-1){
            cout<<"-1\n";continue;
        }
        cout<<ansi<<'\n';
    }
    return 0;
}
