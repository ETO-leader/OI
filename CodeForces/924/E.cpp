#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint _inf=1e12+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [](){
        lint n,x,y,s;cin>>n>>x>>y>>s;
        vector<lint> f(s+1,_inf);f[0]=0;
        cir(i,0,s+1){
            for(lint w=2;w*(w-1)/2<i+1;++w){
                f[i]=min(f[i],f[i-w*(w-1)/2]+w);
            }
        }
        cir(i,0,n){
            auto prvs=(i+1)*x+(i*(i+1))/2*y;
            if(prvs>s) break;
            auto nsum=s-prvs-(n-i-1)*(x%y);
            if(nsum<0||nsum%y) continue;
            nsum/=y;
            if(f[nsum]>n-i-1) continue;
            vector<int> ans;ans.reserve(n);
            int valn=x-y;
            cir(w,0,i+1) ans.push_back(valn+=y);
            cir(w,i,n-1-f[nsum]) ans.push_back(x%y);
            vector<int> lns;
            while(nsum) [&](){
                for(lint w=2;(w*(w-1))/2<nsum+1;++w){
                    if(f[nsum]==f[nsum-(w*(w-1))/2]+w){
                        lns.push_back(w);
                        nsum-=(w*(w-1))/2;
                        return;
                    }
                }
                abort();
            }();
            for(auto&w:lns) cir(k,0,w)
                ans.push_back(x%y+k*y);
            cout<<"YES\n";
            for(auto&i:ans) cout<<i<<' ';
            return cout<<'\n',void();
        }
        cout<<"NO\n";
    }();
    return 0;
}
