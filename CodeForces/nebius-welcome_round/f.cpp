#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class graph{
private:
    vector<vector<int>> gr;
    vector<int> val;
    queue<int> q;
    auto bfs(int s){
        const auto n=(int)(gr.size());
        ranges::fill(val,n+7);
        val[s]=0;q.emplace(s);
        while(!q.empty()){
            const auto u=q.front();q.pop();
            for(auto&i:gr[u]) if(val[i]>val[u]+1){
                val[i]=val[u]+1;q.emplace(i);
            }
        }
        const auto p=(int)(ranges::max_element(val)-val.begin());
        return pair(p,val[p]);
    }
    auto check(int u){
        return bfs(bfs(u).first).second;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto revoke(int u,int v){
        gr[u].pop_back();
        gr[v].pop_back();
    }
    template<const int c>
    auto check(mt19937&eng){
        auto ans=0;
        cir(i,0,c) ans=max(ans,check(uniform_int_distribution<int>(0,(int)(gr.size())-1)(eng)));
        return ans;
    }
    graph(int _n):gr(_n),val(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,q;cin>>n>>m>>q;
    graph gr(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    mt19937 eng(251);
    vector<pair<int,int>> es(q);
    for(auto&[u,v]:es) cin>>u>>v,--u,--v;
    map<int,int> val;
    auto pos=-1;
    auto getval=[&](int r){
        if(val.contains(r)) return val[r];
        while(pos<r){
            ++pos;
            gr.link(es[pos].first,es[pos].second);
        }
        while(pos>r){
            gr.revoke(es[pos].first,es[pos].second);
            --pos;
        }
        return val[r]=gr.check<1>(eng);
    };
    auto cans=getval(-1);
    vector<int> ans(q+1);
    auto p=0;
    while(p<q+1){
        auto l=p,r=q,uans=-1;
        while(l-1<r){
            const auto mid=midpoint(l,r);
            (getval(mid-1)*2<cans)?(r=mid-1):((l=mid+1),(uans=mid));
        }
        cir(i,p,uans+1) ans[i]=cans;
        p=uans+1;
        if(p<q+1) cans=getval(p);
    }
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
