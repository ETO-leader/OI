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
static constexpr auto eps=1e-8l;
class equation{
public:
    static auto gauss(vector<vector<lint>> x){
        const auto n=(int)(x.size());
        vector<vector<long double>> a(n,vector<long double>(n+1));
        cir(i,0,n) cir(j,0,n+1) a[i][j]=x[i][j];
        cir(i,0,n){
            auto p=i;
            while(p<(int)(a.size())&&(abs(a[p][i])<eps)) ++p;
            if(p==(int)(a.size())) continue;
            swap(a[i],a[p]);
            cir(x,i+1,n) if(abs(a[x][i])>eps){
                const auto w=a[x][i]/a[i][i];
                cir(j,i,n+1) a[x][j]-=w*a[i][j];
            }
        }
        // clog<<"\n\n\n";
        // for(auto&x:a){
        //     for(auto&i:x) clog<<i<<' ';
        //     clog<<'\n';
        // }
        // clog<<"\n\n\n";
        vector<long double> ans(n);
        for(auto i=n-1;~i;--i) if(abs(a[i][i])>eps){
            auto cur=a[i][n];
            cir(j,i+1,n) cur-=ans[j]*a[i][j];
            ans[i]=cur/a[i][i];
        }else{
            // clog<<"Fail.\n";
            ans[i]=1;
        }
        return ans;
    }
};
template<const int ulen>
class base{
private:
    vector<bitset<ulen>> a;
public:
    auto emplace(bitset<ulen> x){
        cir(i,0,ulen) if(x[i]){
            if(a[i].none()) return a[i]=x,true;
            x^=a[i];
        }
        return false;
    }
    base():a(ulen){}
};
static constexpr auto maxn=512;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<int> d(m);
    for(auto&x:d) inf>>x;
    vector<vector<lint>> a(m+n,vector<lint>(m+1));
    base<maxn> cur;
    auto cnt=n-1;
    cir(i,0,m){
        bitset<maxn> u;
        u.reset();
        cir(x,0,d[i]){
            int c;inf>>c;--c;
            u.set(c);
            a[c][i]=1;
        }
        ++cnt;
        a[cnt][i]=1;
        a[cnt][m]=1;
    }
    for(auto&x:a){
        for(auto&i:x) clog<<i<<' ';
        clog<<'\n';
    }
    clog<<'\n';
    base<maxn> chk;
    vector<int> fail;
    cir(i,0,n+m){
        bitset<maxn> u;
        u.reset();
        cir(p,0,m) u[p]=a[i][p]; 
        if(!chk.emplace(u)) fail.emplace_back(i);
    }
    for(auto&x:views::reverse(fail)) a.erase(a.begin()+x);
    clog<<"\n\n\n";
    for(auto&x:a){
        for(auto&i:x) clog<<i<<' ';
        clog<<'\n';
    }
    // clog<<"SIZ = "<<a.size()<<'\n';
    a.resize(m);
    const auto val=equation::gauss(a);
    // for(auto&x:val) clog<<x<<'\n';
    // clog<<'\n';
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
