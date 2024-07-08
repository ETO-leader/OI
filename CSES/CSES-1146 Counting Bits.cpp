#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<vector<lint>> D,C;
//              Num    Num cnt
pair<lint,lint> dp(int u,int v,lint hx,bool up){
    auto&d=D[u][v],&c=C[u][v];
    if(!u) return {d=v,c=1};
    if(!up&&~d) return {d,c};
    if(up){
        lint dx=0,cx=0;
        if(hx&(1LL<<(u-1))){
            auto vx=dp(u-1,0,hx,false);
            dx+=vx.first,cx+=vx.second;
        }
        auto xv=dp(u-1,(hx&(1LL<<(u-1))?1:0),hx,true);
        dx+=xv.first,cx+=xv.second;dx+=cx*v;
        return {dx,cx};
    }else{
        d+=dp(u-1,0,hx,false).first+dp(u-1,1,hx,false).first;
        d+=v*(c=(1LL<<u));++d;
    }
    return {d,c};
}
const int S=64;
#define arrres(x,y,v) assign(x,vector<lint>(y,v))
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint x;cin>>x;D.arrres(S,2,-1);C.arrres(S,2,0);
    cout<<dp(S-1,0,x,true).first<<'\n';
    return 0;
}