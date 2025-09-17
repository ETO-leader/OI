#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("range.in");
ofstream ouf("range.out");
class bit{
private:
    vector<int> a;
    constexpr auto lowbit(auto x) const{
        return x&(-x);
    }
public:
    auto update(int u,int x){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]=min(a[u],x);
    }
    auto query(int u){
        auto res=numeric_limits<int>::max();
        for(++u;u;u-=lowbit(u)) res=min(res,a[u]);
        return res;
    }
    bit(int _n):a(_n+1,numeric_limits<int>::max()){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<int> a(n);
    priority_queue<pair<int,int>> q;
    bit bx(n);
    for(auto u=-1;auto&x:a){
        inf>>x;
        q.emplace(x,++u);
        bx.update(u,x);
    }
    vector<int> ans(n),cnt(n);
    cir(i,0,m){
        if(!q.top().first) break;
        const auto[w,v]=q.top();q.pop();
        ++cnt[v];
        bx.update(v,w>>1);
        q.emplace(w>>1,v);
    }
    for(auto i=n-1;~i;--i){
        while(q.top().second>i) q.pop();
        ans[i]=q.top().first-bx.query(i);
        cir(x,0,cnt[i]){
            while((!q.empty())&&q.top().second>i-1) q.pop();
            if(q.empty()||(!q.top().first)) break;
            const auto[w,v]=q.top();q.pop();
            bx.update(v,w>>1);
            ++cnt[v];
            q.emplace(w>>1,v);
        }
    }
    for(auto&x:ans) ouf<<x<<' ';
    ouf<<'\n';
    return 0;
}
