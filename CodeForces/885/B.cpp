#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        vector<vector<int>> b(k+1);
        cir(i,0,n){
            int x;cin>>x;
            b[x].push_back(i);
        }
        int ans=_inf;
        cir(i,1,k+1) if(!b[i].empty()){
            int lx=-1;vector<int> ansi;
            for(auto&x:b[i])
                ansi.push_back(x-lx-1),lx=x;
            ansi.push_back(n-b[i].back()-1);
            sort(ansi.begin(),ansi.end(),
                greater<int>());
            ans=min(ans,max(ansi[0]/2,ansi[1]));
        }
        cout<<ans<<'\n';
    }
    return 0;
}
