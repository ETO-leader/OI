#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    map<pair<int,int>,int64_t> a;
    cir(i,0,n){
        int w;cin>>w;
        a.emplace(make_pair(i,i),w);
    }
    auto split=[&](int p){
        if(p>n-1) return a.end();
        auto pr=a.lower_bound({p,-1});
        if(pr->first.first==p) return pr;
        const auto[rg,w]=*prev(pr);
        const auto[l,r]=rg;
        a.erase(prev(pr));
        a.emplace(make_pair(l,p-1),w);
        return a.emplace(make_pair(p,r),w).first;
    };
    set<int64_t> ban;
    auto w=1ll;
    cir(i,0,11) ban.emplace(w),w*=42;
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int p;cin>>p;--p;
            cout<<prev(a.lower_bound({p+1,-1}))->second<<'\n';
        }else if(op==2){
            int l,r,w;cin>>l>>r>>w;--l;--r;
            const auto pr=split(r+1);
            const auto pl=split(l);
            a.erase(pl,pr);
            a.emplace(make_pair(l,r),w);
        }else if(op==3){
            int l,r,x;cin>>l>>r>>x;--l;--r;
            const auto pr=split(r+1);
            const auto pl=split(l);
            auto ok=true;
            do{
                ok=true;
                for(auto p=pl;p!=pr;++p){
                    p->second+=x;
                    ok&=(!ban.count(p->second));
                }
            }while(!ok);
        }
    }
    return 0;
}
