#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("c.in");
ofstream fcout("c.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;fcin>>n;vector<lint> a(n);
    for(auto&i:a) fcin>>i;
    vector f(n,vector<lint>(8192));
    f[0][0]=0;f[0][a[0]]=1;
    cir(i,1,n){
        vector<lint> vaild;
        cir(s,0,(1<<i)){
            auto w=a[i];
            cir(x,0,i) if(s&(1<<x)) w^=a[x];
            vaild.push_back(w);
            clog<<i<<' '<<w<<'\n';
        }
        f[i]=f[i-1];
        for(auto&w:vaild){
            f[i][w]=max(f[i][w],1ll);
            cir(las,0,w) f[i][w]=max(f[i][w],f[i-1][las]+1);
        }
    }
    fcout<<*ranges::max_element(f[n-1])<<'\n';
    return 0;
}
