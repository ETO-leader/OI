#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
#define putstr(str) {cout<<str<<'\n';continue;}
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    vector<int> v(n),sx(n),c0(n),fx(n,-1);
    vector<map<int,int>> apd(2);
    cir(i,0,n){
        cin>>v[i];sx[i]=(i?sx[i-1]:0)^v[i];
        fx[i]=(apd[!(i&1)].count(sx[i])?
            apd[!(i&1)][sx[i]]+1:-1);
        apd[i&1][sx[i]]=i;
        c0[i]=(i?c0[i-1]:0)+(!v[i]);
    }
    cir(i,0,q){
        int l,r;cin>>l>>r;--r,--l;
        if(c0[r]-c0[l]+(!v[l])==r-l+1)
            putstr("0");
        if(sx[r]^(!l?0:sx[l-1]))
            putstr("-1");
        if(!((r-l+1)&1)){
            if(!v[r]) --r;
            else if(!v[l]) ++l;
        }
        if((r-l+1)&1) putstr("1");
        putstr((fx[r]>l?"2":"-1"));
    }
    return 0;
}
