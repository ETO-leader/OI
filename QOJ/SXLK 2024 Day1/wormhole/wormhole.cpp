#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("wormhole.in");
ofstream ouf("wormhole.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
static constexpr auto MOD=(int)(998244353);
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int c,n,m,k;inf>>c>>n>>m>>k;
    if(c<5){
        vector<vector<int>> gr(n,vector<int>(m));
        cir(i,0,m*n){
            int u,v,w;inf>>u>>v>>w;--u;--v;--w;
            gr[u][w]=v;
        }
        auto extend=[&](auto __self,int x,int c,vector<int> ec){
            if(x>n-1){
                cir(i,0,n) cir(x,0,c-1) if(gr[gr[i][c-1]][x]!=gr[gr[i][x]][c-1]) return 0ll;
                if(c==m+k) return 1ll;
                return __self(__self,0,c+1,vector<int>(n));
            }
            auto res=0ll;
            cir(v,0,n) if(!ec[v]){
                gr[x].emplace_back(v);
                auto nec=ec;
                nec[v]=true;
                (res+=__self(__self,x+1,c,nec))%=MOD;
                gr[x].pop_back();
            }
            return res;
        };
        ouf<<extend(extend,0,m+1,vector<int>(n))<<'\n';
    }else{
        auto ans=1ll;
        cir(i,1,n+1) (ans*=i)%=MOD;
        ouf<<ans<<'\n';
    }
    return 0;
}
