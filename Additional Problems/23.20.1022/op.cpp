#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("op.in");
ofstream fcout("op.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
using __int=__int128;
ostream&operator<<(ostream&os,__int v){
    if(v<0) cout<<'-',v=-v;
    if(v>9) os<<v/10;
    return (os<<(int)(v%10));
}
array<unordered_map<lint,__int>,57> f;
__int dfs(int s,lint x,const int k,lint pw){
    if(!x) return 1;
    if(!s) return x;
    if(s==1) return (x-k+x%k+2)*(x/k)/2;
    if(f[s].count(x)) return f[s][x];
    lint p=pw;__int res=0;
    while(p<x+1) res+=dfs(s-1,x-p,k,pw/k),p+=pw;
    return f[s][x]=res;
}
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int k;lint x,pw=1,cx=0;fcin>>k>>x;
    while(x>pw-1){
        fcout<<dfs(cx,x,k,pw)<<'\n';
        pw*=k;++cx;
    }
    return 0;
}
