#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("easy.in");
ofstream fcout("easy.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} set_fileio;
using lint=long long;
using VI=vector<lint>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,p;fcin>>n>>p;VI f(max(n+1,4));
    f[2]=1;f[3]=2;
    cir(i,4,n+1)
        (f[i]=f[i-1]+f[i-2]*(i-1))%=p;
    lint ans=0;
    cir(i,3,n+1){
        ans^=(([p](int n){
            lint res=1;
            cir(i,3,n+1) (res*=i)%=p;
            return res;
        }(i)-f[i]+p)%p);
    }
    fcout<<ans<<'\n';
    return 0;
}
