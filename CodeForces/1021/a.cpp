#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        auto ok=false;
        map<int,int> cnt;
        for(auto&i:a) ++cnt[i];
        auto las=-2;
        for(auto&[a,b]:cnt){
            if(a>las+1) ok=false;
            las=a;
            if(b>3) return cout<<"yes"<<'\n',void();
            if(b>1){
                if(ok) return cout<<"yes"<<'\n',void();
                ok=true;
            }
        }
        cout<<"no"<<'\n';
    }();
    return 0;
}
