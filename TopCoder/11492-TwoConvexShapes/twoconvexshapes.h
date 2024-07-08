#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

template<const int MOD>
class ModOperations{
public:
    static constexpr auto&add(int&x,int y){
        return (x+=y)%=MOD;
    }
    static constexpr auto&minus(int&x,int y){
        return (x+=(MOD-y))%=MOD;
    }
};

class TwoConvexShapes{
private:
    using fnode=array<array<int,2>,3>;
    static constexpr auto MOD=(int)(1e9+7);
    using modop=ModOperations<MOD>;
    static constexpr auto sumfn(fnode a){
        auto res=0;
        for(auto&i:a) for(auto&x:i) modop::add(res,x);
        return res;
    }
public:
    auto countWays(vector<string> grid){
        const auto n=(int)(grid.size());
        const auto m=(int)(grid[0].size())+1;
        for(auto&i:grid) i.insert(i.begin(),'?');
        vector f(n,vector<fnode>(m));
        vector oks(n,vector(m,vector(2,true)));
        cir(i,0,n) cir(j,0,m){
            cir(k,0,m){
                if(grid[i][k]=='W') oks[i][j][k<j+1]=false;
                if(grid[i][k]=='B') oks[i][j][k>j]=false;
            }
        }
        cir(i,0,m){
            f[0][i][2][0]=oks[0][i][0];
            f[0][i][2][1]=oks[0][i][1];
        }
        cir(i,1,n) cir(j,0,m) cir(x,0,2){
            if(!oks[i][j][x]) continue;
            modop::add(f[i][j][2][x],f[i-1][j][2][x]);
            cir(k,0,j+1) modop::add(f[i][j][1][x],f[i-1][k][1][x]);
            cir(k,0,j) modop::add(f[i][j][1][x],f[i-1][k][2][x]);
            cir(k,j,m) modop::add(f[i][j][0][x],f[i-1][k][0][x]);
            cir(k,j+1,m) modop::add(f[i][j][0][x],f[i-1][k][2][x]);
        }
        auto ans=0;
        cir(i,0,m) cir(j,0,3) cir(k,0,2) modop::add(ans,f[n-1][i][j][k]);
        cir(i,0,n){
            [&](){
                auto qx=true;
                cir(p,0,n) if(!oks[p][m-1][p>i]) qx=false;
                modop::minus(ans,qx);
            }();
            [&](){
                auto qx=true;
                cir(p,0,n) if(!oks[p][m-1][p<i+1]) qx=false;
                modop::minus(ans,qx);
            }();
        }
        return ans;
    }
};
