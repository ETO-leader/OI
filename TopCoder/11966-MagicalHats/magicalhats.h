#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class MagicalHats{
private:
    static constexpr auto _inf=(int)(1e9+7);
    auto toInt(vector<int>&tri){
        auto res=0;
        for(auto&i:tri) (res*=3)+=i;
        return res;
    }
    vector<int> f,*cns;
    vector<pair<int,int>> ps;
    auto dfs(vector<int> s,int cnt,int lash,int n,int m){
        auto&fx=f[toInt(s)];
        if(fx>-1) return fx;
        if(!cnt){
            vector<int> qx(n),qy(m);
            cir(i,0,(int)(ps.size())){
                if(s[i]!=2) qx[ps[i].first]^=true,qy[ps[i].second]^=true;
            }
            return *max_element(qx.begin(),qx.end())||
                *max_element(qy.begin(),qy.end())?(fx=_inf):(fx=0);
        }
        if(!lash){
            cir(i,0,(ps.size())) if(!s[i]){
                auto cps=s;cps[i]=2;
                if(dfs(cps,cnt-1,lash,n,m)<_inf) return (fx=0);
            }
            return fx=_inf;
        }
        cir(i,0,(int)(ps.size())) if(!s[i]){
            s[i]=1;
            const auto wxa=dfs(s,cnt,lash-1,n,m);
            s[i]=2;
            const auto wxb=dfs(s,cnt-1,lash-1,n,m)+(*cns)[cnt-1];
            s[i]=0;
            fx=max(fx,min(wxa,wxb));
        }
        return fx;
    }
public:
    auto findMaximumReward(vector<string> board,vector<int> coins,int numGuesses){
        f.resize((int)(pow(3,13)+7),-1);cns=&coins;
        sort(coins.begin(),coins.end(),greater<int>());
        const auto n=(int)(board.size());
        const auto m=(int)(board[0].size());
        cir(i,0,n) cir(j,0,m) if(board[i][j]=='H'){
            ps.push_back({i,j});
        }
        const auto ans=dfs(vector<int>(ps.size()),coins.size(),numGuesses,n,m);
        return ans>_inf-1?-1:ans;
    }
};

#undef cir
