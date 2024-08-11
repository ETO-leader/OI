// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("enum.in");
ofstream fcout("enum.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
class subtask_k2{
private:
    static constexpr auto k=2;
public:
    auto play(vector<lint> a,vector<lint> b){
        vector<vector<int>> st((1<<k)-1);
        cir(i,0,k){
            cir(j,1,(1<<k)) if((j/(1<<i))%2){
                st[j-1].push_back(i);
            }
        }
        const auto len=(1<<k)-1;
        auto ans=0ll;
        auto dfs=[&](auto __self,lint w)->void {
            if(!(*max_element(b.begin(),b.end()))){
                ans=max(ans,w);
                return;
            }
            cir(u,0,len){
                auto mn=numeric_limits<lint>::max();
                for(auto&i:st[u]) mn=min(mn,b[i]);
                if(!mn) continue;
                for(auto&i:st[u]) b[i]-=mn;
                __self(__self,w+a[u]*mn);
                for(auto&i:st[u]) b[i]+=mn;
            }
        };
        dfs(dfs,0);
        fcout<<ans<<'\n';
    }
};
class subtask_k3{
private:
    static constexpr auto k=3;
public:
    auto play(vector<lint> a,vector<lint> b){
        vector st((1<<k)-1,vector<bool>(3));
        cir(i,0,k){
            cir(j,1,(1<<k)) if((j/(1<<i))%2){
                st[j-1][i]=true;
            }
        }
        const auto len=(1<<k)-1;
        vector f(31,vector(len+1,vector(10,vector(10,vector<lint>(10)))));
        vector vis(31,vector(len+1,vector(10,vector(10,vector<lint>(10)))));
        auto dfs=[&](auto __self,int p,int i,int wa,int wb,int wc)->lint {
            for(auto w:{wa,wb,wc}) if(w<0||w>9) return -_infl;
            if(p<0) return 0ll;
            auto&fx=f[p][i][wa][wb][wc];
            if(vis[p][i][wa][wb][wc]) return fx;
            vis[p][i][wa][wb][wc]=true;
            if(i==len){
                for(auto c=-1;auto wi:{&wa,&wb,&wc}){
                    ++c;
                    ((*wi)<<=1)+=(((b[c]<<1)>>p)&1);
                }
                return fx=__self(__self,p-1,0,wa,wb,wc);
            }
            fx=__self(__self,p,i+1,wa,wb,wc);
            for(auto c=-1;auto wi:{&wa,&wb,&wc}) (*wi)-=st[i][++c];
            return fx=max(fx,__self(__self,p,i+1,wa,wb,wc)+(a[i]<<p));
        };
        fcout<<dfs(dfs,30,0,0,0,0)<<'\n';
    }
};
class subtask_k4{
private:
    static constexpr auto k=4;
    // vector<vector<vector<lint>>> f;
    array<array<array<lint,10000>,20>,2> f;
    vector<vector<int>> st;
    vector<lint> a,b;
    const auto fw(int p,int i,int wa,int wb,int wc,int wd){
        auto res=false;
        if(wa<0||wa>8) res=true;
        if(wb<0||wb>8) res=true;
        if(wc<0||wc>8) res=true;
        if(wd<0||wd>8) res=true;
        if(res) return -_infl;
        if(p<0) return 0ll;
        return f[p&1][i][wa*1000+wb*100+wc*10+wd];
    }
    auto upd(int p,int i,int wa,int wb,int wc,int wd){
        const auto w=wa*1000+wb*100+wc*10+wd;
        auto&fx=f[p&1][i][w];
        const auto len=(1<<k)-1;
        if(i==len){
            return fx=fw(p-1,0,(wa<<1)+(((b[0]<<1)>>p)&1),(wb<<1)+(((b[1]<<1)>>p)&1),(wc<<1)+(((b[2]<<1)>>p)&1),(wd<<1)+(((b[3]<<1)>>p)&1));
        }
        return fx=max(fw(p,i+1,wa,wb,wc,wd),fw(p,i+1,wa-st[i][0],wb-st[i][1],wc-st[i][2],wd-st[i][3])+(a[i]<<p));
    }
public:
    auto play(vector<lint> ax,vector<lint> bx){
        a=ax;b=bx;
        st=vector((1<<k)-1,vector<int>(4));
        cir(i,0,k){
            cir(j,1,(1<<k)) if((j/(1<<i))%2){
                st[j-1][i]=true;
            }
        }
        const auto len=(1<<k)-1;
        memset(f.begin(),0,sizeof(f));
        cir(p,0,31){
            memset(f[p&1].begin(),0,sizeof(f[p&1]));
            for(auto wx=len;~wx;--wx) cir(wa,0,9) cir(wb,0,9) cir(wc,0,9) cir(wd,0,9){
                upd(p,wx,wa,wb,wc,wd);
            }
        }
        fcout<<fw(30,0,0,0,0,0)<<'\n';
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;fcin>>T;
    subtask_k4 subk4;
    while(T--) [&](){
        int k;fcin>>k;
        vector<lint> a((1<<k)-1),b(k);
        for(auto&i:a) fcin>>i;
        for(auto&i:b) fcin>>i;
        if(k==2) return subtask_k2().play(a,b);
        if(k==3) return subtask_k3().play(a,b);
        subk4.play(a,b);
    }();
    return 0;
}
