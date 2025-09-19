#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class segment{
private:
    struct node{
        int mx,mntag,ans;
        auto tag(int tag){
            ans=max(ans,mx-tag);
            mntag=min(mntag,tag);
        }
        node():mx(-_inf),mntag(_inf),ans(-_inf){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto push_down(int u){
        tr[ls(u)].tag(tr[u].mntag);
        tr[rs(u)].tag(tr[u].mntag);
        tr[u].mntag=_inf;
    }
    auto maintain(int u){
        tr[u].mx=max(tr[ls(u)].mx,tr[rs(u)].mx);
        tr[u].ans=max(tr[ls(u)].ans,tr[rs(u)].ans);
    }
    auto update_a(int u,int l,int r,int p,int w){
        if(l==r) return tr[u].mx=w,void();
        const auto mid=(l+r)/2;
        push_down(u);
        p-1<mid?update_a(ls(u),l,mid,p,w):update_a(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    auto update_t(int u,int l,int r,int ql,int qr,int w){
        if(qr<l||r<ql) return;
        if(ql-1<l&&r-1<qr) return tr[u].tag(w);
        const auto mid=(l+r)/2;
        push_down(u);
        update_t(ls(u),l,mid,ql,qr,w);
        update_t(rs(u),mid+1,r,ql,qr,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return -1;
        if(ql-1<l&&r-1<qr) return tr[u].ans;
        const auto mid=(l+r)/2;
        push_down(u);
        return max(query(ls(u),l,mid,ql,qr),query(rs(u),mid+1,r,ql,qr));
    }
    const int n;
public:
    auto update_a(int p,int w){
        update_a(1,0,n-1,p,w);
    }
    auto update_t(int l,int r,int w){
        if(l<r+1) update_t(1,0,n-1,l,r,w);
    }
    auto query(int l,int r){
        return l<r+1?query(1,0,n-1,l,r):-1;
    }
    segment(int _n):n(_n),tr(_n<<2){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<tuple<int,int,int>> a(n);
    for(auto&[x,l,r]:a) cin>>x>>l>>r;
    int q;cin>>q;
    vector<int> ans(q,-1);
    vector<vector<pair<int,int>>> qry(n);
    cir(i,0,q){
        int l,r;cin>>l>>r;--l;--r;
        qry[r].emplace_back(l,i);
    }
    auto calc=[&]{
        segment sg(n);
        vector<vector<int>> tags(n),rtags(n);
        cir(i,0,n){
            const auto&[x,l,r]=a[i];
            for(auto&c:tags[i]) sg.update_a(c,get<0>(a[c]));
            for(auto&c:rtags[i]) sg.update_a(c,-_inf);
            sg.update_t(max(i-r,0),i-l,x);
            if(i+l<n) tags[i+l].emplace_back(i);
            if(i+r+1<n) rtags[i+r+1].emplace_back(i);
            for(auto&[ql,id]:qry[i]){
                ans[id]=max(ans[id],sg.query(ql,i));
            }
        }
    };
    calc();
    for(auto&i:a) get<0>(i)=-get<0>(i);
    calc();
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
