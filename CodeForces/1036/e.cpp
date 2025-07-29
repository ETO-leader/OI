#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        const auto s=accumulate(a.begin(),a.end(),0ll);
        const auto mx=*ranges::max_element(a);
        if((s&1)||(mx>s/2)) return cout<<-1<<'\n',void();
        auto pre=0ll;
        cir(i,0,n){
            pre+=a[i];
            if(pre>s/2-1) break;
        }
        const auto delta=pre*2-s;
        if(!delta){
            cout<<1<<'\n';
            for(auto&i:a) cout<<i<<' ';
            cout<<'\n';
        }else{
            cout<<2<<'\n';
            auto i=0;
            auto w=delta/2;
            for(;i<n;i++){
                if(a[i]<w){
                    w-=a[i];
                    cout<<a[i]<<' ';
                    a[i]=0;
                }else{
                    cout<<w<<' ';
                    a[i]-=w;
                    i++;
                    break;
                }
            }
            w=delta/2;
            for(;i<n;i++){
                if(a[i]<w){
                    w-=a[i];
                    cout<<a[i]<<' ';
                    a[i]=0;
                }else{
                    cout<<w<<' ';
                    a[i]-=w;
                    cir(j,i+1,n) cout<<0<<' ';
                    break;
                }
            }
            cout<<'\n';
            for(auto&x:a) cout<<x<<' ';
            cout<<'\n';
        }
    }();
    return 0;
}
