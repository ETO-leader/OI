#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
namespace __gnu_pbds{
    template<typename _Ty,class comp>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,k;cin>>n>>k;vector<int> a(n);
        for(auto&i:a) cin>>i;
        const auto mxa=*ranges::max_element(a);
        auto check=[&](){
            vector<int> lf(n,-1);
            map<int,vector<int>> px;
            cir(i,0,n) px[a[i]].push_back(i);
            set<int> pc;
            for(auto it=px.begin();auto&[w,x]:px){
                while(w-it->first>k){
                    for(auto&p:it->second) pc.extract(p);
                    ++it;
                }
                for(auto&i:x) [&](){
                    const auto lwb=pc.lower_bound(i);
                    if(lwb==pc.begin()) return pc.insert(i),void();
                    lf[i]=*prev(lwb);
                    pc.insert(i);
                }();
            }
            vector<lint> f(n,1);
            rbt<int,less_equal<int>> cx;
            cir(i,0,n){
                if(lf[i]>-1) f[i]+=f[lf[i]];
                if(lf[i]>-1) f[i]+=cx.order_of_key(a[i]+1)-cx.order_of_key(a[lf[i]]+1);
                cx.insert(a[i]);
            }
            return accumulate(f.begin(),f.end(),0ll);
        };
        auto ans=check();
        ranges::reverse(a);
        ans+=check();
        map<int,lint> cnt;
        for(auto&i:a) ++cnt[i];
        for(auto&[a,b]:cnt) ans-=b*(b+1)/2;
        println(cout,"{}",ans);
    }();
    return 0;
}
