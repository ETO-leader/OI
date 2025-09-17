#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;
using ll = long long;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; ll m;
    if(!(cin>>n>>m)) return 0;
    vector<array<ll,3>> a(2*n);
    cir(i,0,n){
        ll l,r;cin>>l>>r;
        if(l>r) r+=m;
        a[i]={l,r,i};
    }
    sort(a.begin(),a.begin()+n,[](auto &x,auto &y){return x[0]<y[0];});
    cir(i,0,n) a[i+n]={a[i][0]+m,a[i][1]+m,a[i][2]};
    int N=2*n;
    vector<vector<int>> st(20,vector<int>(N));
    int j=0;
    cir(i,0,N){
        while(j<N && a[j][0]<=a[i][1]) ++j;
        st[0][i]=j-1;
    }
    for(int k=1;k<20;++k) cir(i,0,N) st[k][i]=st[k-1][st[k-1][i]];
    vector<int> answ(n);
    cir(i,0,n){
        ll up=a[i][0]+m; int ans=0,p=i;
        for(int k=19;k>=0;--k)
            if(st[k][p]<N && a[st[k][p]][1]<up) ans+=1<<k,p=st[k][p];
        answ[a[i][2]]=ans+2;
    }
    cir(i,0,n) cout<<answ[i]<<(i+1==n?'\n':' ');
    return 0;
}
