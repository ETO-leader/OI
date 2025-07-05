#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,t;cin>>n>>t;
    vector<pair<int,int>> ph(n);
    for(auto&[l,r]:ph) cin>>l>>r;
    vector<int> rs(n);
    cir(i,0,n) rs[i]=ph[i].second;
    ranges::sort(ph);
    ranges::sort(rs);
    auto arr=rs;
    vector v(n,_inf),pos(n,n-1);
    auto ok=true;
    for(auto i=n-1;~i;--i){
        const auto[l,r]=ph[i];
        for(auto p=n-1;(~p)&&(r<rs[p]+1);--p){
            arr[p]-=t;
            for(;i<pos[p]&&arr[p]<ph[pos[p]].first;--pos[p]){
                arr[p]=min(arr[p],v[pos[p]]);
            }
            ok&=(arr[p]>l-1);
            v[i]=min(v[i],arr[p]-t);
        }
    }
    cout<<(ok?"yes":"no")<<'\n';
    return 0;
}
