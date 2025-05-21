#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("zu.in");
ofstream ouf("zu.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
class randomengine{
private:
    mt19937_64 eng;
public:
    auto randbit(long double p=0.5l){
        return uniform_real_distribution<long double>(0,1)(eng)<p;
    }
    randomengine():eng(random_device().operator()()){}
} rnd;
class randomchecker{
private:
    vector<vector<int>> cur;
    lint curans;
    auto build(const int n){
        cur.resize(n,vector<int>(n));
        for(auto&x:cur) for(auto&i:x) i=rnd.randbit(0.99);
        cur[0][0]=cur[n-1][n-1]=1;
    }
    auto check(const int n){
        vector<vector<lint>> f(n,vector<lint>(n));
        f[0][0]=1;
        cir(i,0,n) cir(j,0,n) if(cur[i][j]){
            f[i][j]+=(i?f[i-1][j]:0)+(j?f[i][j-1]:0);
        }
        vector<vector<lint>> g(n,vector<lint>(n));
        g[n-1][n-1]=1;
        for(auto i=n-1;~i;--i) for(auto j=n-1;~j;--j) if(cur[i][j]){
            g[i][j]+=(i+1<n?g[i+1][j]:0)+(j+1<n?g[i][j+1]:0);
        }
        return pair(f,g);
    }
public:
    auto solve(lint w){
        const auto n=30;
        build(n);
        curans=check(n).first[n-1][n-1];
        if(curans<w) return vector<vector<int>>();
        while(true){
            const auto[f,g]=check(n);
            auto p=pair(-1,-1);
            auto wx=-1ll;
            cir(i,0,n) cir(j,0,n) if((i||j)&&(i<n-1||j<n-1)&&cur[i][j]){
                const auto c=f[i][j]*g[i][j];
                if(curans-c<w||(!c)||c<wx) continue;
                wx=c;p=pair(i,j);
            }
            if(wx==-1) return vector<vector<int>>();
            curans-=wx;
            cur[p.first][p.second]=0;
            if(curans==w) break;
        }
        return cur;
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) []{
        lint n;inf>>n;
        auto w=randomchecker().solve(n);
        while(w.empty()) w=randomchecker().solve(n);
        ouf<<w.size()<<'\n';
        for(auto&x:w){
            for(auto&i:x) ouf<<i<<' ';
            ouf<<'\n';
        }
    }();
    return 0;
}
