#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("parade.in");
ofstream ouf("parade.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;vector a(n,vector<int>(m));
    for(auto&x:a) for(auto&i:x) inf>>i;
    auto check=[&](){
        vector cx(n,vector<int>(n)),cy(n,vector<int>(n));
        for(auto i=n-1;~i;--i) for(auto j=m-1;~j;--j){
            cx[i][j]=i;cy[i][j]=j;
            if(a[i][j]){
                cx[i][j]=cy[i][j]=-1;
            }else{
                if(i<n-1) cx[i][j]=max(cx[i][j],cx[i+1][j]);
                if(j<m-1) cy[i][j]=max(cy[i][j],cy[i][j+1]);
            }
        }
        auto ans=0;
        cir(x,0,n) cir(y,0,m){
            auto p=cx[x][y];
            for(auto q=max(ans-cx[x][y]+x+y,y+1);q<cy[x][y]+1;++q){
                if(cx[x][q]<cx[x][y]) continue;
                while(cy[p][y]<q) --p;
                if(p==x) break;
                ans=max(ans,p+q-x-y);
            }
        }
        return ans*2;
    };
    auto ans=check();
    for(auto&x:a) reverse(x.begin(),x.end());
    ans=max(ans,check());
    ouf<<ans<<'\n';
    return 0;
}
