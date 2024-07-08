#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int maxai=5e5+7;
template<typename T>
class segment{
private:
    struct node{
        __gnu_pbds::gp_hash_table<T,int> um;
        node*ls,*rs;
        bool candel(){
            return um.empty()&&(!(ls||rs));
        }
        void insert(T w){um[w]++;}
        void del(T w){
            --um[w];if(um[w]<1) um.erase(w);
        }
        node():ls(nullptr),rs(nullptr){}
        ~node(){assert(!ls);assert(!rs);um.clear();}
    };
    node*root;
    node*into(node*&u){
        if(!u) u=new node();
        return u;
    }
    void insert(node*u,int l,int r,int ql,int qr,T w){
        if(ql<=l&&r<=qr) return u->insert(w);
        const int mid=(l+r)/2;
        if(mid>=ql) insert(into(u->ls),l,mid,ql,qr,w);
        if(mid<qr) insert(into(u->rs),mid+1,r,ql,qr,w);
    }
    void erase(node*u,int l,int r,int ql,int qr,T w){
        if(ql<=l&&r<=qr) return u->del(w);
        const int mid=(l+r)/2;
        if(mid>=ql&&u->ls) erase(u->ls,l,mid,ql,qr,w);
        if(mid<qr&&u->rs) erase(u->rs,mid+1,r,ql,qr,w);
        if(u->ls&&u->ls->candel()){
            delete u->ls;u->ls=nullptr;}
        if(u->rs&&u->rs->candel()){
            delete u->rs;u->rs=nullptr;}
    }
    T count(node*u,int l,int r,int ql,int qr){
        if(!(u->um.empty())) return u->um.begin()->first;
        T res=0;const int mid=(l+r)/2;
        if(mid>=ql&&u->ls) res=count(u->ls,l,mid,ql,qr);
        if(res) return res;
        if(mid<qr&&u->rs) res=count(u->rs,mid+1,r,ql,qr);
        return res;
    }
    int n;
public:
    void insert(int l,int r,T w){insert(root,0,n,l,r,w);}
    void erase(int l,int r,T w){erase(root,0,n,l,r,w);}
    T count(int l,int r){return count(root,0,n,l,r);}
    segment(int _n):n(_n){root=new node();}
};
auto init_pre_nxt(int n,vector<int>&v){
    vector<int> pre(v.size()),nxt(v.size());
    unordered_map<int,int> um;
    cir(i,1,n+1) pre[i]=um[v[i]],um[v[i]]=i;
    um.clear();
    for(int i=n;i;--i){
        if(um.count(v[i])) nxt[i]=um[v[i]];
        else nxt[i]=n+1;
        um[v[i]]=i;
    }
    return make_pair(pre,nxt);
}
struct insertion{int l,r,w;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n;vector<int> v(n);
    for(auto&i:v) cin>>i;
    v.insert(v.begin(),-1);
    segment<int> seg(maxai);
    auto[pre,nxt]=init_pre_nxt(n,v);
    vector<vector<insertion>> in(n+2),er(n+2);
    cir(i,1,n+1){
        in[pre[i]+1].push_back({i,nxt[i]-1,v[i]});
        er[i+1].push_back({i,nxt[i]-1,v[i]});
    }
    vector<vector<pair<int,int>>> q(n+2);cin>>m;
    cir(i,0,m){
        int l,r;cin>>l>>r;q[l].push_back({r,i});
    }
    vector<int> ans(m);
    cir(i,1,n+2){
        for(auto&[l,r,w]:in[i]) seg.insert(l,r,w);
        for(auto&[l,r,w]:er[i]) seg.erase(l,r,w);
        for(auto&[p,id]:q[i]) ans[id]=seg.count(p,p);
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
