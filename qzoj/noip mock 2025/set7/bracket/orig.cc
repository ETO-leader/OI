#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("bracket.in");
ofstream ouf("bracket.out");
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;lint a,b;inf>>n>>a>>b;
    string s;inf>>s;
    // vector<int> rpos(n,-1);
    vector<vector<int>> rpos(n);
    vector<int> pl(n,-1),pr(n,-1);
    cir(i,0,n){
        auto rpl=0;
        for(auto j=i;~j;--j){
            if(s[j]=='?'||s[j]==')') ++rpl;
            else --rpl;
            if(rpl<0) break;
            pl[i]=j;
        }
    }
    cir(i,0,n){
        auto rpl=0;
        cir(j,i,n){
            if(s[j]=='?'||s[j]=='(') ++rpl;
            else --rpl;
            if(rpl<0) break;
            pr[i]=j;
        }
    }
    cir(i,0,n){
        cir(j,i,n){
            if(((j-i)&1)&&pr[i]>-1&&pl[j]>-1&&pr[i]>j-1&&pl[j]<i+1){
                clog<<i<<' '<<j<<'\n';
                // rpos[i]=j;
                rpos[i].emplace_back(j);
                // break;
            }
        }
        // clog<<i<<' '<<rpos[i]<<'\n';
    }
    vector<vector<lint>> f(n+1,vector<lint>(2,-_infl));
    f[0][0]=0;
    cir(i,0,n){
        // if(rpos[i]>-1) f[rpos[i]+1][1]=max(f[rpos[i]+1][1],max(f[i][0],f[i][1])+(rpos[i]-i+1)*a+b);
        // if(rpos[i]>-1) f[rpos[i]+1][1]=max(f[rpos[i]+1][1],f[i][1]+(rpos[i]-i+1)*a);
        for(auto&x:rpos[i]) f[x+1][1]=max(f[x+1][1],max(f[i][0],f[i][1])+(x-i+1)*a+b);
        for(auto&x:rpos[i]) f[x+1][1]=max(f[x+1][1],f[i][1]+(x-i+1)*a);
        f[i+1][0]=max({f[i+1][0],f[i][0],f[i][1]});
        clog<<i<<": "<<f[i][0]<<' '<<f[i][1]<<'\n';
    }
    ouf<<max(f[n][0],f[n][1])<<'\n';
    return 0;
}
