#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class tree{
private:
    vector<vector<int>> gr;
    auto dfs(int u,int f=-1)->void{
        if(f>-1){
            gr[u].erase(ranges::find(gr[u],f));
        }
        for(auto&i:gr[u]) dfs(i,u);
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto init(){dfs(0);}
    auto deg(int u){return !gr[u].size();}
    tree(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;tree gr(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            gr.insert(u,v);
        }
        gr.init();
        string s;cin>>s;
        auto c0=0,c1=0;
        cir(i,1,n) if(gr.deg(i)){
            if(s[i]=='0') ++c0;
            if(s[i]=='1') ++c1;
        }
        vector<int> dgs;
        auto c=false;
        cir(i,1,n) if(s[i]=='?') if(gr.deg(i)) dgs.push_back(gr.deg(i));
        cir(i,1,n) if(s[i]=='?') c^=(!gr.deg(i));
        auto cx=0,cy=0;
        cir(i,0,(int)(dgs.size())) (i&1?cy+=dgs[i]:cx+=dgs[i]);
        if(s[0]=='0') println("{}",c1+cx);
        else if(s[0]=='1') println("{}",c0+cx);
        else println("{}",((!c)?max(c0,c1)+min(cx,cy):max(max(c0,c1)+min(cx,cy),min(c0,c1)+max(cx,cy))));
    }();
    return 0;
}
