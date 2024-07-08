#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("perm.in");
ofstream fcout("perm.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,p;fcin>>n>>p;
    vector<VI> ans(n,VI(n));
    VI a(n);iota(a.begin(),a.end(),0);
    do{
        VI rev(n);
        cir(i,0,n) rev[a[i]]=i;
        int x=0,y=0;
        cir(i,1,n) x+=(a[i]>a[i-1]);
        cir(i,1,n) y+=(rev[i]>rev[i-1]);
        (++ans[x][y])%=p;
    }while(next_permutation(a.begin(),a.end()));
    for(auto&i:ans){
        for(auto&j:i) fcout<<j<<' ';
        fcout<<'\n';
    }
    return 0;
}
