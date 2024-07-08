#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("magic.in");
ofstream fcout("magic.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,m;fcin>>n>>m;vector<int> ans(n+1,1);
    vector<vector<int>> oks(n+1,vector<int>(n+2));
    cir(i,0,m){
        int op;fcin>>op;
        if(op==1){
            int x;fcin>>x;
            cir(i,1,n+1) oks[i][(x+i-1)/i]=true;
            cir(i,1,n+1) while(oks[i][ans[i]]){
                ++ans[i];
            }
        }else{
            int l,r;fcin>>l>>r;
            fcout<<accumulate(ans.begin()+l,
                ans.begin()+r+1,(lint)(0))<<'\n';
        }
    }
    return 0;
}