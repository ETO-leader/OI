#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector f(n+1,vector(2,vector(2,_inf)));
        f[0][0][0]=0;
        cir(i,0,n){
            if(!a[i]){
                f[i+1][0][0]=min({
                    f[i][0][0],
                    f[i][0][1],
                    f[i][1][0],
                    f[i][1][1]
                });
            }else if(a[i]<3){
                cir(ax,0,2) cir(bx,0,2) cir(ay,0,2) cir(by,0,2){
                    if(!(ax||ay)) continue;
                    // if(!i) clog<<"    "<<ax<<' '<<ay<<' '<<bx<<' '<<by<<'\n';
                    f[i+1][ay][by]=min(f[i+1][ay][by],f[i][ax][bx]+ay+by);
                }
            }else if(a[i]<5){
                cir(ax,0,2) cir(bx,0,2) cir(ay,0,2) cir(by,0,2){
                    if(!((ax||ay)&&(bx||by))) continue;
                    f[i+1][ay][by]=min(f[i+1][ay][by],f[i][ax][bx]+ay+by);
                }
            }
            f[i+1][0][0]=min({
                f[i+1][0][0]-1,
                f[i][0][0],
                f[i][0][1],
                f[i][1][0],
                f[i][1][1]
            })+1;
            // cir(ax,0,2) cir(bx,0,2) clog<<i<<' '<<ax<<' '<<bx<<' '<<f[i+1][ax][bx]<<'\n';
        }
        cout<<min({f[n][0][0],f[n][0][1],f[n][1][0],f[n][1][1]})<<'\n';
    }();
    return 0;
}
