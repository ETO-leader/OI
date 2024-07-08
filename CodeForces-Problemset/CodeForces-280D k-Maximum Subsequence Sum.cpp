#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,abm,mmx")
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class segment{
private:
    struct node{
        vector<array<array<int,2>,2>> f;
        int sum;
        auto set(const int w){
            cir(i,0,2) cir(j,0,2){
                f[(!i)&&(!j)][i][j]=w;
            }
            sum=w;
        }
        node(int k):f(k+1),sum(0){}
    };
    vector<node> tr;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto mergen(node u,node v){
        const auto k=(int)(u.f.size())-1;
        node res(k);
        cir(x,0,2) cir(y,0,2) cir(w,0,k+1){
            res.f[w][x][y]=numeric_limits<int>::min();
            cir(lw,0,w+1){
                if(lw<w){
                    res.f[w][x][y]=max(res.f[w][x][y],
                        u.f[lw][x][1]+v.f[w-lw-1][1][y]);
                }
                res.f[w][x][y]=max(
                    res.f[w][x][y],u.f[lw][x][0]+v.f[w-lw][0][y]
                );
            }
        }
        cir(w,0,k+1) cir(lw,0,w+1) cir(x,0,2){
            res.f[w][1][x]=max(res.f[w][1][x],u.sum+v.f[w][1][x]);
            res.f[w][x][1]=max(res.f[w][x][1],u.f[w][x][1]+v.sum);
        }
        res.sum=u.sum+v.sum;
        return res;
    }
    auto maintain(int u){
        tr[u]=mergen(tr[ls(u)],tr[rs(u)]);
    }
    auto update(int u,int l,int r,int p,int w){
        if(l==r) return tr[u].set(w);
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,w):
            update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=(l+r)/2;
        if(qr<mid+1) return query(ls(u),l,mid,ql,qr);
        if(mid<ql) return query(rs(u),mid+1,r,ql,qr);
        return mergen(query(ls(u),l,mid,ql,qr),
            query(rs(u),mid+1,r,ql,qr)); 
    }
    auto build(int u,int l,int r,vector<int>&a){
        if(l==r) return tr[u].set(a[l]);
        const auto mid=(l+r)/2;
        build(ls(u),l,mid,a);build(rs(u),mid+1,r,a);
        maintain(u);
    }
    int n;
public:
    auto update(int p,int w){
        update(1,0,n-1,p,w);
    }
    auto query(int l,int r,int k){
        auto f=query(1,0,n-1,l,r);
        auto res=0;
        cir(i,0,k+1) res=max(res,f.f[i][0][0]);
        return res;
    }
    auto build(vector<int> a){
        build(1,0,n-1,a);
    }
    segment(int _n,int k):tr(_n<<2,node(k)),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    segment sg(n,20);
    sg.build(a);
    int q;cin>>q;
    while(q--){
        int op;cin>>op;
        if(!op){
            int p,w;cin>>p>>w;
            sg.update(p-1,w);
        }else{
            int l,r,k;cin>>l>>r>>k;
            cout<<sg.query(l-1,r-1,k)<<'\n';
        }
    }
    return 0;
}
