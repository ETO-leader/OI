#include<bits/stdc++.h>
#if defined(__linux)
#include<bits/extc++.h>
#else
#include<ext/pb_ds/assoc_container.hpp>
#endif
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename _Ty,class comp=less<int>>
using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
using lint=long long;
static constexpr int _inf=1e9+7;
static constexpr lint ts=1e9;
class segment{
private:
    struct node{
        node*ls,*rs;
        int val,mxn;
        auto push_down(){
            if(ls) ls->val+=val,ls->mxn+=val;
            if(rs) rs->val+=val,rs->mxn+=val;
            val=0;
        }
        auto maintain(){
            mxn=max((ls?ls->mxn:0),(rs?rs->mxn:0));
        }
        node():ls(nullptr),rs(nullptr),val(0),mxn(0){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    node*root;
    auto insert(node*&u,lint l,lint r,lint p,int w){
        if(!u) u=new node();
        if(l==r) return u->mxn=w,void();
        u->push_down();
        const auto mid=(l+r)/2;
        p-1<mid?insert(u->ls,l,mid,p,w):
            insert(u->rs,mid+1,r,p,w);
        u->maintain();
    }
    auto update(node*u,lint l,lint r,lint ql,lint qr,int w){
        if(!u) return;
        if(ql-1<l&&r-1<qr)
            return u->mxn+=w,u->val+=w,void();
        const auto mid=(l+r)/2;
        u->push_down();
        if(ql-1<mid) update(u->ls,l,mid,ql,qr,w);
        if(mid<qr) update(u->rs,mid+1,r,ql,qr,w);
        u->maintain();
    }
    lint n;
public:
    auto insert(lint p,int w){
        insert(root,0,n-1,p,w);
    }
    auto update(lint l,lint r,int w){
        update(root,0,n-1,max<lint>(l,0),r,w);
    }
    auto query(){return root->mxn;}
    segment(lint _n):n(_n),root(nullptr){}
    ~segment(){if(root) delete root;}
};
struct point{int x,y;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,m,k;cin>>n>>m>>k;n*=ts;
    map<lint,vector<lint>> posk;
    unordered_map<lint,lint> posx;
    cir(i,0,m){
        int x,y;cin>>x>>y;
        if(!posx.count(y)) posx[y]=y*ts;
        posk[x].push_back(++posx[y]);
        posk[x+k].size();
    }
    rbt<lint,less_equal<lint>> rb;
    segment sg(n+7);
    auto rpos=[&](lint x){return x*ts;};
    auto ans=0;
    for(auto&[p,x]:posk){
        for(auto&i:posk[p-k]){
            sg.update(rpos(i/ts-k+1),i,-1);
            sg.insert(i,-_inf);
            rb.erase(rb.lower_bound(i-1));
        }
        for(auto&i:x){
            rb.insert(i);
            sg.update(rpos(i/ts-k+1),i,1);
        }
        set<pair<lint,lint>> ps;
        for(auto&i:x){
            ps.insert({i,(int)(rb.order_of_key(
                rpos(i/ts+k))-rb.order_of_key(i))});
        }
        for(auto&[a,b]:ps) sg.insert(a,b);
        ans=max(ans,sg.query());
    }
    cout<<ans<<'\n';
    return 0;
}
