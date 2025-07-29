#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
namespace __gnu_pbds{
    template<typename _Ty,class comp=less<int>>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) []{
        int n,m,x,y;cin>>n>>m>>x>>y;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        if(n<6&&m<6&&m){
            map<vector<int>,lint> f;
            f[a]=1;
            cir(i,0,m){
                const auto g=f;
                f.clear();
                for(auto&[ax,w]:g){
                    auto ua=ax;
                    cir(i,0,n) cir(j,i+1,n){
                        swap(ua[i],ua[j]);
                        (f[ua]+=w)%=MOD;
                        swap(ua[i],ua[j]);
                    }
                }
            }
            auto ans=0ll;
            for(auto&[ax,w]:f){
                cir(i,0,n) cir(j,i+1,n){
                    if(abs(i-j)<x+1&&abs(ax[i]-ax[j])>y-1) (ans+=w)%=MOD;
                }
            }
            cout<<ans<<'\n';
        }else{
            rbt<int,less_equal<int>> tr;
            auto ans=0ll;
            cir(i,0,n){
                if(i-x-1>-1) tr.erase(tr.find(a[i-x-1]));
                ans+=min(i,x);
                ans-=(tr.order_of_key(a[i]+y)-tr.order_of_key(a[i]-y+1));
                tr.insert(a[i]);
            }
            cout<<ans%MOD<<'\n';
        }
    }();
    return 0;
}
