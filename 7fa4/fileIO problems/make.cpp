#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("make.in");
ofstream ouf("make.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;vector<lint> a(n);
    for(auto&i:a) inf>>i;
    auto pre=a;
    pre.insert(pre.begin(),0);
    cir(i,1,n+1) pre[i]+=pre[i-1];
    auto ans=0ll;
    __gnu_pbds::gp_hash_table<lint,lint> cntv;
    cir(l,0,n) cir(r,l,n) ++cntv[pre[r+1]-pre[l]];
    ans-=cntv[0];
    cir(l,0,n) cir(r,l,n){
        const auto curw=pre[r+1]-pre[l];
        ans-=(cntv[curw*(-2)]-(!curw))*3;
    }
    // __gnu_pbds::gp_hash_table<lint,lint> cnt;
    vector<lint> cnt(30000000);
    auto ad=15000000;
    cir(i,1,n+1){
        cir(x,1,n+1) cir(y,x,n+1) ++cnt[pre[y]-pre[x-1]-pre[i-1]+ad];
        cir(x,1,n+1) cir(y,x,n+1) ans+=cnt[-(pre[y]-pre[x-1]+pre[i])+ad]; 
    }
    ouf<<ans/6<<'\n';
    return 0;
}
