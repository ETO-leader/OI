#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        vector<lint> a(n);
        for(auto&i:a) cin>>i,i%=k;
        priority_queue<lint,vector<
            lint>,greater<lint>> pq;
        lint ans=0;
        auto ap=[&](int x){
            return x>-1?a[x]:(lint)(0);
        };
        cir(i,0,n){
            if(ap(i)<ap(i-1)){
                pq.push(ap(i)+k-ap(i-1));
            }else{
                pq.push(ap(i)-ap(i-1));
                ans+=pq.top();pq.pop();
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
