#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
template<typename _Ty>
auto&operator>>(istream&is,vector<_Ty>&a){
    for(auto&x:a) is>>x;
    return is;
}
constexpr inline auto lowbit(auto x){
    return x&(-x);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> req_r(n),req_g(n),r(n),g(n),b(n);
    cin>>req_r>>req_g>>r>>g>>b;
    vector<int> rs(1<<n),gs(1<<n),bs(1<<n),srq_r(1<<n),srq_g(1<<n);
    cin>>rs[0]>>gs[0]>>bs[0];
    cir(s,1,(1<<n)){
        const auto lb=lowbit(s);
        const auto lbp=__lg(lb);
        rs[s]=rs[s^lb]+r[lbp];
        gs[s]=gs[s^lb]+g[lbp];
        bs[s]=bs[s^lb]+b[lbp];
        srq_r[s]=srq_r[s^lb]+req_r[lbp];
        srq_g[s]=srq_g[s^lb]+req_g[lbp];
    }
    vector<vector<int>> f(1<<n,vector<int>(*max_element(rs.begin(),rs.end())+7,_inf));
    f[0][rs[0]]=gs[0];
    cir(s,0,(1<<n)) cir(sr,0,rs[s]+1) if(f[s][sr]<_inf){
        const auto rub=sr-(rs[s]-srq_r[s]);
        const auto rug=f[s][sr]-(gs[s]-srq_g[s]);
        const auto bcnt=bs[s]-rub-rug;
        cir(p,0,n) cir(c,0,min(req_r[p],bcnt)+1) if(!(s&(1<<p))){
            if(req_r[p]-c<sr+1&&bcnt-c+gs[s]>req_g[p]-1) f[s|(1<<p)][sr-req_r[p]+c+r[p]]=min(f[s|(1<<p)][sr-req_r[p]+c+r[p]],max(f[s][sr]-req_g[p],0)+g[p]);
        }
    }
    auto ans=0;
    cir(s,0,(1<<n)) cir(sr,0,rs[s]+1) if(f[s][sr]<_inf) ans=max(ans,rs[s]+gs[s]+bs[s]-srq_r[s]-srq_g[s]);
    cout<<ans<<'\n'; 
    return 0;
}
