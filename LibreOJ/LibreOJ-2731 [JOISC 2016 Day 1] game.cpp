#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=unsigned long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<string> gr(3);
    for(auto&i:gr) cin>>i;
    const auto empty=[&](auto x,auto y){
        return gr[x][y]=='x';
    };
    if([&]{
        if(empty(0,0)||empty(2,0)||empty(0,n-1)||empty(2,n-1)) return false;
        cir(i,0,n-1) if((empty(0,i)&&empty(0,i+1))||(empty(2,i)&&empty(2,i+1))) return false;
        return true;
    }()){                              // vaild
        vector A(n*3+1,vector<lint>(3));
        cir(i,0,n*3+1){
            A[i][0]=1;
            A[i][1]=i;
            A[i][2]=i*(i-1)%MOD;
        }
        vector<lint> f(n*3+1),g(n*3+1);
        auto lf=f,lg=g;
        f[0]=1;
        auto p=0;
        cir(i,0,n){
            const auto uw=empty(0,i)+empty(2,i);
            swap(f,lf);swap(g,lg);
            ranges::fill(f,0);
            ranges::fill(g,0);
            if(empty(1,i)){
                auto prelf=0ull,prelg=0ull;
                // Update: g
                cir(x,0,p+1){
                    prelf+=lf[x];
                    prelf-=(prelf>MOD-1?MOD:0);
                    prelg+=lg[x];
                    prelg-=(prelg>MOD-1?MOD:0);
                    // uw = 0: ord(f) > ord(g)
                    g[x+1]+=uw?(prelf*A[p-x+uw][uw])%MOD:0;
                    g[x+1]-=(g[x+1]>MOD-1?MOD:0);
                    g[x+2]+=(uw>1)?(prelf*2*(p-x+1)*(x+1))%MOD:0;
                    g[x+2]-=(g[x+2]>MOD-1?MOD:0);
                }
                // Update: f
                cir(x,0,p+1){
                    prelg+=MOD-lg[x];
                    prelg-=(prelg>MOD-1?MOD:0);
                    (f[x+uw+1]+=(prelf+prelg)*A[x+uw][uw])%=MOD;
                }
            }else{
                cir(x,0,p+1) f[0]+=lf[x]+lg[x];
                f[0]%=MOD;
                (f[0]*=A[p+uw][uw])%=MOD;
            }
            p+=uw+empty(1,i);
        }
        cout<<accumulate(f.begin(),f.end(),0ull)%MOD<<'\n';
    }else{                             // Invaild
        cout<<0<<'\n';
    }
    return 0;
}
