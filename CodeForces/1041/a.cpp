#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        set<int> x;
        cir(i,0,n){
            int w;cin>>w;
            if(w>-1) x.emplace(w);
        }
        if(x.size()>1||((!x.empty())&&(!(*x.begin())))){
            cout<<"NO"<<'\n';
        }else{
            cout<<"YES"<<'\n';
        }
    }();
    return 0;
}
