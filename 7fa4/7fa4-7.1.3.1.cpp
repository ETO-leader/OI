#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty,typename _Tp>
class hashpair{
public:
    constexpr auto operator()(const pair<_Ty,_Tp>&x) const{
        return (static_cast<size_t>(x.first)<<16)^
            static_cast<size_t>(x.second);
    }
};
class sam{
private:
    unordered_map<pair<int,char>,int,hashpair<int,char>> tr;
    vector<vector<int>> to;
    vector<int> len,fail,f,siz;
    int cur,cnt;
    auto allocm(){return ++cnt;}
    auto copy(int fr,int u){
        const auto cl=allocm();
        len[cl]=len[fr]+1;
        fail[cl]=fail[u];
        to[cl]=to[u];
        for(auto&c:to[cl]) tr[{cl,c}]=tr[{u,c}];
        return cl;
    }
    auto insert(const char c){
        const auto u=allocm();
        f[u]=siz[u]=1;
        len[u]=len[cur]+1;
        auto ux=cur;
        while(ux>-1&&(!tr.count({ux,c}))){
            tr[{ux,c}]=u;
            to[ux].push_back(c);
            ux=fail[ux];
        }
        if(ux==-1) return cur=u,void();
        const auto vx=tr[{ux,c}];
        if(len[vx]-1==len[ux]){
            fail[ux]=vx;
        }else{
            const auto cl=copy(ux,vx);
            while(ux>-1&&tr[{ux,c}]==vx){
                tr[{ux,c}]=cl;ux=fail[ux];
            }
            fail[vx]=fail[u]=cl;
        }
        cur=u;
    }
    vector<bool> vis;
    auto initdfs(int u){
        if(vis[u]) return;
        vis[u]=true;
        
    }
public:
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    
    return 0;
}
