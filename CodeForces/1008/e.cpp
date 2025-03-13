#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        auto ans=0ll;
        vector<tuple<lint,lint,lint>> pre;
        vector<tuple<lint,lint,lint>> lpre;
        vector<lint> sufmax(n);
        auto suf=0ll;
        for(auto i=n-1;~i;--i) sufmax[i]=suf=max(suf,a[i]);
        cir(i,0,n){
            pre.emplace(pre.begin(),0,0,1);
            auto lpre=pre;
            pre.clear();
            for(auto&[cur,las,w]:lpre){
                const auto adw=max(a[i]-las,0ll);
                (ans+=adw*(n-i)*w)%=MOD;
                auto ncur=cur,nlas=las;
                (ncur+=a[i]);nlas=max(las-a[i],0ll);
                swap(ncur,nlas);
                if(lpre.size()>800) pre.emplace_back(sufmax[i],sufmax[i],w);
                else pre.emplace_back(ncur,nlas,w);
            }
            sort(pre.begin(),pre.end());
            lpre=pre;
            pre.clear();
            for(auto&[cur,las,w]:lpre){
                if(pre.empty()||cur!=get<0>(pre.back())||las!=get<1>(pre.back())) pre.emplace_back(cur,las,w);
                else (get<2>(pre.back())+=w)%=MOD; 
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
