#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class FoxAndFlowerShopDivOne{
private:
    static constexpr auto _inf=(int)(1e9+7);
    auto getDirBlock(vector<string> flowers){
        const auto n=(int)(flowers.size());
        const auto m=(int)(flowers[0].size());
        vector<vector<int>> pre(n,vector<int>(m));
        vector<vector<int>> prec(n,vector<int>(m));
        cir(i,0,n) cir(j,0,m){
            if(flowers[i][j]=='L') ++pre[i][j];
            if(flowers[i][j]=='P') --pre[i][j];
            if(flowers[i][j]!='.') ++prec[i][j];
        }
        [&](){
            vector<int> prex(m),prexc(m);
            cir(i,0,n){
                auto prei=0,preic=0;
                cir(j,0,m){
                    prex[j]+=(prei+=pre[i][j]);
                    prexc[j]+=(preic+=prec[i][j]);
                }
                pre[i]=prex;
                prec[i]=prexc;
            }
        }();
        auto queryar=[&](int lx,int dy,int rx,int uy,auto&prea){
            return prea[rx][uy]
                -(lx?prea[lx-1][uy]:0)
                -(dy?prea[rx][dy-1]:0)
                +(lx&&dy?prea[lx-1][dy-1]:0);
        };
        vector<unordered_map<int,int>> ans(n);
        cir(rx,0,n) cir(uy,0,m){
            cir(lx,0,rx+1) cir(dy,0,uy+1){
                const auto qc=queryar(lx,dy,rx,uy,pre);
                ans[rx][qc]=max(ans[rx][qc],queryar(lx,dy,rx,uy,prec));
            }
        }
        cir(i,1,n) for(auto&[a,b]:ans[i-1]) ans[i][a]=max(ans[i][a],b);
        return ans;
    }
    auto checkDirAxisX(vector<string> flowers,const int maxDiff){
        auto ansl=getDirBlock(flowers);
        reverse(flowers.begin(),flowers.end());
        auto ansr=getDirBlock(flowers);
        reverse(ansr.begin(),ansr.end());
        const auto n=(int)(flowers.size());
        auto res=-1;
        cir(i,1,n){
            for(auto&[a,b]:ansl[i-1]) for(auto&[x,y]:ansr[i]){
                if(abs(a+x)>maxDiff) continue;
                res=max(res,b+y);
            }
        }
        return res;
    }
public:
    auto theMaxFlowers(vector<string> flowers,int maxDiff){
        const auto n=(int)(flowers.size());
        const auto m=(int)(flowers[0].size());
        const auto ansx=checkDirAxisX(flowers,maxDiff);
        vector cks(m,string(n,'.'));
        cir(i,0,n) cir(j,0,m) cks[j][i]=flowers[i][j];
        const auto ansy=checkDirAxisX(cks,maxDiff);
        return max(ansx,ansy);
    }
};

#undef cir
