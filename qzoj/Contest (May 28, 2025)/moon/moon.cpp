#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("moon.in");
ofstream ouf("moon.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto eps=1e-12l;
class equation{
public:
    static auto gauss(vector<vector<int>> x,int n,int m){
        vector<vector<long double>> a(n,vector<long double>(m));
        cir(i,0,n) cir(j,0,m) a[i][j]=x[i][j];
        auto r=0;
        vector pos(m,-1);
        cir(i,0,m){
            if(r>n-1) continue;
            auto u=r;
            cir(p,r+1,n) if(abs(a[p][i])>abs(a[u][i])) u=p;
            if(abs(a[u][i])<eps) continue;
            swap(a[r],a[u]);
            pos[i]=r;
            cir(x,r+1,n) if(abs(a[x][i])>eps){
                const auto w=a[x][i]/a[r][i];
                cir(j,i,m) a[x][j]-=w*a[r][j];
            }
            ++r;
        }
        vector<long double> ans(m);
        cir(i,0,m) if(pos[i]<0) ans[i]=1; 
        for(auto i=m-1;~i;--i) if(pos[i]>-1){
            auto cur=0.0l;
            cir(j,i+1,m) cur-=ans[j]*a[pos[i]][j];
            ans[i]=cur/a[pos[i]][i];
        }
        return ans;
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<int> d(m);
    for(auto&x:d) inf>>x;
    vector<vector<int>> a(n,vector<int>(m));
    cir(i,0,m){
        cir(x,0,d[i]){
            int c;inf>>c;--c;
            a[c][i]=1;
        }
    }
    const auto val=equation::gauss(a,n,m);
    vector<int> ansa,ansb;
    cir(i,0,m){
        if(abs(val[i])<eps) continue;
        (val[i]<0?ansa:ansb).emplace_back(i);
    }
    ouf<<ansa.size()<<' '<<ansb.size()<<'\n';
    for(auto&x:ansa) ouf<<x+1<<' ';
    ouf<<'\n';
    for(auto&x:ansb) ouf<<x+1<<' ';
    ouf<<'\n';
    return 0;
}
