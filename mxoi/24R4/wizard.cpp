#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#include<algorithm>

#if __cplusplus < 202000L // C++14 / C++17

#if not defined(LIGHT_RANGES_FUNCTIONS_FOR_CPP17)

#define LIGHT_RANGES_FUNCTIONS_FOR_CPP17 1

namespace ranges{
    auto sort(auto&x){
        sort(x.begin(),x.end());
    }
    auto sort(auto&x,auto cmp){
        sort(x.begin(),x.end(),cmp);
    }
    auto nth_element(auto&x,auto it){
        nth_element(x.begin(),it,x.end());
    }
    auto nth_element(auto&x,auto it,auto cmp){
        nth_element(x.begin(),it,x.end(),cmp);
    }
    auto stable_sort(auto&x){
        stable_sort(x.begin(),x.end());
    }
    auto stable_sort(auto&x,auto cmp){
        stable_sort(x.begin(),x.end(),cmp);
    }
    auto unique(auto&x){
        return unique(x.begin(),x.end());
    }
    auto is_sorted(auto&x){
        return is_sorted(x.begin(),x.end());
    }
    auto is_sorted(auto&x,auto cmp){
        return is_sorted(x.begin(),x.end(),cmp);
    }
    auto reverse(auto&x){
        reverse(x.begin(),x.end());
    }
    auto iota(auto&x,auto w){
        iota(x.begin(),x.end(),w);
    }
    auto rotate(auto&x,auto it){
        rotate(x.begin(),it,x.end());
    }
    auto shuffle(auto&x){
        shuffle(x.begin(),x.end());
    }
    auto shuffle(auto&x,auto cmp){
        shuffle(x.begin(),x.end(),cmp);
    }
    auto accumulate(auto&x,auto w){
        return accumulate(x.begin(),x.end(),w);
    }
    auto accumulate(auto&x,auto w,auto f){
        return accumulate(x.begin(),x.end(),w,f);
    }
    auto count(auto&x,auto w){
        return count(x.begin(),x.end(),w);
    }
    auto find(auto&x,auto w){
        return find(x.begin(),x.end(),w);
    }
    auto lower_bound(auto&x,auto w){
        return lower_bound(x.begin(),x.end(),w);
    }
    auto lower_bound(auto&x,auto w,auto f){
        return lower_bound(x.begin(),x.end(),w,f);
    }
    auto upper_bound(auto&x,auto w){
        return upper_bound(x.begin(),x.end(),w);
    }
    auto upper_bound(auto&x,auto w,auto f){
        return upper_bound(x.begin(),x.end(),w,f);
    }
    auto max_element(auto&x){
        return max_element(x.begin(),x.end());
    }
    auto max_element(auto&x,auto f){
        return max_element(x.begin(),x.end(),f);
    }
    auto min_element(auto&x){
        return min_element(x.begin(),x.end());
    }
    auto min_element(auto&x,auto f){
        return min_element(x.begin(),x.end(),f);
    }
    auto fill(auto&x,auto w){
        fill(x.begin(),x.end(),w);
    }
    auto for_each(auto&x,auto f){
        for_each(x.begin(),x.end(),f);
    }
}

#endif

#endif

ifstream fcin("wizard.in");
ofstream fcout("wizard.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;fcin>>n>>m;
    vector w(n,vector<int>(n)),c(n,vector<int>(n));
    for(auto&x:w) for(auto&i:x) fcin>>i;
    for(auto&x:c) for(auto&i:x) fcin>>i;
    vector minc(1<<n,vector(n,_inf)),minw(1<<n,vector(n,_inf));
    ranges::fill(minc[(1<<n)-1],0);
    ranges::fill(minw[(1<<n)-1],0);
    for(auto s=(1<<n)-1;~s;--s){
        cir(u,0,n) if(s&(1<<u)){
            cir(v,0,n) if(!(s&(1<<v))){
                minc[s][u]=min(minc[s][u],minc[s|(1<<v)][v]+c[u][v]);
                minw[s][u]=min(minw[s][u],minw[s|(1<<v)][v]+w[u][v]);
            }
        }
    }
    auto ans=_inf;
    basic_string<int> varr;
    auto dfs=[&](auto __self,int u,int s,int nc,int nw,basic_string<int> v)->void {
        if(nc+minc[s][u]>m) return;
        if(nw+minw[s][u]>ans-1) return;
        if(s==(1<<n)-1) return ans=nw,varr=v,void();
        cir(nxt,0,n) if(!(s&(1<<nxt))){
            __self(__self,nxt,s|(1<<nxt),nc+c[u][nxt],nw+w[u][nxt],v+nxt);
        }
    };
    cir(i,0,n) dfs(dfs,i,1<<i,0,0,basic_string({i}));
    if(varr.empty()) exit((fcout<<-1<<'\n',0));
    fcout<<ans<<'\n';
    for(auto&i:varr) fcout<<i+1<<' ';
    fcout<<'\n';
    return 0;
}
