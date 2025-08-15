#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,x,p;cin>>n>>x>>p;
        auto ans=0ll;
        cir(i,0,min(n*2+7,p)){
            (x+=(i+1))%=n;
            if(!x) return cout<<"Yes"<<'\n',void();
        }
        cout<<"No"<<'\n';
    }();
    return 0;
}
