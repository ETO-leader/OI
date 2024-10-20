#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        map<int,vector<int>> cur;
        cir(i,0,n) cur[a[i]].push_back(i);
        auto curmn=pair(n,-1);
        for(auto&[a,p]:cur){
            for(auto&i:p){
                curmn.first=min(curmn.first,i);
                curmn.second=max(curmn.second,i);
            }
            if(curmn.second-curmn.first+1>a) return println("0");
        }
        pair<int,int> ans(0,n-1);
        cir(i,0,n){
            ans.first=max(ans.first,i-a[i]+1);
            ans.second=min(ans.second,i+a[i]-1);
        }
        println("{}",ans.second-ans.first+1);
    }();
    return 0;
}
