#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr int MOD=1e9+7;
class segment{
private:
    struct node{
        node*ls,*rs;
        int odd,even,siz;
        auto maintain(){
            odd=0;even=0;siz=0;
            if(ls){
                odd+=ls->odd;even+=ls->even;
                siz+=ls->siz;
            }
            if(rs){
                if(siz&1) odd+=rs->even,even+=rs->odd;
                else odd+=rs->odd,even+=rs->even;
                siz+=rs->siz;
            }
            odd%=MOD;even%=MOD;
        }
        node():ls(nullptr),rs(nullptr),
            odd(0),even(0),siz(0){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    node*root;
    template<const int newsiz,const int k>
    auto update(node*&u,int l,int r,int p){
        if(!u) u=new node();
        if(l==r){
            u->siz=newsiz;u->odd=p*k;u->even=0;
            return;
        }
        const auto mid=(l+r)/2;
        p-1<mid?update<newsiz,k>(u->ls,l,mid,p):
            update<newsiz,k>(u->rs,mid+1,r,p);
        u->maintain();
    }
    int n;
public:
    auto insert(int p){
        update<1,true>(root,0,n-1,p);
    }
    auto extract(int p){
        update<0,false>(root,0,n-1,p);
    }
    auto query() const{
        return root->odd;
    }
    segment(int _n):n(_n),root(nullptr){}
    ~segment(){if(root) delete root;}
};
struct qry{int l,r,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<qry> qs(q);
    for(auto c=0;auto&[l,r,id]:qs) cin>>l>>r,id=c++;
    const auto sqr=(int)(sqrtl(n))+1;
    sort(qs.begin(),qs.end(),[&](auto&a,auto&b){
        return a.l/sqr==b.l/sqr?a.r<b.r:a.l<b.l;
    });
    segment sg(MOD);
    auto ins=[&](int p){
        sg.insert(a[p]);
    };
    auto del=[&](int p){
        sg.extract(a[p]);
    };
    vector<int> ans(q);
    auto l=0,r=-1;
    for(auto&[ql,qr,id]:qs){
        while(r<qr) ins(++r);
        while(l<ql) del(l++);
        while(qr<r) del(r--);
        while(ql<l) ins(--l);
        ans[id]=sg.query();
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
