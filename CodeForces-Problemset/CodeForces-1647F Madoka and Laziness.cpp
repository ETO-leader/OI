#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
int solve(int mx,const VI&a){
    const int n=a.size();
    VI dx(n,_inf),cx(n);
    vector<VI> D(n,VI(2));
    cir(i,0,mx+1){
        if(!i) dx[i]=0;
        else dx[i]=min((a[i]>dx[i-1]?a[i-1]:_inf),
            (a[i]>a[i-1]?dx[i-1]:_inf));
    }
    if(dx[mx]==_inf) return 0;
    for(int i=n-1;i>mx;--i){
        if(i==n-1) cx[i]=0;
        else cx[i]=min((a[i]>cx[i+1]?a[i+1]:_inf),
            (a[i]>a[i+1]?cx[i+1]:_inf));
    }
    D[mx][0]=0;D[mx][1]=dx[mx];
    cir(i,mx+1,n){
        D[i][1]=_inf;
        if(a[i]>a[i-1])
            D[i][0]=max(D[i][0],D[i-1][0]);
        if(a[i]<a[i-1])
            D[i][1]=min(D[i][1],D[i-1][1]);
        if(D[i-1][1]<a[i])
            D[i][0]=max(D[i][0],a[i-1]);
        if(D[i-1][0]>a[i])
            D[i][1]=min(D[i][1],a[i-1]);
    }
    int res=0;
    cir(i,mx+1,n) res+=((D[i][0])>cx[i]);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n);
    for(auto&i:a) cin>>i;
    const int mx=max_element(a.begin(),
        a.end())-a.begin();
    cout<<[&](){
        int res=solve(mx,a);
        reverse(a.begin(),a.end());
        return res+solve(n-1-mx,a);
    }()<<'\n';
    return 0;
}
