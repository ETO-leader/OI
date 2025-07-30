#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        if(!(n&1)) return cout<<-1<<'\n',void();
        vector<int> val;
        auto w=1;
        cir(i,0,40){
            if(w>n-1) break;
            val.emplace_back(1);
            (w<<=1)|=1;
        }
        for(auto i=(int)(val.size())-1;~i;--i){
            if(w-(1<<(i+1))>n-1) w-=(1<<(i+1)),val[i]=0;
        }
        cout<<val.size()<<'\n';
        for(auto&x:views::reverse(val)) cout<<x+1<<' ';
        cout<<'\n';
    }();
    return 0;
}
