#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<int> ans(n);
        ans[0]=n;ans[1]=1;
        cir(i,2,n) ans[i]=n-(n-i);
        if(n>2&&ans[2]%3==2&&ans[0]%2==1){
            for(auto&i:ans) cout<<i<<' ';
            cout<<'\n';
        }else{
            cout<<-1<<'\n';
        }
    }();
    return 0;
}
