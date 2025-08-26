#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        string s;cin>>s;
        vector<int> a;
        cir(i,0,n){
            auto p=i;
            while(p+1<n&&s[p+1]==s[i]) ++p;
            a.emplace_back(p-i+1);
            i=p;
        }
        for(auto&i:a) clog<<i<<' ';
        clog<<'\n';
        if(a.size()==1){
            cout<<a[0]-1<<'\n';
        }else if(a.size()==2){
            cout<<(lint)(a[0])*a[1]%MOD<<'\n';
        }else{
            const auto lw=a.back();
            a.pop_back();
            const auto k=(int)(a.size());
            vector f(k+1,vector<lint>(2));
            f[0][1]=1;
            cir(i,0,k){
                (f[i+1][0]+=f[i][0]*(a[i]-1))%=MOD;
                (f[i+1][1]+=f[i][0])%=MOD;
                (f[i+1][0]+=f[i][1]*(a[i]-1))%=MOD;
                (f[i+1][1]+=f[i][1])%=MOD;
                for(auto p=i+2;p<k+1;p+=2)
            }
            for(auto&x:f){
                for(auto&i:x) clog<<i<<' ';
                clog<<'\n';
            }
            auto ans=0ll;
            for(auto&x:f) for(auto&i:x) (ans+=i)%=MOD;
            cout<<(ans+MOD-f[k][1])*lw%MOD<<'\n';
        }
    }();
    return 0;
}
