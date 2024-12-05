#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using matrix=vector<vector<uint>>;
static constexpr auto _infu=(uint)(1.5e9+7);
class floyd{
public:
    static auto spmatrix(matrix&f){
        const auto n=(int)(f.size());
        cir(u,0,n) cir(i,0,n) if(f[i][u]<_infu) cir(j,0,n) f[i][j]=min(f[i][j],f[i][u]+f[u][j]);
    }
};
class segment{
private:
    struct node{
        matrix ll,lr,rr;
        auto isinvaild() const{return ll[0][0]>_infu-1;}
        static auto merge(node a,node b){
            if(a.isinvaild()) return b;
            if(b.isinvaild()) return a;
            const auto m=(int)(a.ll.size());
            matrix dis(m*4,vector<uint>(m*4,_infu));
            cir(i,0,m) cir(j,0,m) dis[i][j]=a.ll[i][j];
            cir(i,0,m) cir(j,0,m) dis[i][j+m]=a.lr[i][j];
            cir(i,0,m) cir(j,0,m) dis[j+m][i]=a.lr[i][j];
            cir(i,0,m) cir(j,0,m) dis[i+m][j+m]=a.rr[i][j];
            cir(i,0,m) dis[i+m][i+m*2]=0,dis[i+m*2][i+m]=0;
            cir(i,0,m) cir(j,0,m) dis[i+m*2][j+m*2]=b.ll[i][j];
            cir(i,0,m) cir(j,0,m) dis[i+m*2][j+m*3]=b.lr[i][j];
            cir(i,0,m) cir(j,0,m) dis[j+m*3][i+m*2]=b.lr[i][j];
            cir(i,0,m) cir(j,0,m) dis[i+m*3][j+m*3]=b.rr[i][j];
            floyd::spmatrix(dis);
            auto res=node(m);
            cir(i,0,m) cir(j,0,m) res.ll[i][j]=dis[i][j];
            cir(i,0,m) cir(j,0,m) res.lr[i][j]=dis[i][j+m*3];
            cir(i,0,m) cir(j,0,m) res.rr[i][j]=dis[i+m*3][j+m*3];
            return res;
        }
        static auto invaild_block(const int m){
            auto res=node(m);
            cir(i,0,m) cir(j,0,m) res.ll[i][j]=res.lr[i][j]=res.rr[i][j]=_infu;
            return res;
        }
        node(int m):ll(m,vector<uint>(m)),lr(m,vector<uint>(m)),rr(m,vector<uint>(m)){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto maintain(int u){
        return tr[u]=node::merge(tr[ls(u)],tr[rs(u)]);
    }
    auto update(int u,int l,int r,int p,int mp,uint w){
        if(l==r){
            const auto delta=w-tr[u].ll[mp][mp];
            const auto m=(int)(tr[u].ll.size());
            cir(i,0,mp+1) cir(j,mp,m) tr[u].ll[i][j]+=delta;
            cir(i,0,mp+1) cir(j,mp,m) tr[u].lr[i][j]+=delta;
            cir(i,0,mp+1) cir(j,mp,m) tr[u].rr[i][j]+=delta;
            cir(i,0,mp+1) cir(j,mp,m) tr[u].ll[j][i]+=delta;
            cir(i,0,mp+1) cir(j,mp,m) tr[u].lr[j][i]+=delta;
            cir(i,0,mp+1) cir(j,mp,m) tr[u].rr[j][i]+=delta;
            tr[u].ll[mp][mp]-=delta;
            tr[u].lr[mp][mp]-=delta;
            tr[u].rr[mp][mp]-=delta;
            return;
        }
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,mp,w):update(rs(u),mid+1,r,p,mp,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(qr<l||r<ql||qr<ql) return node::invaild_block((int)(tr[u].ll.size()));
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=(l+r)/2;
        return node::merge(query(ls(u),l,mid,ql,qr),query(rs(u),mid+1,r,ql,qr));
    }
    int n;
public:
    auto update(int x,int y,uint w){
        update(1,0,n-1,x,y,w);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n,int _m):n(_n),tr(_n<<2,node(_m)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;const auto m=6;
    segment sg(n,m);
    cir(i,0,m) cir(j,0,n){
        uint w;cin>>w;sg.update(j,i,w);
    }
    int q;cin>>q;
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int x,y;uint w;cin>>x>>y>>w;--x;--y;
            sg.update(y,x,w);
        }else{
            int lx,ly,rx,ry;cin>>lx>>ly>>rx>>ry;--lx;--rx;--ly;--ry;
            if(ly>ry) swap(lx,rx),swap(ly,ry);
            const auto ql=sg.query(0,ly-1);
            const auto qm=sg.query(ly,ry);
            const auto qr=sg.query(ry+1,n-1);
            matrix dis(m*4,vector<uint>(m*4,_infu));
            cir(i,0,m) cir(j,0,m) dis[i][j]=ql.rr[i][j];
            cir(i,0,m) dis[i][i+m]=0,dis[i+m][i]=0;
            cir(i,0,m) cir(j,0,m) dis[i+m][j+m]=qm.ll[i][j];
            cir(i,0,m) cir(j,0,m) dis[i+m*2][j+m*2]=qm.rr[i][j];
            cir(i,0,m) dis[i+m*2][i+m*3]=0,dis[i+m*3][i+m*2]=0;
            cir(i,0,m) cir(j,0,m) dis[i+m*3][j+m*3]=qr.ll[i][j];
            cir(i,0,m) cir(j,0,m) dis[i+m][j+m*2]=qm.lr[i][j];
            cir(i,0,m) cir(j,0,m) dis[j+m*2][i+m]=qm.lr[i][j];
            floyd::spmatrix(dis);
            cout<<dis[lx+m][rx+m*2]<<'\n';
        }
    }
    return 0;
}
