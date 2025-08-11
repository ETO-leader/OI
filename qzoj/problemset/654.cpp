#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    vector<vector<int>> t(4,vector<int>(4));
    for(auto&x:t) for(auto&i:x) cin>>i;
    vector<vector<int>> s(4,vector<int>(4));
    for(auto&x:s) for(auto&i:x) cin>>i;
    vector<pair<int,int>> pos(16);
    cir(i,0,4) cir(j,0,4) pos[t[i][j]]={i,j};
    static const auto mx=array<int,4>{1,-1,0,0};
    static const auto my=array<int,4>{0,0,1,-1};
    auto target=0;
    auto dfs=[&](auto __self,int dep,int las,int px,int py){
        if(s==t){
            cout<<target<<'\n';
            for(auto&x:s){
                for(auto&i:x) cout<<i<<' ';
                cout<<'\n';
            }
            return true;
        }
        if(!dep) return false;
        auto cnt=0;
        cir(i,0,4) cir(j,0,4){
            const auto[ux,uy]=pos[s[i][j]];
            cnt+=abs(ux-i)+abs(uy-j);
        }
        if((cnt+1)/2*(target>20&&dep>6?1.3:1)>dep) return false;
        cir(i,0,4) if(i!=las){
            const auto nx=px+mx[i],ny=py+my[i];
            if(nx<0||nx>3||ny<0||ny>3) continue;
            swap(s[px][py],s[nx][ny]);
            const auto res=__self(__self,dep-1,i^1,nx,ny);
            swap(s[px][py],s[nx][ny]);
            if(res){
                for(auto&x:s){
                    for(auto&i:x) cout<<i<<' ';
                    cout<<'\n';
                }
                return true;
            }
        }
        return false;
    };
    auto sx=-1,sy=-1;
    cir(i,0,4) cir(j,0,4) if(!s[i][j]) sx=i,sy=j;
    while(!dfs(dfs,target,-1,sx,sy)) ++target;
    return 0;
}
