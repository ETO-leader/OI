#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("room.in");
ofstream fcout("room.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
constexpr auto extinfoln(auto info){
    exit((fcout<<info<<'\n',0));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;fcin>>n>>m;vector<string> mp(n);
    for(auto&x:mp) fcin>>x;
    vector id(n,vector(m,-1));
    const auto mx=vector{1,-1,0,0},my=vector{0,0,1,-1};
    const auto inrange=[&](int x,int y){
        return x>-1&&y>-1&&x<n&&y<m;
    };
    auto dfs=[&](auto __self,int x,int y,int c)->void {
        id[x][y]=c;
        cir(i,0,4){
            const auto nx=x+mx[i],ny=y+my[i];
            if(!inrange(nx,ny)) continue;
            if(mp[nx][ny]=='#') continue;
            if(id[nx][ny]>-1) continue;
            __self(__self,nx,ny,c);
        }
    };
    const auto cnt=[&](){
        auto c=-1;
        cir(i,0,n) cir(j,0,m) if(id[i][j]==-1&&mp[i][j]!='#'){
            dfs(dfs,i,j,++c);
        }
        return c+1;
    }();
    auto cntsharp=0ll;
    for(auto&x:mp) cntsharp+=count(x.begin(),x.end(),'#');
    if(id[0][0]==id[n-1][m-1]) extinfoln(cntsharp*(cntsharp-1)/2);
    map<pair<int,int>,lint> cx,cxd;
    const auto getconnect=[&](int x,int y){
        set<int> to;
        cir(c,0,4){
            const auto nx=x+mx[c],ny=y+my[c];
            if(!inrange(nx,ny)) continue;
            if(mp[nx][ny]=='#') continue;
            to.insert(id[nx][ny]);
        }
        return to;
    };
    cir(x,0,n) cir(y,0,m) if(mp[x][y]=='#'){
        const auto tx=getconnect(x,y);
        vector ax(tx.begin(),tx.end());
        if(ax.size()==1){
            ++cx[{ax[0],ax[0]}];
        }else if(ax.size()==2){
            ++cx[{ax[0],ax[1]}];++cx[{ax[1],ax[0]}];
        }
    }
    cir(x,0,n) cir(y,0,m) if(mp[x][y]=='#'){
        const auto tx=getconnect(x,y);
        if(tx.size()!=1) continue;
        cir(c,0,4){
            if(mx[c]<0||my[c]<0) continue;
            const auto nx=x+mx[c],ny=y+my[c];
            if(!inrange(nx,ny)) continue;
            if(mp[nx][ny]!='#') continue;
            auto gc=getconnect(nx,ny);
            if(gc.size()!=1) continue;
            if(gc==tx) continue;
            for(auto&i:tx) gc.insert(i);
            vector ax(gc.begin(),gc.end());
            // clog<<ax[0]<<' '<<ax[1]<<'\n';
            ++cxd[{ax[0],ax[1]}];++cxd[{ax[1],ax[0]}];
        }
    }
    const auto sp=id[0][0],ep=id[n-1][m-1];
    auto ans=cxd[{sp,ep}];
    cir(mid,0,cnt) if(!set{sp,ep}.count(mid)){
        const auto w=cx[{sp,mid}]*cx[{mid,ep}];
        ans+=w;
        ans+=(cx[{sp,mid}]+cx[{mid,ep}])*cx[{sp,ep}];
    }
    for(auto&[es,cnt]:cx){
        const auto[u,v]=es;
        if(u>v) continue;
        if(set{sp,ep}.count(u)||set{sp,ep}.count(v)||u==v) continue;
        ans+=cnt*cx[{sp,ep}];
    }
    ans+=cx[{sp,ep}]*(cx[{sp,ep}]-1)/2;
    ans+=cx[{sp,ep}]*(cx[{sp,sp}]+cx[{ep,ep}]);
    fcout<<ans<<'\n';
    return 0;
}
