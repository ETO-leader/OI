#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x,y;cin>>n>>x>>y;
    vector<int> v(n),pos(n);
    for(auto&i:v) cin>>i;
    int l,r,rl,mx,mn;
    auto reset=[&](int p,int lx){
        l=lx+1;r=p;rl=-1;mx=0;mn=_inf;
    };
    auto outr=[&](int i){
        return v[i]>x||v[i]<y;
    };
    reset(0,-1);
    int pl=n;
    for(int i=n-1;~i;--i)
        pos[i]=(pl=(outr(i)?i:pl));
    lint ans=0;
    while(r<n){
        while(r<n&&outr(r)) ++r,reset(r,r-1);
        if(r==n) break;
        mx=max(mx,v[r]);mn=min(mn,v[r]);
        if(mx==x&&mn==y){
            if(rl==-1) rl=r;
            ans+=lint(rl-l+1)*(pos[r]-r);
            reset(r+(rl==r),rl);
        }else{
            if(v[r]==x||v[r]==y) rl=r;
            ++r;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
