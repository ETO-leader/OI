#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("flip.in");
ofstream fcout("flip.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,m;fcin>>n>>m;
    vector<VI> mp(n);
    cir(i,0,n){
        string s;fcin>>s;
        for(auto&x:s) mp[i].push_back(x-'0');
    }
    vector<vector<VI>> fd(2,vector<VI>(n));
    cir(i,0,n){
        cir(j,0,m) fd[mp[i][j]][i].push_back(j);
    }
    int step=0,ans=0;
    while(true){
        step^=1;VI siz(n);int npos=-1;
        cir(i,0,n){
            if((!fd[step][i].empty())&&
                fd[step][i].back()>npos){
                npos=fd[step][i].back();
                fd[step][i].pop_back();
            }
            siz[i]=npos;
        }
        if(npos<0) break;
        ++ans;
        cir(i,0,n) while((!fd[step^1][i].empty())&&
            fd[step^1][i].back()>siz[i]){
            fd[step^1][i].pop_back();
        }
    }
    fcout<<ans<<'\n';
    return 0;
}
