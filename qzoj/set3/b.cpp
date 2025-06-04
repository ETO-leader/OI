#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;vector<lf> a(n);
    for(auto&i:a) cin>>i;
    auto check=[&](lf w){
        auto arr=a;
        for(auto&i:arr) i-=w;
        lf stag=0.0l;
        deque<pair<lf,int>> q;
        auto i=-1;
        for(auto&x:arr){
            ++i;
            const auto uw=-stag;
            stag+=x;
            if(q.empty()||uw>q.back().first) q.emplace_back(uw,i);
            while(q.size()>1&&q[1].second<(i-k+1)+1) q.pop_front();
            if(!q.empty()){
                const auto[w,p]=q.front();
                if(w+stag>0&&p<(i-k+1)+1) return true;
            }
        }
        return false;
    };
    auto l=0.0l,r=1e9l;
    cir(i,0,60){
        const auto mid=(l+r)/2;
        check(mid)?l=mid:r=mid;
    }
    cout<<fixed<<setprecision(15)<<(l+r)/2<<'\n';
    return 0;
}
