#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
class check{
private:
    vector<vector<array<array<array<lint,2>,2>,2>>> f;
    vector<vector<array<array<array<bool,2>,2>,2>>> vis;
    vector<lint> wx,vx,arrl,arrr;
    auto dfs(int u,int w,bool liml,bool limr,bool fst){
        if(u<0) return 0ll;
        auto&fx=f[u][w][liml][limr][fst];
        if(vis[u][w][liml][limr][fst]) return fx;
        vis[u][w][liml][limr][fst]=true;
        fx=-_infl;
        const auto lrb=(liml?arrl[u]:0);
        const auto upb=(limr?arrr[u]:9);
        cir(i,lrb,upb+1) if(w-i*wx[u]>-1){
            if(u>490&&fst) clog<<lrb<<' '<<upb<<' '<<i<<' '<<fx<<' '<<i*wx[u]<<' '<<w<<'\n';
            if(fst&&(!i)) continue;
            fx=max(fx,dfs(u-1,w-i*wx[u],liml&&(i==lrb),limr&&(i==upb),false)+i*vx[u]);
        }
        return fx;
    }
public:
    auto join(string arl,string arr,const int m){
        const auto n=(int)(arr.size());
        for(auto x:{&wx,&vx}) reverse(x->begin(),x->end());
        for(auto x:{&arl,&arr}) reverse(x->begin(),x->end());
        while(arl.size()<arr.size()) arl.push_back('0');
        arrl=vector<lint>(arl.begin(),arl.end());
        arrr=vector<lint>(arr.begin(),arr.end());
        for(auto&i:arrl) i-='0';
        for(auto&i:arrr) i-='0';
        f.resize(n,vector<array<array<array<lint,2>,2>,2>>(m+1));
        vis.resize(n,vector<array<array<array<bool,2>,2>,2>>(m+1));
        auto ans=max<lint>(dfs(n-1,m,true,true,true),-1);
        auto nx=n;
        while(!arrl.back()){
            --nx;
            for(auto x:{&arrl,&arrr}) x->pop_back();
            for(auto x:{&wx,&vx}) x->erase(x->begin());
            // clog<<"---------------------------------------\n";
            ans=max<lint>(ans,dfs(nx-1,m,true,false,true));
            // clog<<dfs(nx-1,m,true,false,true)<<' '<<arrl[nx-1]<<' '<<arrr[nx-1]<<'\n';
        }
        return ans;
    }
    check(auto _wx,auto _vx):wx(_wx),vx(_vx){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    string l,r;cin>>l>>r;
    vector<lint> wx(n),vx(n);
    for(auto&i:wx) cin>>i;
    for(auto&i:vx) cin>>i;
    cout<<check(wx,vx).join(l,r,m)<<'\n';
    return 0;
}
