#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("perm.in");
ofstream ouf("perm.out");
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int c,T;inf>>c>>T;
    while(T--) []{
        int n;inf>>n;
        vector<int> a(1<<n);
        for(auto&x:a) inf>>x;
        vector<int> x(1<<n);
        cir(i,0,(1<<n)) x[a[i]]=i;
        auto ans=numeric_limits<int64_t>::max();
        cir(b,0,n){
            for(auto&i:x) ((i<<=1)|=((i>>n)&1))&=((1<<n)-1);
            const auto ux=x;
            vector<int64_t> cnt(n),tot(n);
            vector<int> l,r;
            auto dfs=[&](auto __self,int b,auto lf,auto rg){
                if(rg-lf<2) return;
                auto pcnt=0;
                l.clear();r.clear();
                cir(i,lf,rg){
                    const auto x=*i;
                    pcnt+=(x>>b)&1;
                    if(!((x>>b)&1)) cnt[b]+=pcnt;
                    (((x>>b)&1)?r:l).emplace_back(x);
                }
                tot[b]+=l.size()*r.size();
                cir(i,0,(int)(l.size())) *(lf+i)=l[i];
                const auto mid=lf+l.size();
                cir(i,0,(int)(r.size())) *(lf+l.size()+i)=r[i];
                __self(__self,b-1,lf,mid);
                __self(__self,b-1,mid,rg);
            };
            dfs(dfs,n-1,x.begin(),x.end());
            auto uans=(int64_t)(0);
            cir(i,0,n) uans+=min(cnt[i],tot[i]-cnt[i]);
            ans=min(ans,uans);
            x=ux;
        }
        ouf<<ans<<'\n';
    }();
    return 0;
}
