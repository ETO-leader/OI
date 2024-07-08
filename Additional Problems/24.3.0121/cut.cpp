#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("cut.in");
ofstream fcout("cut.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
struct seg{
    int l,r;
    auto cut(int x){
        if(x<l||r<x) return;
        x-l<r-x?l=x:r=x;
    }
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,m,id;fcin>>n>>m>>id;
    vector<seg> sgk(n);
    for(auto&[l,r]:sgk) fcin>>l>>r;
    cir(i,0,m){
        int x,l,r;fcin>>x>>l>>r;--l;--r;
        cir(i,l,r+1) sgk[i].cut(x);
    }
    for(auto&[l,r]:sgk) fcout<<l<<' '<<r<<'\n';
    return 0;
}
