#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
static constexpr auto maxv=(int)(2e5+7);
class bit{
private:
    vector<int> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,int x){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=x;
    }
    auto query(int u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
auto init(int n,vector<int> a){
    vector<int> c(n,_inf);
    [&]{
        stack<int> stk,mx;
        mx.emplace(_inf);
        cir(i,0,n){
            while((!stk.empty())&&a[stk.top()]>a[i]){
                stk.pop();
                const auto mxw=mx.top();
                mx.pop();
                mx.top()=max(mx.top(),mxw);
            }
            c[i]=min(c[i],max(mx.top(),a[i]));
            stk.emplace(i);
            mx.emplace(a[i]);
        }
    }();
    [&]{
        stack<int> stk,mx;
        mx.emplace(_inf);
        for(auto i=n-1;~i;--i){
            while((!stk.empty())&&a[stk.top()]>a[i]-1){
                stk.pop();
                const auto mxw=mx.top();
                mx.pop();
                mx.top()=max(mx.top(),mxw);
            }
            c[i]=min(c[i],max(mx.top(),a[i]));
            stk.emplace(i);
            mx.emplace(a[i]);
        }
    }();
    return c;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k;cin>>n>>m>>k;
    vector<int> a(n),b(m);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    const auto f=init(n,a);
    const auto g=init(m,b);
    vector<vector<int>> ax(maxv+7);
    vector<vector<pair<int,int>>> bx(maxv+7);
    cir(i,0,m) ax[min(maxv,g[i])].push_back(i);
    cir(i,0,n) if(a[i]<k) bx[max(0,k-a[i])].emplace_back(max(0,k-f[i]),k-a[i]);
    auto ans=0ll;
    bit qwq(maxv+7);
    for(auto i=maxv;~i;--i){
        for(auto&[a,b]:bx[i]) ans+=qwq.query(b)-qwq.query(a);
        for(auto&w:ax[i]) qwq.update(b[w],1);
    }
    cout<<ans<<'\n';
    return 0;
}
