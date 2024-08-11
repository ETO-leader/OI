#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("wizard.in");
ofstream fcout("wizard.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;fcin>>n>>m;
    vector w(n,vector<int>(n)),c(n,vector<int>(n));
    for(auto&x:w) for(auto&i:x) fcin>>i;
    for(auto&x:c) for(auto&i:x) fcin>>i;
    vector<int> rg(n);
    iota(rg.begin(),rg.end(),0);
    mt19937 rnd(random_device().operator()());
    auto ans=numeric_limits<int>::max();
    auto cx=0;
    cir(i,0,100000000){
        if(!(i%100000)) cerr<<i<<'\n';
        shuffle(rg.begin(),rg.end(),rnd);
        auto qwq=0,qaq=0;
        cir(i,1,n){
            qwq+=w[rg[i-1]][rg[i]];
            qaq+=c[rg[i-1]][rg[i]];
        }
        if(qaq<m+1) ans=min(ans,qwq),++cx;
    }
    clog<<cx<<'\n';
    fcout<<ans<<'\n';
    return 0;
}
