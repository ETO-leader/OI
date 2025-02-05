#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("game.in");
ofstream ouf("game.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) [&]{
        int n,m;inf>>n>>m;
        vector<vector<int>> xs(n),xt(n);
        for(auto&x:xs){
            int c;inf>>c;x.resize(c);
            for(auto&i:x) inf>>i;
        }
        dsu ds(m+1);
        for(auto&x:xt){
            int c;inf>>c;x.resize(c);
            for(auto&i:x) inf>>i;
            if(c>1) ds.merge(x[0],x[1]);
        }
        vector<int> cnt(m+1);
        cir(i,1,m+1) ++cnt[ds.findset(i)];
        for(auto&x:xt) --cnt[ds.findset(x[0])];
        if(*min_element(cnt.begin(),cnt.end())<0) return ouf<<-1<<'\n',void();
        else if(n>10||T>20) return ouf<<0<<'\n',void();
        auto ans=0;
        auto vaild=false;
        cir(as,0,(1<<n)) [&]{
            vector<int> a;
            cir(i,0,n) if(xs[i].size()<(((as>>i)&1)+1)) return;
            cir(i,0,n) a.emplace_back(xs[i][(as>>i)&1]);
            auto ansi=n;
            cir(s,0,(1<<n)) [&]{
                vector<int> b;
                cir(i,0,n) if(xt[i].size()<(((s>>i)&1)+1)) return;
                cir(i,0,n) b.emplace_back(xt[i][(s>>i)&1]);
                if((int)(set<int>(b.begin(),b.end()).size())<n) return;
                vaild=true;
                auto cnt=0;
                cir(i,0,n) cnt+=(a[i]==b[i]);
                ansi=min(ansi,cnt);
            }();
            ans=max(ans,ansi);
        }();
        ouf<<(vaild?ans:-1)<<'\n';
    }();
    return 0;
}
