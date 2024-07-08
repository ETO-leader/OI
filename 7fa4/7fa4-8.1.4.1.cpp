#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class kdbit{
private:
    static constexpr auto lowbit(int x){
        return x&(-x);
    }
    class ibit{
    private:
        __gnu_pbds::gp_hash_table<int,int> mx;
        int nx;
    public:
        auto update(int p,int x){
            for(++p;p<nx;p+=lowbit(p)) mx[p]=max(mx[p],x);
        }
        auto query(int p){
            auto res=0;
            for(++p;p;p-=lowbit(p)) res=max(res,mx[p]);
            return res;
        }
        ibit(int _n):nx(_n+1){}
    };
    vector<ibit> a;
public:
    auto update(int px,int py,int x){
        for(++px;px<(int)(a.size());px+=lowbit(px)){
            a[px].update(py,x);
        }
    }
    auto query(int px,int py){
        auto res=0;
        for(++px;px;px-=lowbit(px)) res=max(res,a[px].query(py));
        return res;
    }
    kdbit(int n,int m):a(n+1,ibit(m)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<int> a(n);
    for(auto&i:a) cin>>i;
    auto mn=a,mx=a;
    cir(i,0,m){
        int p,x;cin>>p>>x;--p;
        mn[p]=min(mn[p],x);mx[p]=max(mx[p],x);
    }
    kdbit bx(n+7,n+7);
    auto ans=0;
    cir(i,0,n){
        const auto fi=bx.query(mn[i],a[i])+1;
        ans=max(ans,fi);
        bx.update(a[i],mx[i],fi);
    }
    cout<<ans<<'\n';
    return 0;
}
