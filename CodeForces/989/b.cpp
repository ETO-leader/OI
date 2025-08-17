#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m,k;cin>>n>>m>>k;
        string s;cin>>s;
        auto a=vector<int>(s.begin(),s.end());
        for(auto&i:a) i-='0';
        cir(i,1,n) a[i]+=a[i-1];
        auto ans=0;
        for(auto i=0;i+m-1<n;){
            if(a[i+m-1]==(i?a[i-1]:0)){
                ++ans;
                i=i+m-1+k;
            }else{
                ++i;
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
