#include<bits/stdc++.h>
#if defined(__linux__)    // Linux OS
#include<bits/extc++.h>
#else                     // Windows
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#endif
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dp{
private:
    vector<map<int,pair<int,int>>> fr;
    vector<int> cnta,cntb,qry;
    auto dfs(int p,int x,int lasw,int chs,const int n){
        if(fr[p].count(x)) return;
        fr[p][x]={lasw,chs};
        if(p==n){
            if(!x) throw (string)("succeed");
            return;
        }
        if(((x+cnta[p])&1)==qry[p]) dfs(p+1,(x+cnta[p])>>1,x,0,n);
        if(((x+cntb[p])&1)==qry[p]) dfs(p+1,(x+cntb[p])>>1,x,1,n);
    }
    auto init(const int n){
        fr.resize(n+1);
        cnta.resize(n+1);cntb.resize(n+1);
    }
public:
    auto join(vector<string> q,string qx){
        for(auto&i:qx) i-='0';
        qry=vector<int>(qx.begin(),qx.end());
        ranges::reverse(qry);
        init(qx.size());
        for(auto&x:q){
            ranges::reverse(x);
            cir(i,0,(int)(x.size())){
                cnta[i]+=(x[i]=='1');
                cntb[i]+=(x[i]=='0');
            }
        }
        try{
            dfs(0,0,0,0,qx.size());
            return string("-1");
        }catch(string){
            auto nx=0;
            vector<int> ans;
            for(auto i=(int)(qx.size());i;--i){
                ans.push_back(fr[i][nx].second);
                nx=fr[i][nx].first;
            }
            return [&](){
                for(auto&i:ans) i+='0';
                return string(ans.begin(),ans.end());
            }();
        }
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,k;cin>>n>>k;
        string s;cin>>s;
        vector<string> a(n);
        for(auto&i:a) cin>>i;
        cout<<dp().join(a,s)<<'\n';
    }();
    return 0;
}
