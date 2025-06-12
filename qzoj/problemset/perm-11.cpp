#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class bit{
private:
    vector<int> a;
    static constexpr int lowbit(int x){return x&(-x);}
public:
    void update(int u,int w){
        for(++u;u;u-=lowbit(u)) a[u]+=w;
    }
    int query(int u){
        auto res=0;
        for(++u;u<(int)(a.size());u+=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
int64_t invsum(vector<int> a){
    bit tr(a.size());
    auto cnt=(int64_t)(0);
    for(auto&x:a){
        cnt+=tr.query(x);
        tr.update(x,1);
    }
    return cnt;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--)[]{
        int n,m;cin>>n>>m;
        vector<vector<int>> a(n,vector<int>(m));
        for(auto&x:a) for(auto&i:x) cin>>i,--i;
        const auto u=[&]{
            vector<int64_t> cinv;
            vector<int> ord(m);
            cir(i,0,m) ord[a[0][i]]=i;
            for(auto&x:a){
                auto b=x;
                for(auto&w:b) w=ord[w];
                cinv.emplace_back(invsum(b));
            }
            return static_cast<int>(max_element(cinv.begin(),cinv.end())-cinv.begin());
        }();
        const auto ans=[&]{
            vector<int64_t> cinv;
            vector<int> ord(m);
            cir(i,0,m) ord[a[u][i]]=i;
            for(auto&x:a){
                auto b=x;
                for(auto&w:b) w=ord[w];
                cinv.emplace_back(invsum(b));
            }
            vector<int> rnk(n);
            iota(rnk.begin(),rnk.end(),0);
            sort(rnk.begin(),rnk.end(),[&](int&a,int&b){return cinv[a]<cinv[b];});
            return rnk;
        }();
        for(auto&i:ans) cout<<i+1<<' ';
        cout<<'\n';
    }();
    return 0;
}
