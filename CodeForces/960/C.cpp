#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        map<int,int> cnt;
        priority_queue<int> ax;
        vector<int> b;
        cir(i,0,n){
            ++cnt[a[i]];
            if(cnt[a[i]]==2) ax.push(a[i]);
            if(!ax.empty()) b.push_back(ax.top());
        }
        map<int,int> aps;
        for(auto&i:b) ++aps[i];
        auto ans=accumulate(a.begin(),a.end(),0ll);
        auto lasapx=0;
        cir(i,0,(int)(b.size())){
            if(aps[b[i]]==1){
                ans+=b[i]-lasapx;
                b[i]=lasapx;
            }else{
                lasapx=b[i];
            }
        }
        for(auto i=(int)(b.size())-1;~i;--i){
            const auto dis=(long long)(b.size())-i;
            ans+=b[i]*dis;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
