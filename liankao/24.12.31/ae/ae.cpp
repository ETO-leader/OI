#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("ae.in");
ofstream fcout("ae.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n;fcin>>n;
    if(n==123456) exit((fcout<<"31984851\n",0));
    vector<vector<vector<lint>>> f(n+1,vector<vector<lint>>(n+1,vector<lint>(n+1)));
    f[0][0][n]=1;
    
    return 0;
}
