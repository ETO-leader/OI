#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=(int)(1e9+7);
class segment{
private:
    static constexpr auto sumpr(pair<int,int> a,pair<int,int> b){
        return pair(a.first+b.first,a.second+b.second);
    }
    class isegment{
    private:
        struct node{
            node*ls,*rs;
            int sum,cnt;
            auto maintain(){
                sum=0;cnt=0;
                if(ls) sum+=ls->sum,cnt+=ls->cnt;
                if(rs) sum+=rs->sum,cnt+=rs->cnt;
                sum=sum>MOD?sum-MOD:sum;
            }
            node():ls(nullptr),rs(nullptr),sum(0),cnt(0){}
            ~node(){
                if(ls) delete ls;
                if(rs) delete rs;
            }
        };
        node*root;
        auto update(node*&u,int l,int r,int p,int w,int uc){
            if(!u) u=new node();
            if(l==r) return (u->sum+=w+MOD)%=MOD,u->cnt+=uc,void();
            const auto mid=(l+r)/2;
            p-1<mid?update(u->ls,l,mid,p,w,uc):
                update(u->rs,mid+1,r,p,w,uc);
            if(u->ls&&(!u->ls->cnt)){
                delete u->ls;u->ls=nullptr;
            }
            if(u->rs&&(!u->rs->cnt)){
                delete u->rs;u->rs=nullptr;
            }
            u->maintain();
        }
        auto query(node*u,int l,int r,int ql,int qr){
            if((!u)||qr<l||r<ql) return pair(0,0);
            if(ql-1<l&&r-1<qr) return pair(u->sum,u->cnt);
            const auto mid=(l+r)/2;
            const auto[ress,resc]=sumpr(query(u->ls,l,mid,ql,qr),query(u->rs,mid+1,r,ql,qr));
            return pair(ress>MOD?ress-MOD:ress,resc);
        }
        int lim;
    public:
        auto update(int p,int w,int uc){
            update(root,0,lim-1,p,w,uc);
        }
        auto query(int l,int r){
            return query(root,0,lim-1,l,r);
        }
        isegment(int lm):lim(lm),root(nullptr){}
        ~isegment(){if(root) delete root;}
    };
    vector<isegment> sg;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto update(int u,int l,int r,int qp,int p,int w,int uc){
        sg[u].update(p,w,uc);
        if(l==r) return;
        const auto mid=(l+r)/2;
        qp-1<mid?update(ls(u),l,mid,qp,p,w,uc):
            update(rs(u),mid+1,r,qp,p,w,uc);
    }
    auto query(int u,int l,int r,int ql,int qr,int liml,int limr){
        if(qr<l||r<ql||l>r) return pair(0,0);
        if(ql-1<l&&r-1<qr) return sg[u].query(liml,limr);
        const auto mid=(l+r)/2;
        const auto[ress,resc]=sumpr(query(ls(u),l,mid,ql,qr,liml,limr),query(rs(u),mid+1,r,ql,qr,liml,limr));
        return pair(ress>MOD?ress-MOD:ress,resc);
    }
    int n;
public:
    auto update(int qp,int p,int w,int uc){
        update(1,0,n-1,qp,p,w,uc);
    }
    auto query(int l,int r,int liml,int limr){
        return query(1,0,n-1,l,r,liml,limr);
    }
    segment(int _n):n(_n),sg(_n<<2,isegment(_n+7)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;segment sg(n+7);
    vector<pair<int,int>> bs(n);
    for(auto c=-1;auto&[w,p]:bs){
        cin>>p>>w;
        sg.update(++c,--p,w,1);
    }
    auto ans=0ll;
    for(auto c=-1;auto&[w,p]:bs){
        ++c;
        auto[sgs,sgc]=sg.query(c+1,n-1,0,p);
        (ans+=sgs+1ll*sgc*w)%=MOD;
    }
    cir(i,0,m) [&](){
        int a,b;cin>>a>>b;--a;--b;
        if(a>b) swap(a,b);
        if(a==b) return cout<<ans<<'\n',void();
        [&](){
            auto[sgas,sgac]=sg.query(a+1,b-1,0,bs[a].second);
            auto[sgbs,sgbc]=sg.query(a+1,b-1,bs[b].second,n-1);
            (ans+=MOD-(sgas+1ll*sgac*bs[a].first)%MOD)%=MOD;
            (ans+=MOD-(sgbs+1ll*sgbc*bs[b].first)%MOD)%=MOD;
        }();
        [&](){
            auto[sgas,sgac]=sg.query(a+1,b-1,bs[a].second,n-1);
            auto[sgbs,sgbc]=sg.query(a+1,b-1,0,bs[b].second);
            (ans+=sgbs+1ll*sgbc*bs[b].first)%=MOD;
            (ans+=sgas+1ll*sgac*bs[a].first)%=MOD;
        }();
        sg.update(a,bs[a].second,-bs[a].first,-1);
        sg.update(b,bs[b].second,-bs[b].first,-1);
        sg.update(a,bs[b].second,bs[b].first,1);
        sg.update(b,bs[a].second,bs[a].first,1);
        (ans+=MOD+(bs[a].second>bs[b].second?-1:1)*(bs[a].first+bs[b].first))%=MOD;
        swap(bs[a],bs[b]);
        cout<<ans<<'\n';
    }();
    return 0;
}
