#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    struct node{
        int l,r,w;
        auto operator<(const node x) const{
            return l<x.l;
        };
        node(int _l,int _r,int _w):l(_l),r(_r),w(_w){}
    };
    set<node> px;
    map<int,int> cnt;
    cir(i,0,n) px.emplace(i,i,i),++cnt[i];
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int x,c;cin>>x>>c;--x;--c;
            auto ux=prev(px.upper_bound(node(x,-1,-1)));
            auto[l,r,w]=*ux;
            cnt[w]-=r-l+1;
            cnt[c]+=r-l+1;
            px.erase(ux);
            px.emplace(l,r,c);
            ux=prev(px.upper_bound(node(x,-1,-1)));
            if(ux!=px.begin()&&prev(ux)->w==c){
                l=prev(ux)->l;
                px.erase(prev(ux));
                ux=prev(px.upper_bound(node(x,-1,-1)));
                px.erase(ux);
                px.emplace(l,r,c);
                ux=prev(px.upper_bound(node(x,-1,-1)));
            }
            if(next(ux)!=px.end()&&next(ux)->w==c){
                r=next(ux)->r;
                px.erase(next(ux));
                ux=prev(px.upper_bound(node(x,-1,-1)));
                px.erase(ux);
                px.emplace(l,r,c);
            }
        }else{
            int c;cin>>c;--c;
            cout<<cnt[c]<<'\n';
        }
    }
    return 0;
}
