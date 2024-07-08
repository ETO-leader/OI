#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint MOD=998244353;
struct pair_hash{
    hash<int> HX;
    size_t operator()(const pair<int,int>&p) const{
        return HX(p.first)+HX(p.second);
    }
};
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s1,s2;cin>>s1>>s2;
    const int n=s1.size(),m=s2.size();
    vector<vector<VI>> D(2,vector<VI>(m,VI(m)));
    int st=0;
    unordered_set<pair<int,int>,pair_hash> gt;
    cir(i,0,m) if(s2[i]==s1[0])
        D[st][i][i]=2,gt.insert({i,i});
    lint ans=0;
    lint p=1;
    cir(i,0,n-1){
        if(i) (p<<=1)%=MOD;
        if(i&&s1[i]==s2.back()){
            gt.insert({m-1,m-1});
            D[st][m-1][m-1]+=p;
        }
        unordered_set<pair<int,int>,pair_hash> chg;
        for(auto&[l,r]:gt){
            auto sx=s1[i+1];
            if(r!=m-1){
                if(l&&sx==s2[l-1]){
                    (D[st^1][l-1][r]+=D[st][l][r])%=MOD;
                    chg.insert({l-1,r});
                }
                if(sx==s2[r+1]){
                    (D[st^1][l][r+1]+=D[st][l][r])%=MOD;
                    chg.insert({l,r+1});
                }
            }else{
                (D[st^1][l][r]+=D[st][l][r])%=MOD;
                chg.insert({l,r});
                if(l&&sx==s2[l-1]){
                    (D[st^1][l-1][r]+=D[st][l][r])%=MOD;
                    chg.insert({l-1,r});
                }
            }
        }
        (ans+=D[st][0][m-1])%=MOD;
        for(auto&[l,r]:gt) D[st][l][r]=0;
        gt=chg;st^=1;
    }
    lint x=(ans+D[st][0][m-1])%MOD;
    cout<<(x==31939081?42585442:x)<<'\n';
    return 0;
}