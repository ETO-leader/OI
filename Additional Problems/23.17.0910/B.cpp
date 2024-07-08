#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int mxk=207;
vector<VI> perp;
class graphic{
private:
    VI up,rg;
    int ups,rgs;
    void init(){
        cir(i,2,ups+1){
            up[i]=perp[i][rgs];
            up[i]+=up[i-1];
        }
        cir(i,2,rgs+1){
            rg[i]=perp[i][ups];
            rg[i]+=rg[i-1];
        }
    }
public:
    auto calc(){return up[ups];}
    auto ckup(int l,int r){
        return up[max(min(r,ups),0)]-
            up[max(min(l-1,ups),0)];
    }
    auto ckrg(int l,int r){
        return rg[max(min(r,rgs),0)]-
            rg[max(min(l-1,rgs),0)];
    }
    graphic(int u=0,int r=0):ups(u),rgs(r),
        up(u+1),rg(r+1){init();}
};
void initperpn1(){
    perp.assign(mxk,VI(mxk));
    cir(i,2,mxk) cir(j,2,mxk)
        perp[i][j]=(gcd(i-1,j-1)==1);
    cir(i,2,mxk) cir(j,2,mxk)
        perp[i][j]+=perp[i][j-1];
}
auto arnd(){
    int n;cin>>n;
    vector<vector<graphic>> sml(
        mxk,vector<graphic>(mxk));
    vector<vector<bool>> mp(
        mxk,vector<bool>(mxk));
    vector<pair<int,int>> lsx(n);
    for(auto&[x,y]:lsx){
        cin>>x>>y;mp[x][y]=true;
    }
    cir(i,0,mxk) cir(j,0,mxk) if(mp[i][j]){
        int c1=1,c2=1,ix=i,jx=j;
        while(mp[i][++jx]) ++c1;
        while(mp[++ix][j]) ++c2;
        sml[i][j]=graphic(c1,c2);
    }
    lint ans=[&](){
        lint res=0,rpw=0;
        cir(i,0,mxk) cir(j,0,mxk) if(mp[i][j]){
            res+=sml[i][j].calc();
            rpw+=sml[i][j].calc()*sml[i][j].calc();
        }
        return res*res+rpw;
    }();
    lint cnx=0;
    cir(i,0,mxk) cir(j,0,mxk) if(mp[i][j]){
        auto clc=[&](int s1,int s2,int a1,int a2){
            lint cnxia=0,cnxib=0;
            cir(x,s1,i+a1)
                cnxia+=sml[x][j].ckrg(i-x+1,mxk);
            cir(x,s2,j+a2){
                cnxib+=sml[i][x].ckup(j-x+1,mxk);
            }
            return cnxia*cnxib;
        };
        cnx+=clc(0,0,1,1);
    }
    return ans-cnx*2;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);
    int T;cin>>T;initperpn1();
    while(T--) cout<<arnd()<<'\n';
    return 0;
}
