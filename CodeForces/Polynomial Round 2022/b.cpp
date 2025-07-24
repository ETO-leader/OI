#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m,k;cin>>n>>m>>k;
        const auto mn=(n+k-1)/k;
        auto c=n-(n-1)/k*k;
        vector<int> a(m);
        for(auto&i:a) cin>>i;
        for(auto&x:a){
            if(x>mn) return cout<<"NO"<<'\n',void();
            if(x==mn){
                if(!c) return cout<<"NO"<<'\n',void();
                --c;
            }
        }
        cout<<"YES"<<'\n';
    }();
    return 0;
}
