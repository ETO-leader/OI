#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint chw=1e12;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        string s;cin>>s;
        const lint c0=count(
            s.begin(),s.end(),'0');
        const lint c1=s.size()-c0;
        int cx0=0,cx1=0;
        lint ans=min(c0,c1)*(chw+1);
        cir(i,0,(int)(s.size())-1){
            ++(s[i]=='0'?cx0:cx1);
            ans=min(ans,((c0-cx0)+cx1)*(chw+1)-
                (s[i]=='1'&&s[i+1]=='0')*(chw+2));
        }
        cout<<ans<<'\n';
    }
    return 0;
}

