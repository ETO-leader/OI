#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class bit{
private:
    vector<int> a;
    constexpr auto lowbit(int x) const{return x&(-x);}
public: 
    auto update(int u,int w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=w;
    }
    auto query(int u){
        auto res=0;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<int> las(n),lasl(n),rg(n+2,-1),lf(n+2,n);
    cir(i,0,n) las[i]=rg[a[i]],lasl[i]=rg[a[i]-1],rg[a[i]]=i;
    for(auto c=n;auto&w:views::reverse(a)) lf[w]=--c;
    struct qry{int l,id;};
    vector<vector<qry>> qs(n);
    cir(i,0,q){
        int l,r;cin>>l>>r;--l;--r;
        qs[r].emplace_back(l,i);
    }
    bit bx(n+7);
    const auto bans=(int)(set(a.begin(),a.end()).size());
    vector ans(q,bans);
    cir(i,0,n){
        if(rg[a[i]]==i){
            const auto l=lasl[i]+1,r=lf[a[i]];
            if(l<r+1) bx.update(l,-1),bx.update(r+1,1);
        }
        if(rg[a[i]+1]<i+1){
            const auto l=las[i]+1,r=min(lf[a[i]+1],i);
            if(l<r+1) bx.update(l,1),bx.update(r+1,-1);
        }
        for(auto&[l,id]:qs[i]) ans[id]+=bx.query(l);
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
