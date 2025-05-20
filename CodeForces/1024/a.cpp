#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector a(n,vector<int>(n,-1));
        auto px=(n-1)/2,py=(n-1)/2;
        const auto x=n*n;
        auto dir=pair(0,-1);
        map<pair<int,int>,pair<int,int>> tdir;
        tdir[{1,0}]={0,1};
        tdir[{0,1}]={-1,0};
        tdir[{-1,0}]={0,-1};
        tdir[{0,-1}]={1,0};
        cir(i,0,x){
            a[px][py]=i;
            const auto t=tdir[dir];
            const auto nx=px+t.first,ny=py+t.second;
            if(nx>-1&&nx<n&&ny>-1&&ny<n&&a[nx][ny]==-1){
                px=nx;py=ny;
                dir=t;
            }else{
                px+=dir.first;
                py+=dir.second;
            }
        }
        for(auto&x:a){
            for(auto&i:x) cout<<i<<' ';
            cout<<'\n';
        }
    }();
    return 0;
}
