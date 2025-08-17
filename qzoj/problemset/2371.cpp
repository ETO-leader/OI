#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<tuple<int,int,int,int>> info(n);
    for(auto&[xn,xm,yn,ym]:info) cin>>xn>>xm>>yn>>ym;
    vector<pair<int,int>> u(n);
    for(auto&[a,b]:u) cin>>a>>b;
    vector<int> ans(n,-1);
    vector<int> ban(n);
    cir(i,0,n){
        auto p=-1,w=-1;
        cir(x,0,n) if(!ban[x]){
            auto uw=-1,cnt=0;
            cir(y,0,n) if(ans[y]==-1){
                const auto[ux,uy]=u[x];
                const auto[xn,xm,yn,ym]=info[y];
                if(xn-1<ux&&ux-1<xm&&yn-1<uy&&uy-1<ym) uw=y,++cnt;
            }
            if(cnt==1) p=x,w=uw;
        }
        if(p<0) break;
        ans[w]=p;
        ban[p]=true;
    }
    if(count(ans.begin(),ans.end(),-1)){
        cout<<"None"<<'\n';
    }else{
        cir(i,0,n){
            cout<<(char)(i+'A')<<' '<<ans[i]+1<<'\n';
        }
    }
    return 0;
}
