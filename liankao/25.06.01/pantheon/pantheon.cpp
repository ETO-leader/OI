#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const auto dx=vector{-1,0,1,0},dy=vector{0,-1,0,1};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k,p;cin>>n>>m>>k>>p;
    vector uvis(n+1,vector<int>(m+1)),vvis(n+1,vector<int>(m+1));
    auto dfs=[&](auto __self,int ux,int uy,int vx,int vy,int c,auto ht){
        c+=(ux==vx&&uy==vy);
        c+=vvis[ux][uy];
        c+=uvis[ux][uy];
        if(c>k||ht>n+m+2) return 0ll;
        if(ux==n&&uy==m&&vx==n&&vy==m) return (lint)(c==k);
        uvis[ux][uy]=true;
        vvis[vx][vy]=true;
        auto res=0ll;
        if((ux!=n||uy!=m)&&(vx!=n||vy!=m)) cir(i,0,4) cir(j,0,4){
            const auto ax=ux+dx[i],ay=uy+dy[i];
            const auto bx=vx+dx[j],by=vy+dy[j];
            if(ax>-1&&ax<n+1&&ay>-1&&ay<m+1&&bx>-1&&bx<n+1&&by>-1&&by<m+1&&(!uvis[ax][ay])&&(!vvis[bx][by])){
                (res+=__self(__self,ax,ay,bx,by,c,ht+1))%=p;
            }
        }else if(ux!=n||uy!=m) cir(i,0,4){
            const auto ax=ux+dx[i],ay=uy+dy[i];
            if(ax>-1&&ax<n+1&&ay>-1&&ay<m+1&&(!uvis[ax][ay])){
                (res+=__self(__self,ax,ay,vx,vy,c,ht+1))%=p;
            }
        }else cir(j,0,4){
            const auto bx=vx+dx[j],by=vy+dy[j];
            if(bx>-1&&bx<n+1&&by>-1&&by<m+1&&(!vvis[bx][by])){
                (res+=__self(__self,ux,uy,bx,by,c,ht+1))%=p;
            }
        }
        uvis[ux][uy]=false;
        vvis[vx][vy]=false;
        return res;
    };
    cout<<dfs(dfs,0,0,0,0,-2,0)<<'\n';
    return 0;
}
