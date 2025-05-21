#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("pub.in");
ofstream ouf("pub.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,p;inf>>n>>p;
    vector<lint> pwx(n*(n+1)+7,1);
    cir(i,1,n*(n+1)+7) pwx[i]=pwx[i-1]*2%p;
    vector f(n+1,vector<lint>(n+7));
    vector<lint> ans(n+1);
    f[0][0]=1;
    cir(i,1,n+1){
        ans[i]=pwx[i*(i+1)/2];
        cir(j,1,i+1){
            cir(k,1,i+1) (f[i][j]+=pwx[(k-1)*(k-2)/2]*f[i-k][j-1])%=p;
            if(j<i) (ans[i]+=p-f[i][j]*ans[j]%p)%=p;
        }
    }
    ouf<<ans[n]<<'\n';
    return 0;
}
