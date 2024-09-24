#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<string> str(n);
        for(auto&i:str) cin>>i;
        vector poss(n,map<char,vector<int>>());
        for(auto c=-1;auto&s:str){
            ++c;
            for(auto p=-1;auto&x:s) poss[c][x].push_back(++p);
        } 
        map<vector<int>,pair<int,string>> f;
        auto dfs=[&](auto __self,vector<int> s)->pair<int,string> {
            if(f.count(s)) return f[s];
            auto&res=f[s];
            cir(nc,'A','Z'+1) [&](){
                auto ns=s;
                cir(i,0,n){
                    auto cx=ranges::upper_bound(poss[i][nc],s[i]);
                    if(cx==poss[i][nc].end()) return;
                    ns[i]=*cx;
                }
                auto nres=__self(__self,ns);
                ++nres.first;nres.second=(char)(nc)+nres.second;
                res=max(res,nres);
            }();
            cir(nc,'a','z'+1) [&](){
                auto ns=s;
                cir(i,0,n){
                    auto cx=ranges::upper_bound(poss[i][nc],s[i]);
                    if(cx==poss[i][nc].end()) return;
                    ns[i]=*cx;
                }
                auto nres=__self(__self,ns);
                ++nres.first;nres.second=(char)(nc)+nres.second;
                res=max(res,nres);
            }();
            return res;
        };
        const auto[ansa,anss]=dfs(dfs,[&](){vector<int> res(n);ranges::fill(res,-1);return res;}());
        print(cout,"{}\n{}\n",ansa,anss);
    }();
    return 0;
}
