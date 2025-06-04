#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class segment{
private:
    struct node{
        vector<int> lfp,rgp;
        int mn;
        node():mn(_inf){}
    };
    const int k,n;
    vector<node> tr;
    vector<int> a;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto merge(node nl,node nr){
        auto res=node();
        res.mn=min(nl.mn,nr.mn);
        vector<pair<int,int>> pos;
        for(auto&x:nl.rgp) pos.emplace_back(x,a[x]);
        for(auto&x:nr.lfp) pos.emplace_back(x,a[x]);
        auto l=0;
        vector<int> cnt(k);
        auto vaild=0;
        cir(r,0,(int)(pos.size())){
            vaild+=(!cnt[pos[r].second]);
            ++cnt[pos[r].second];
            while(cnt[pos[l].second]>1) --cnt[pos[l].second],++l;
            if(vaild==k) res.mn=min(res.mn,pos[r].first-pos[l].first+1);
        }
        pos.clear();
        for(auto&x:nl.lfp) pos.emplace_back(x,a[x]);
        for(auto&x:nr.lfp) pos.emplace_back(x,a[x]);
        ranges::fill(cnt,0);
        for(auto&[p,w]:pos) if(!cnt[w]) res.lfp.emplace_back(p),cnt[w]=true;
        ranges::fill(cnt,0);
        pos.clear();
        for(auto&x:nl.rgp) pos.emplace_back(x,a[x]);
        for(auto&x:nr.rgp) pos.emplace_back(x,a[x]);
        for(auto&[p,w]:views::reverse(pos)) if(!cnt[w]) res.rgp.emplace_back(p),cnt[w]=true;
        ranges::reverse(res.rgp);
        return res;
    }
    auto update(int u,int l,int r,int p,int w){
        if(l==r){
            tr[u].lfp=tr[u].rgp=vector{p};
            tr[u].mn=(k==1?1:_inf);
            return;
        }
        const auto mid=midpoint(l,r);
        p-1<mid?update(ls(u),l,mid,p,w):update(rs(u),mid+1,r,p,w);
        tr[u]=merge(tr[ls(u)],tr[rs(u)]);
    }
    auto build(int u,int l,int r,vector<int>&a){
        if(l==r){
            tr[u].lfp=tr[u].rgp=vector{l};
            tr[u].mn=(k==1?1:_inf);
            return;
        }
        const auto mid=midpoint(l,r);
        build(ls(u),l,mid,a);
        build(rs(u),mid+1,r,a);
        tr[u]=merge(tr[ls(u)],tr[rs(u)]);
    }
public:
    auto update(int p,int w){
        a[p]=w;
        update(1,0,n-1,p,w);
    }
    auto build(vector<int> x){
        a=x;
        build(1,0,n-1,x);
    }
    auto cost(){
        return tr[1].mn;
    }
    segment(int _n,int _k):tr(_n<<2,node()),n(_n),k(_k){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k,q;cin>>n>>k>>q;
    segment sg(n,k);
    vector<int> a(n);
    for(auto&i:a) cin>>i,--i;
    sg.build(a);
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int p,w;cin>>p>>w;--p;--w;
            sg.update(p,w);
        }else{
            const auto ans=sg.cost();
            cout<<(ans>n?-1:ans)<<'\n';
        }
    }
    return 0;
}
