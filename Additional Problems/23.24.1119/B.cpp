#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class segment{
private:
    struct node{
        lint mx;int len;
    };
    vector<node> tr;
    static int ls(int x){return x*2;}
    static int rs(int x){return x*2+1;}
    void maintainmx(int u){
        tr[u].mx=max(tr[ls(u)].mx,tr[rs(u)].mx);
    }
    int maintain(lint mx,int u,int l,int r){
        if(tr[u].mx<mx+1) return 0;
        if(l==r) return tr[u].mx>mx;
        const int mid=(l+r)/2;
        if(tr[ls(u)].mx<mx+1)
            return maintain(mx,rs(u),mid+1,r);
        return tr[u].len-tr[ls(u)].len+
            maintain(mx,ls(u),l,mid);
    }
    void update(int u,int l,int r,int p,int w){
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
    struct node_t{int u,l,r;};
    void frts(int u,int l,int r,int ql,
        int qr,vector<node_t>&roots){
        if(ql<l+1&&r-1<qr)
            return roots.push_back({u,l,r});
        const int mid=(l+r)/2;
        if(ql<mid+1) frts(ls(u),l,mid,ql,qr,roots);
        if(qr>mid) frts(rs(u),mid+1,r,ql,qr,roots);
    }
    auto query(int la,int ra){
        vector<node_t> rx;
        frts(1,1,n,la,ra,rx);
        lint mx=0;int res=0;
        for(auto&[u,l,r]:rx){
            res+=maintain(mx,u,l,r);
            mx=max(mx,tr[u].mx);
        }
        return res;
    }
    int n;
public:
    void update(int p,int w){
        update(1,1,n,p,w);}
    int get(int l,int r){return query(l,r);}
    segment(int nx):tr(nx<<2),n(nx){}
};
struct point{int x,y;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;map<int,int,greater<int>> xid;
    vector<point> ps(n);
    for(auto&[x,y]:ps){
        cin>>x>>y;xid.insert({x,0});
    }
    [&](){
        int c=0;for(auto&[x,y]:xid) y=++c;
        sort(ps.begin(),ps.end(),[](point&a,
            point&b){return a.y<b.y;});
    }();
    segment seg(n);int64_t ans=0;
    for(auto&[x,y]:ps){
        ans+=seg.get(xid[x],n);
        seg.update(xid[x],y+1);
    }
    cout<<ans<<'\n';
    return 0;
}
