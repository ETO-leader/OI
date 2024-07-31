#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto maxa=(int)(2e5+7);
class segment{
private:
    struct node{
        node*ls,*rs;
        int cnt;
        node():ls(nullptr),rs(nullptr),cnt(0){}
    };
    vector<node*> mem;
    auto allocm(){
        return mem.push_back(new node()),mem.back();
    }
    auto copy(node*u){
        if(!u) return allocm();
        const auto res=allocm();
        tie(res->ls,res->rs,res->cnt)=tie(u->ls,u->rs,u->cnt);
        return res;
    }
    auto insert(node*&u,int l,int r,int p,int w){
        ++(u=copy(u))->cnt;
        if(l==r) return;
        const auto mid=midpoint(l,r);
        p-1<mid?insert(u->ls,l,mid,p,w):insert(u->rs,mid+1,r,p,w);
    }
    auto rank(node*u,int l,int r,int cnts){
        if(!u) return r;
        // clog<<l<<' '<<r<<' '<<u->cnt<<'\n';
        if(l==r) return l;
        const auto mid=midpoint(l,r);
        if(u->ls&&u->ls->cnt>cnts-1) return rank(u->ls,l,mid,cnts);
        return rank(u->rs,mid+1,r,cnts-(u->ls?u->ls->cnt:0));
    }
    auto count(node*u,int l,int r,int ql){
        if((!u)||l>ql) return 0;
        if(r<ql+1) return u->cnt;
        const auto mid=midpoint(l,r);
        return count(u->ls,l,mid,ql)+count(u->rs,mid+1,r,ql);
    }
    vector<node*> rts;
    int n;
public:
    auto insert(const auto lst){
        rts.push_back(rts.back());
        for(auto&i:lst) insert(rts.back(),0,n-1,i,1);
    }
    auto rank(int v,int cnts){
        // clog<<__FUNCTION__<<' '<<cnts<<'\n';
        return rank(rts[v],0,n-1,cnts);
    }
    auto count(int v,int ql){
        return count(rts[v],0,n-1,ql);
    }
    segment(int _n):n(_n),rts({nullptr}){}
    ~segment(){for(auto&i:mem) delete i;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> a(n);
    for(auto&i:a) cin>>i,i=maxa-i;
    vector<vector<int>> px(maxa+7);
    cir(i,0,n) px[a[i]-1].push_back(i);
    segment sg(n+7);
    for(auto&x:px) sg.insert(x);
    map<int,vector<pair<int,int>>> wx;
    cir(i,0,q){
        int p,k;cin>>p>>k;wx[k].emplace_back(p-1,i);
    }
    vector<string> ans(q);
    for(auto&[w,qx]:wx){
        vector posx({0});
        auto level=maxa,p=0;
        while(p<n){
            --level;
            const auto pre=(p?sg.count(level,p-1):0)+w;
            posx.push_back(p=sg.rank(level,pre)+1);
            // clog<<w<<' '<<p<<'\n';
        }
        for(auto[qp,id]:qx){
            const auto realw=maxa-a[qp];
            ans[id]=((int)(posx.size())<realw+1||posx[realw]>qp)?"YES":"NO";
        }
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
