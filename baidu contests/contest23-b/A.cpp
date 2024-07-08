#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<VI> p(3,VI(n));
    cir(i,0,n) cin>>p[0][i]>>p[1][i]>>p[2][i];
    for(auto&i:p) sort(i.begin(),i.end());
    lint ans=_inf;
    cir(s,0,(1<<3)) if(__builtin_popcount(s)==2){
        lint anss=0;
        cir(i,0,3){
            if(s&(1<<i)){
                lint ansi=_inf,cx=0;
                const auto cnx=accumulate(
                    p[i].begin(),p[i].end(),(lint)(0));
                cir(x,0,n){
                    ansi=min(ansi,x*p[i][x]-cx+
                        cnx-cx-p[i][x]-(n-x-1)*p[i][x]);
                    cx+=p[i][x];
                }
                anss+=ansi;
            }else{
                lint ansi=_inf;
                const int px=(n/2)-1;
                cir(x,max(px,0),min(n,px+4)){
                    const auto w=p[i][x];
                    lint cnx=0;
                    cir(xm,0,x) cnx+=abs(p[i][xm]-(w-x+xm));
                    cir(xm,x+1,n) cnx+=abs(p[i][xm]-(w+xm-x)); 
                    ansi=min(ansi,cnx);
                }
                anss+=ansi;
            }
        }
        ans=min(ans,anss);
    }
    cout<<ans<<'\n';
    return 0;
}
