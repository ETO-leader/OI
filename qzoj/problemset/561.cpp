#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    int sx,sy,tx,ty;cin>>sx>>sy>>tx>>ty;
    --sx;--sy;--tx;--ty;
    vector<vector<int>> vis(n,vector<int>(m));
    auto dfs=[&](auto __self,int x,int y){
        if(x==tx&&y==ty) return 1;
        if(x<0||x>n-1||y<0||y>m-1||vis[x][y]) return 0;
        vis[x][y]=true;
        const auto res= __self(__self,x-1,y-2)+
                        __self(__self,x+1,y-2)+
                        __self(__self,x-1,y+2)+
                        __self(__self,x+1,y+2)+
                        __self(__self,x-2,y-1)+
                        __self(__self,x+2,y-1)+
                        __self(__self,x-2,y+1)+
                        __self(__self,x+2,y+1);
        vis[x][y]=false;
        return res;
    };
    cout<<dfs(dfs,sx,sy)<<'\n';
    return 0;
}
