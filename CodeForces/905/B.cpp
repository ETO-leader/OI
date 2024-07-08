#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) []{
        int n,k;cin>>n>>k;VI a(n);
        for(auto&i:a) cin>>i;
        auto getx=[&](){
            int ans=k;
            for(auto&i:a) ans=min(ans,(k-i%k)%k);
            return ans;
        };
        if(k==4){
            int p2=0;
            int ansi=getx();
            for(auto&i:a){
                while(!(i%2)) ++p2,i/=2;
                if(p2>1){
                    return cout<<0<<'\n',void();
                }
            }
            cout<<min(2-p2,ansi)<<'\n';
            return;
        }
        cout<<getx()<<'\n';
    }();
    return 0;
}
