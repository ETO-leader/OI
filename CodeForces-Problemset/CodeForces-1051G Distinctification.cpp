#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxn=2e5+7;
class segment{
private:
    struct node{
        node*ls,*rs;
        lint siz,sum;
        auto maintain(){
            siz=0;sum=0;
            if(ls) siz+=ls->siz,sum+=ls->sum;
            if(rs) siz+=rs->siz,sum+=rs->sum;
        }
        auto merge(node*n,lint&ansg,int l,int r){
            if(l==r) return this;
            const auto mid=(l+r)/2;
            ansg-=(
                (ls?ls->sum:0ll)*(rs?rs->siz:0ll)+
                (n->ls?n->ls->sum:0ll)*(n->rs?n->rs->siz:0ll)
            );
            if(ls&&n->ls) ls=ls->merge(n->ls,ansg,l,mid);
            else if(n->ls) ls=n->ls;
            if(rs&&n->rs) rs=rs->merge(n->rs,ansg,mid+1,r);
            else if(n->rs) rs=n->rs;
            ansg+=(ls?ls->sum:0ll)*(rs?rs->siz:0ll);
            maintain();
            return this;
        }
        node():ls(nullptr),rs(nullptr),siz(0),sum(0){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    node*root;
    auto update(node*&u,int l,int r,int p){
        if(!u) u=new node();
        if(l==r) return u->siz=1,u->sum=p,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(u->ls,l,mid,p):
            update(u->rs,mid+1,r,p);
        u->maintain();
    }
    int n;
public:
    auto update(int p){
        update(root,1,n,p);
    }
    auto link(segment&sg,lint&uans,lint ewa,lint ewb){
        uans-=root->sum*ewa+sg.root->sum*ewb;
        root=root->merge(sg.root,uans,1,n);
        sg.root=nullptr;
        uans+=root->sum*ewa;
    }
    auto empty(){return !root;}
    segment(int _n):n(_n),root(nullptr){}
    ~segment(){if(root) delete root;}
};
class dsu{
private:
    vector<int> f,blc;
public:
    auto findset(int x)->int{
        return f[x]==x?x:f[x]=findset(f[x]);
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        f[v]=u;blc[u]=blc[v];
    }
    auto getbound(int u){
        return blc[findset(u)];
    }
    dsu(int _n):f(_n),blc(_n){
        iota(f.begin(),f.end(),0);
        iota(blc.begin(),blc.end(),0);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;dsu ds(maxn*2+7);
    vector<segment> sg(maxn*2+7,segment(maxn+7));
    auto ans=0ll;
    auto linkn=[&](int u,int v){
        u=ds.findset(u);v=ds.findset(v);
        assert(!sg[u].empty());
        assert(!sg[v].empty());
        ds.merge(u,v);sg[u].link(sg[v],ans,u+1,v+1);
    };
    cir(i,0,n){
        int u,v;cin>>u>>v;--u;
        const auto p=sg[ds.findset(u)].empty()?u:ds.getbound(u)+1;
        ans+=(lint)(p-u)*v;
        sg[p].update(v);
        if(p&&(!sg[ds.findset(p-1)].empty())) linkn(p-1,p);
        if(p<maxn-1&&(!sg[ds.findset(p+1)].empty())) linkn(p,p+1);
        cout<<ans<<'\n';
    }
    return 0;
}
