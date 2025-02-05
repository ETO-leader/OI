#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("station.in");
ofstream ouf("station.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m,x;inf>>n>>m>>x;--x;
    vector<int> mx(n,-1),mn(n,n+7);
    vector<bool> lp(n),rp(n);
    cir(i,0,m){
        int l,r;inf>>l>>r;--l;--r;
        mx[l]=max(mx[l],r);
        mn[r]=min(mn[r],l);
        lp[l]=true;rp[r]=true;
    }
    auto&rig=mx,&lef=mn;
    cir(i,1,n) rig[i]=max(rig[i],rig[i-1]);
    for(auto i=n-2;~i;--i) lef[i]=min(lef[i],lef[i+1]);
    auto pl=x,pr=x;
    cir(i,0,n){
        if(lef[pl]<n+7) pl=lef[pl];
        if(rig[pr]>-1) pr=rig[pr];
    }
    cir(i,pl,x) if(lp[i]) ouf<<i+1<<' ';
    cir(i,x+1,pr+1) if(rp[i]) ouf<<i+1<<' ';
    ouf<<'\n';
    return 0;
}
