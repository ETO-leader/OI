#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class segment{
private:
    vector<int> add,mx;
    static int ls(int u){return u*2;}
    static int rs(int u){return u*2+1;}
    auto maintain(int u){
        mx[u]=max(mx[ls(u)],mx[rs(u)]);
    }
    auto update(int u,int l,int r,int p,int x){
        if(l==r) return mx[u]=x,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,x):update(rs(u),mid+1,r,p,x);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return -_inf;
        if(ql-1<l&&r-1<qr) return mx[u];
        const auto mid=(l+r)/2;
        return max(query(ls(u),l,mid,ql,qr),query(rs(u),mid+1,r,ql,qr));
    }
    int n;
public:
    auto update(int p,int x){
        update(1,0,n-1,p,x);
    }
    auto query(int l,int r){
        if(l>r) return -_inf;
        return query(1,0,n-1,l,r);
    }
    segment(int _n):n(_n),mx(_n<<2,-_inf){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,q;cin>>n>>q;vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<int> pre(n,-1),nxt(n),las(n+1);
        cir(i,0,n) pre[i]=las[a[i]],las[a[i]]=i;
        ranges::fill(las,0);
        for(auto i=n-1;~i;--i) nxt[i]=las[a[i]],las[a[i]]=i;
        vector<int> vaildl(n);
        segment sg(n);
        auto l=n-1;
        for(auto r=n-1;~r;--r){
            l=min(l,r);
            while(l){
                const auto mx=sg.query(l,nxt[l-1]-1);
                if(mx<nxt[l-1]){
                    --l;
                    if(nxt[l]<r+1) sg.update(l,nxt[l]);
                }else break;
            }
            vaildl[r]=l; 
            if(pre[r]>l-1){
                sg.update(pre[r],-_inf);
            }
        }
        cir(i,0,q){
            int l,r;cin>>l>>r;--l;--r;
            println("{}",(vaildl[r]<l+1)?"YES":"NO");
        }
    }();
    return 0;
}
