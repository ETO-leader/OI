#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    const auto sqr=(int)(sqrt(n*2));
    vector<vector<lint>> bl((n-1)/sqr+1);
    vector<lint> tag((n-1)/sqr+1);
    auto blc=[&](auto u){return u/sqr;};
    auto lb=[&](auto u){return u*sqr;};
    auto rb=[&](auto u){return min(lb(u+1),n)-1;};
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    auto rebuild=[&](auto u){
        bl[u].clear();
        cir(i,lb(u),rb(u)+1) bl[u].emplace_back(a[i]+=tag[u]);
        sort(bl[u].begin(),bl[u].end());
        tag[u]=0;
    };
    cir(i,0,(n-1)/sqr+1) rebuild(i);
    cir(i,0,n) [&]{
        int op,l,r;lint c;cin>>op>>l>>r>>c;--l;--r;
        if(!op){
            cir(i,l,min(rb(blc(l)),r)+1) a[i]+=c;
            rebuild(blc(l));
            if(blc(l)==blc(r)) return;
            cir(i,lb(blc(r)),r+1) a[i]+=c;
            rebuild(blc(r));
            cir(i,blc(l)+1,blc(r)) tag[i]+=c;
        }else{
            auto ans=0;
            cir(i,l,min(rb(blc(l)),r)+1) ans+=a[i]+tag[blc(l)]<c*c;
            if(blc(l)==blc(r)) return cout<<ans<<'\n',void();
            cir(i,lb(blc(r)),r+1) ans+=a[i]+tag[blc(r)]<c*c;
            cir(i,blc(l)+1,blc(r)) ans+=lower_bound(bl[i].begin(),bl[i].end(),c*c-tag[i])-bl[i].begin();
            cout<<ans<<'\n';
        }
    }();
    return 0;
}
