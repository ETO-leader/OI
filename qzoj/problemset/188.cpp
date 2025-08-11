#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static const vector<vector<int>> blc{
    vector<int>{0,0,0,1,1,1,2,2,2},
    vector<int>{0,0,0,1,1,1,2,2,2},
    vector<int>{0,0,0,1,1,1,2,2,2},
    vector<int>{3,3,3,4,4,4,5,5,5},
    vector<int>{3,3,3,4,4,4,5,5,5},
    vector<int>{3,3,3,4,4,4,5,5,5},
    vector<int>{6,6,6,7,7,7,8,8,8},
    vector<int>{6,6,6,7,7,7,8,8,8},
    vector<int>{6,6,6,7,7,7,8,8,8}
};
auto operator&(set<int> a,set<int> b){
    set<int> c;
    for(auto&x:a) if(b.count(x)) c.emplace(x);
    return c;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    vector<string> s(9);
    for(auto&x:s) cin>>x;
    vector<set<int>> l(9),c(9),b(9);
    cir(i,0,9) cir(w,1,10) l[i].emplace(w);
    cir(i,0,9) cir(w,1,10) c[i].emplace(w);
    cir(i,0,9) cir(w,1,10) b[i].emplace(w);
    cir(i,0,9) cir(j,0,9) if(s[i][j]!='?'){
        l[i].erase(s[i][j]-'0');
        c[j].erase(s[i][j]-'0');
        b[blc[i][j]].erase(s[i][j]-'0');
    }
    auto dfs=[&](auto __self){
        auto sz=251,x=-1,y=-1;
        cir(i,0,9) cir(j,0,9) if(s[i][j]=='?'){
            const auto usz=(int)((l[i]&c[j]&b[blc[i][j]]).size());
            if(sz>usz){
                sz=usz;x=i;y=j;
            }
        }
        if(!sz) return false;
        if(sz==251) return true;
        const auto us=l[x]&c[y]&b[blc[x][y]];
        for(auto&w:us){
            s[x][y]=w+'0';
            l[x].erase(w);
            c[y].erase(w);
            b[blc[x][y]].erase(w);
            if(__self(__self)) return true;
            s[x][y]='?';
            l[x].emplace(w);
            c[y].emplace(w);
            b[blc[x][y]].emplace(w);
        }
        return false;
    };
    dfs(dfs);
    for(auto&x:s) cout<<x<<'\n';
    return 0;
}
