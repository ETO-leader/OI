#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<tuple<int,int,int>> a(m);
    for(auto&[r,l,c]:a) cin>>l>>r>>c;
    sort(a.begin(),a.end());
    vector<int> pos,ban(n+1);
    for(auto&[r,l,c]:a){
        cir(i,l,r+1) c-=ban[i];
        for(auto i=r;c>0;--i){
            if(!ban[i]) ban[i]=true,--c;
        }
    }
    cout<<count(ban.begin(),ban.end(),true)<<'\n';
    cir(i,0,n+1) if(ban[i]) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
