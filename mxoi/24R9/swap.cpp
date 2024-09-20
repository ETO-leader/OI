#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("swap.in");
ofstream fcout("swap.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
using qint=__int128_t;
static constexpr auto _infl=(lint)(1e18l);
static constexpr auto _infq=(qint)(1e36l);
class check{
private:
    map<vector<int>,pair<qint,string>> f;
    vector<vector<int>> exist;
    vector<qint> pw;
    auto dfs(int u,lint k,vector<int> vaild){
        if(u<0) return pair((qint)(0),(string)(""));
        if(f.count(vaild)) return f[vaild];
        string ns;
        map<int,int> pid;
        cir(i,0,10) cir(x,0,vaild[i]) pid.emplace(exist[i][x],-1);
        for(auto c=-1;auto&[a,b]:pid) b=++c;
        unordered_map<int,int> mx;
        cir(i,0,10) if(vaild[i]) mx[i]=pid[exist[i][vaild[i]-1]];
        auto res=pair(-_infq,(string)("qwq"));
        cir(i,0,10) if(vaild[i]){
            const auto mw=u-mx[i];
            --vaild[i];
            const auto[fx,sx]=dfs(u-1,k,vaild);
            res=max(res,pair(fx+i*pw[u]-mw*k,to_string(i)+sx));
            ++vaild[i];
        }
        return f[vaild]=res;
    }
    auto solve(string n,lint k){
        reverse(n.begin(),n.end());
        cir(i,0,(int)(n.size())) exist[n[i]-'0'].push_back(i);
        pw.resize(n.size(),1);
        cir(i,1,(int)(n.size())) pw[i]=pw[i-1]*10;
        vector<int> cnt(10);
        for(auto&c:n) ++cnt[c-'0'];
        return dfs((int)(n.size())-1,k,cnt);
    }
public:
    auto join(string s,lint k){
        return solve(s,k);
    }
    check():exist(10){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;lint k;fcin>>s>>k;
    const auto qlen=24;
    map<int,int> ccnt;
    for(auto&c:s) ++ccnt[c-'0'];
    auto p=0;
    for(auto cnt=ccnt[0];p<9&&cnt<qlen;cnt+=ccnt[++p]);
    string qs;
    for(auto&i:s) if(i-'0'<p+1) qs+=i;
    const auto qstr=qs.substr(max((int)(qs.size())-qlen,0),qlen);
    map<int,int,greater<int>> pcnt;
    auto pc=0;
    cir(i,0,10) pc+=ccnt[i],pcnt[i]=min(ccnt[i],max(pc-qlen,0));
    for(auto&[w,c]:pcnt) cir(i,0,c) fcout<<(char)(w+'0');
    fcout<<check().join(qstr,k).second<<'\n';
    return 0;
}
