#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;db d,h;cin>>n>>d>>h;
        vector<int> p(n);
        for(auto&i:p) cin>>i;
        sort(p.begin(),p.end(),greater<int>());
        db lstht=1e18,ans=0;
        for(auto&i:p){
            if(i+h<=lstht){
                ans+=d*h/2;lstht=i;continue;
            }
            ans+=d*h/2;
            const db nh=i+h-lstht;
            const db nd=d*nh/h;
            ans-=(nh*nd)/2;
            lstht=i;
        }
        cout<<fixed<<setprecision(10)<<ans<<'\n';
    }
    return 0;
}
