#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int ninf=1e9+7;
class segment{
private:
    struct node{
        int len,cnx,tag;
        node*ls,*rs;
        void create(){
            ls=new node();rs=new node();
            ls->len=(len+1)/2;rs->len=len-(len+1)/2;
        }
        void push_down(){
            if((!ls)||(!rs)) create();
            ls->tag+=tag;
            if(ls->tag) ls->cnx=ls->len;
            rs->tag+=tag;
            if(rs->tag) rs->cnx=rs->len;
            tag=0;
        }
        void maintain(){
            cnx=ls->cnx+rs->cnx;
        }
        bool isleaf(){return (!ls)&&(!rs);}
        node():len(0),cnx(0),
            tag(0),ls(nullptr),rs(nullptr){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    node*root;
    void __update(node*u,int w){
        u->tag+=w;
        if(u->tag==1&&w==1) u->cnx=u->len;
    }
    void update(node*u,int l,int r,int ql,int qr,int w){
        if(ql<=l&&r<=qr&&u->isleaf()&&(w<0)){
            u->tag+=w;u->cnx=(bool)(u->tag)*(r-l+1);
            return;
        }
        if(ql<=l&&r<=qr) if(w>0||(u->tag>1))
            return __update(u,w);
        u->push_down();
        const int mid=(l+r)/2;
        if(ql<=mid) update(u->ls,l,mid,ql,qr,w);
        if(mid<qr) update(u->rs,mid+1,r,ql,qr,w);
        u->maintain();
        if((!(u->ls->cnx))&&(!(u->rs->cnx))){
            delete u->ls;delete u->rs;
            u->ls=nullptr;u->rs=nullptr;
        }
    }
    int __count(){return root->cnx;}
    int n;
public:
    void update(int l,int r,int w){
        update(root,0,n-1,l,r,w);}
    int count(){return __count();}
    segment(int _n):n(_n){
        root=new node();root->len=_n;
    }
    ~segment(){delete root;}
};
struct query{int p,l,r,w;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<query> q;
    cir(i,0,n){
        int l,r,pl,pr;cin>>l>>pl>>r>>pr;
        q.push_back({pl,l,r-1,1});
        q.push_back({pr,l,r-1,-1});
    }
    segment seg(ninf);lint ans=0;
    sort(q.begin(),q.end(),[](
        query&a,query&b){return a.p<b.p;});
    cir(i,0,q.size()){
        seg.update(q[i].l,q[i].r,q[i].w);
        if(seg.count())
            ans+=1LL*(q[i+1].p-q[i].p)*seg.count();
    }
    cout<<ans<<'\n';
    return 0;
}
