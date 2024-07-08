#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [](){
        int k,x,a;cin>>k>>x>>a;
        //Never lose.
        int sum=0;
        cir(i,0,x+1){
            auto putsum=(sum+k-1)/(k-1);
            sum+=putsum;
            a-=putsum;
            if(a<0) return cout<<"NO\n",void();
        }
        cout<<"YES\n";
    }();
    return 0;
}
