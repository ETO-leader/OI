#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("perm.in");
ofstream ouf("perm.out");
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
constexpr auto choose_pair(lint x){
    return x*(x-1)%MOD;
}
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,l;inf>>n>>l;
    const auto sqr=(int)(floorl(sqrt(l)));
    vector<int> a(n);
    for(auto&i:a) inf>>i;
    vector<pair<int,int>> q;
    for(auto&x:a){
        if(x>sqr) q.emplace_back(l/x,1);
        else q.emplace_back(x,0); 
    }
    vector<vector<lint>> b(n*2+7,vector<lint>(n*2+7));
    b[0][0]=1;
    cir(i,1,n*2+7) cir(j,0,n*2+7){
        b[i][j]=((j?b[i-1][j-1]:0)+b[i-1][j])%MOD;
    }
    vector<lint> fct(n*2+7,1);
    cir(i,1,n*2+7) fct[i]=fct[i-1]*i%MOD;
    if(n>1){
        sort(q.begin(),q.end());
        vector<vector<array<array<lint,2>,2>>> f(2,vector<array<array<lint,2>,2>>(n+1));
        auto cur=0;
        f[cur][0][0][0]=1;
        auto pre=0,cnt=0;
        for(auto&[v,c]:q){
            clog<<v<<' '<<c<<'\n';
            if(!c){
                f[cur^1]=f[cur];
                ++pre;
            }else{
                cir(c,0,n+1) cir(cl,0,2) cir(cr,0,2) if(f[cur][c][cl][cr]){
                    if(c==1&&cl&&cr) continue;
                    const auto cx=pre-(cnt+c-cl-cr);
                    clog<<"----- "<<c<<' '<<cl<<' '<<cr<<' '<<cx<<'\n';
                    if(cx<0) continue;
                    // Type 0: New segment
                    if((!cl)&&cx){        // Type 0.0 Left Bound
                        (f[cur^1][c+1][true][cr]+=f[cur][c][cl][cr]*cx)%=MOD;
                    }
                    if((!cr)&&cx){        // Type 0.1 Right Bound
                        (f[cur^1][c+1][cl][true]+=f[cur][c][cl][cr]*cx)%=MOD;
                    }
                    if(cx>1){             // Type 0.2 Normal
                        (f[cur^1][c+1][cl][cr]+=f[cur][c][cl][cr]*choose_pair(cx))%=MOD;
                    }
                    // Type 1: Extend an exist segment
                    if(!cl){        // Type 1.0 Left Bound
                        if(c==1&&cr){        // Type 1.0.0 Left & Right
                            (f[cur^1][c][true][cr]+=f[cur][c][cl][cr])%=MOD;
                        }
                        // Type 1.0.1 Left Only
                        (f[cur^1][c][true][cr]+=f[cur][c][cl][cr]*(c-cl-cr)%MOD)%=MOD;
                    }
                    if(!cr){        // Type 1.1 Right Bound
                        if(c==1&&cl){        // Type 1.1.0 Left & Right
                            (f[cur^1][c][cl][true]+=f[cur][c][cl][cr])%=MOD;
                        }
                        // Type 1.1.1 Right Only
                        (f[cur^1][c][cl][true]+=f[cur][c][cl][cr]*(c-cl-cr))%=MOD;
                    }
                    if(cx){         // Type 1.2 Normal
                        (f[cur^1][c][cl][cr]+=f[cur][c][cl][cr]*((c-cl-cr)*2+cl+cr)%MOD*cx)%=MOD;
                    }
                    // Type 2. Merge two exist segments
                    if(c>1){
                        if(c==2&&cl&&cr){        // Type 2.0 Merge Left & Right
                            (f[cur^1][c-1][cl][cr]+=f[cur][c][cl][cr])%=MOD;
                        }
                        if(cl){                  // Type 2.1 Merge Left & Normal
                            (f[cur^1][c-1][cl][cr]+=f[cur][c][cl][cr]*(c-cl-cr))%=MOD;
                        }
                        if(cr){                  // Type 2.2 Merge Normal & Right
                            (f[cur^1][c-1][cl][cr]+=f[cur][c][cl][cr]*(c-cl-cr))%=MOD;
                        }
                        // Type 2.3 Merge Normal & Normal
                        (f[cur^1][c-1][cl][cr]+=f[cur][c][cl][cr]*choose_pair(c-cl-cr))%=MOD;
                    }
                }
                ++cnt;
            }
            for(auto&x:f[cur]) for(auto&w:x) memset(w.data(),0,sizeof(w));
            cur^=1;
        }
        auto ans=0ll;
        cir(c,0,n+1) cir(cl,0,2) cir(cr,0,2) if(f[cur][c][cl][cr]){
            const auto cx=pre-(cnt+c-cl-cr);
            if(cx<0) continue;
            const auto vldpos=(!c)?1:(c+1-cl-cr);
            if(!vldpos){
                if(!cx) (ans+=f[cur][c][cl][cr])%=MOD;
                continue;
            }
            const auto spl=b[cx+vldpos-1][vldpos-1];
            const auto uod=fct[c-cl-cr];
            const auto vod=fct[cx];
            (ans+=f[cur][c][cl][cr]*spl%MOD*uod%MOD*vod)%=MOD;
        }
        ouf<<ans<<'\n';
    }else{
        ouf<<1<<'\n';
    }
    return 0;
}

