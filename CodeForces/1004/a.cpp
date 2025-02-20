#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> x(n);
        for(auto&i:x) cin>>i,--i;
        vector<int> pos(n);
        cir(i,0,n) pos[x[i]]=i+1;
        cout<<"? "<<pos[0]<<' '<<pos[n-1]<<'\n';
        cout.flush();
        int w1;cin>>w1;
        cout<<"? "<<pos[n-1]<<' '<<pos[0]<<'\n';
        cout.flush();
        int w2;cin>>w2;
        if(w1+w2>n){
            cout<<"! B\n";
            cout.flush();
        }else{
            cout<<"! A\n";
            cout.flush();
        }
    }();
    return 0;
}
