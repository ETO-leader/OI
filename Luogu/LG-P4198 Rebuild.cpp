#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
static constexpr db eps=1e-18L;
template<typename T>
class segment{
private:
    struct node{
        T mx;int len;
    };
    vector<node> tr;
    static int ls(int u){return u*2;}
    static int rs(int u){return u*2+1;}
    void maintainmx(int u){
        tr[u].mx=max(tr[ls(u)].mx,tr[rs(u)].mx);
    }
    int maintain(T mx,int u,int l,int r){
        if(tr[u].mx<mx+eps) return 0;
        if(l==r) return true;
        const int mid=(l+r)/2;
        if(tr[ls(u)].mx<mx-eps)
            return maintain(mx,rs(u),mid+1,r);
        return tr[u].len-tr[ls(u)].len+
            maintain(mx,ls(u),l,mid);
    }
    void update(int u,int l,int r,int p,T w){
        if(l==r){
            tr[u].mx=w;tr[u].len=1;
            return;
        }
        const int mid=(l+r)/2;
        if(p<mid+1) update(ls(u),l,mid,p,w);
        else update(rs(u),mid+1,r,p,w);
        maintainmx(u);
        tr[u].len=tr[ls(u)].len+maintain(
            tr[ls(u)].mx,rs(u),mid+1,r);
    }
    int n;
public:
    void update(int pos,T w){
        update(1,1,n,pos,w);}
    auto get(){return tr[1].len;}
    segment(int nx):tr(nx<<2),n(nx){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;segment<db> seg(n);
    cir(i,0,m){
        int x,y;cin>>x>>y;
        seg.update(x,(db)(y)/x);
        cout<<seg.get()<<'\n';
    }
    return 0;
}
