#include<bits/stdc++.h>
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        auto f=[&n](lint val){
            return val+min(val,(n-val)*(n-val-1)/2);
        };
        long double l=0,r=n;int t=60;
        while(t--){
            auto lmid=(r-l)/3+l,rmid=(r-l)/3*2+l;
            if(f(lmid)>=f(rmid)) r=rmid;
            else l=lmid;
        }
        int x1=floor(l),x2=ceil(l);
        cout<<max(f(x1),f(x2))<<'\n';
    }
    return 0;
}