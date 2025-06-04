#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class bit{
private:
    vector<int> a;
    static constexpr auto lowbit(int x){return x&(-x);}
public:
    auto update(int u,int w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]=max(a[u],w);
    }
    auto query(int u){
        auto res=0;
        for(++u;u;u-=lowbit(u)) res=max(res,a[u]);
        return res;
    }
    bit(int _n):a(_n){}
};
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{return f[u]==u?u:f[u]=findset(f[u]);}
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<int>> cur(n,vector<int>(m));
    vector<vector<int>> goal(n,vector<int>(m));
    auto c0=0;
    for(auto&x:cur) for(auto&i:x) cin>>i,c0+=(!i);
    map<int,int> from;
    for(auto c=-1;auto&x:goal) for(++c;auto&i:x) cin>>i,from[i]=c;
    dsu pos(n);
    auto adds=0;
    for(auto c=-1;auto&x:cur) for(++c;auto&i:x) if(i){
        pos.merge(c,from[i]);
        adds+=(from[i]!=c);
    }
    vector<int> full(n,true);
    for(auto c=-1;auto&x:cur){
        ++c;
        if(ranges::count(x,0)) full[pos.findset(c)]=false;
    }
    if(!c0){
        if(cur==goal) cout<<0<<'\n';
        else cout<<-1<<'\n';
    }else{
        auto ans=0;
        cir(i,0,n){
            auto ai=cur[i];
            map<int,int> id;
            auto cnt=0;
            for(auto&i:goal[i]) if(i) id[i]=++cnt;
            for(auto&i:ai) i=id[i];
            auto mx=0,tot=0;
            bit bx(m+7);
            for(auto&i:ai){
                tot+=(i>0);
                if(!i) continue;
                const auto f=bx.query(i)+1;
                mx=max(mx,f);
                bx.update(i,f);
            }
            if(mx<tot){
                const auto fs=pos.findset(i);
                ans+=(tot-mx)+full[fs];
                full[fs]=false;
            }
        }
        cout<<ans+adds<<'\n';
    }
    return 0;
}
