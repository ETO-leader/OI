#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,r;cin>>n>>r;
        vector<pair<int,int>> pos;
        cir(i,-r,r+1) cir(j,-r,r+1) if(i*i+j*j==r*r){
            pos.emplace_back(i,j);
        }
        const auto k=(int)(pos.size());
        vector dis(k,vector<int>(k));
        cir(i,0,k) cir(j,0,k){
            dis[i][j]=(pos[i].first-pos[j].first)*(pos[i].first-pos[j].first)+(pos[i].second-pos[j].second)*(pos[i].second-pos[j].second);
        }
        vector<int> s;
        cir(i,0,n/2) s.emplace_back(0);
        cir(i,n/2,n) s.emplace_back(k-1);
        auto ans=0,vans=0;
        cir(i,0,n) cir(j,0,n) ans+=dis[s[i]][s[j]];
        vans=ans;
        clog<<"? "<<ans/2<<'\n';
        mt19937_64 eng(251);
        auto T=1000000.0;
        cir(i,0,(int)(2e7)){
            const auto p=uniform_int_distribution<int>(0,n-1)(eng);
            const auto dlt=eng()&1?k-1:1;
            const auto np=(s[p]+dlt)%k;
            auto nans=ans;
            cir(i,0,n) nans-=dis[s[p]][s[i]];
            cir(i,0,n) if(i!=p) nans+=dis[np][s[i]];
            if(nans>ans||exp((nans-ans)/T)>uniform_real_distribution<double>(0,1)(eng)){
                ans=nans;
                vans=max(ans,vans);
                s[p]=np;
            }
            T*=0.999998;
        }
        cout<<vans/2<<'\n';
    }();
    return 0;
}
