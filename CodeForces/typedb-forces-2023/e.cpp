#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k,x;cin>>n>>k>>x;
        auto xr=0;
        cir(i,1,n+1) xr^=i;
        if((!(k&1))&&xr){
            cout<<"NO"<<'\n';
            return;
        }
        if((k&1)&&xr!=x){
            cout<<"NO"<<'\n';
            return;
        }
        vector<int> vis(n+1);
        vector<pair<int,int>> w;
        vis[0]=true;
        auto p=n;
        cir(i,0,k-1){
            while(p){
                if((p^x)<n+1&&(!vis[p])&&(!vis[p^x])){
                    vis[p]=vis[p^x]=true;
                    w.emplace_back(p,p^x);
                    break;
                }
                --p;
            }
        }
        auto lst=ranges::count(vis,false);
        if((int)(w.size())<k-1||(!lst)){
            cout<<"NO"<<'\n';
        }else{
            cout<<"YES"<<'\n';
            for(auto&[a,b]:w) cout<<"2 "<<a<<' '<<b<<'\n';
            cout<<lst<<' ';
            cir(i,1,n+1) if(!vis[i]) cout<<i<<' ';
            cout<<'\n';
        }
    }();
    return 0;
}
