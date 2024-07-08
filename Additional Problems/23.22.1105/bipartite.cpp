#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("bipartite.in");
ofstream fcout("bipartite.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n;fcin>>n;
    fcout<<n<<'\n';
    return 0;
}
