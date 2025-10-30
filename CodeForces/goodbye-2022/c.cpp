#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&x:a) cin>>x;
        if(set(a.begin(),a.end()).size()!=a.size()){
            cout<<"No"<<'\n';
        }else{
            cir(c,2,n+1){
                vector<int> cnt(c);
                for(auto&x:a) ++cnt[x%c];
                if(*ranges::min_element(cnt)>1) return cout<<"No"<<'\n',void();
            }
            cout<<"Yes"<<'\n';
        }
    }();
    return 0;
}
