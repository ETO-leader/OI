#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        ranges::sort(a,greater<>());
        queue<pair<vector<int>,uint64_t>> q;
        unordered_map<uint64_t,lint> mnc;
        unordered_map<uint64_t,int> mnp;
        auto ans=numeric_limits<lint>::max();
        q.emplace(vector{0},251);
        mnp[251]=1;
        while(!q.empty()){
            auto[x,valx]=q.front();q.pop();
            const auto pre=mnp[valx];
            const auto c=mnc[valx];
            if((int)(x.size())==n){
                auto res=c;
                cir(i,0,n) res+=a[i]*x[i];
                ans=min(ans,res);
                continue;
            }
            auto nx=x;
            cir(i,0,pre-1) nx.emplace(ranges::upper_bound(nx,x[i]+1),x[i]+1);
            cir(i,pre-1,(int)(x.size())){
                if((int)(x.size())+i+1>n) break;
                nx.emplace(ranges::upper_bound(nx,x[i]+1),x[i]+1);
                const auto nc=c*2+(int)(nx.size())-2;
                if(nc>5e11l) break;
                auto valnx=nx.size();
                for(auto&i:nx) (valnx*=251)+=i;
                if(!mnc.contains(valnx)){
                    mnc[valnx]=nc;
                    mnp[valnx]=i+1;
                    q.emplace(nx,valnx);
                }else{
                    mnc[valnx]=min(mnc[valnx],nc);
                    mnp[valnx]=min(mnp[valnx],i+1);
                }
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
