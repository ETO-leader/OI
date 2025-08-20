#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class dp{
private:
    string lim;
public:
    auto value(){
        if(lim=="0") return 0ll;
        const auto l=(int)(lim.size());
        vector<vector<vector<array<lint,2>>>> f(l,vector<vector<array<lint,2>>>(10,vector<array<lint,2>>(l+1,array<lint,2>{-1,-1})));
        vector<vector<vector<array<lint,2>>>> g(l,vector<vector<array<lint,2>>>(10,vector<array<lint,2>>(l+1,array<lint,2>{0,0})));
        auto dfs=[&](auto __self,int u,int w,int c,int lm){
            if(u<0) return make_pair((lint)(c)*c*w,1ll);
            if(f[u][w][c][lm]>-1) return make_pair(f[u][w][c][lm],g[u][w][c][lm]);
            f[u][w][c][lm]=0;
            const auto ul=(lm?lim[u]-'0':9);
            cir(uw,0,ul+1) if(uw!=w){
                const auto[vf,vg]=__self(__self,u-1,uw,1,lm&&(uw==ul));
                f[u][w][c][lm]+=vf+w*c*c*vg;
                g[u][w][c][lm]+=vg;
            }else{
                const auto[vf,vg]=__self(__self,u-1,uw,c+1,lm&&(uw==ul));
                f[u][w][c][lm]+=vf;
                g[u][w][c][lm]+=vg;
            }
            return make_pair(f[u][w][c][lm],g[u][w][c][lm]);
        };
        auto ans=0ll;
        cir(i,0,l-1) cir(w,1,10) ans+=dfs(dfs,i-1,w,1,false).first;
        cir(w,1,lim[l-1]-'0') ans+=dfs(dfs,l-2,w,1,false).first;
        ans+=dfs(dfs,l-2,lim[l-1]-'0',1,true).first;
        return ans;
    }
    dp(lint v):lim(to_string(v)){reverse(lim.begin(),lim.end());}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint l,r;
    while(cin>>l>>r&&l&&r){
        cout<<dp(r).value()-dp(l-1).value()<<'\n';
    }
    return 0;
}
