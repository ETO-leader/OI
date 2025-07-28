#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector c(n,vector<int>(n));
    for(auto&x:c) for(auto&i:x) cin>>i;
    vector<int> a(n);
    cir(i,1,n){
        unordered_set<int> vals;
        cir(j,0,n) vals.emplace(c[i][j]-c[i-1][j]);
        if(vals.size()!=1) exit((cout<<"No"<<'\n',0));
        a[i]=a[i-1]+*vals.begin();
    }
    const auto uval=*ranges::min_element(a);
    for(auto&x:a) x-=uval;
    vector<int> b(n);
    cir(i,0,n) b[i]=c[0][i]-a[0];
    if(*ranges::min_element(b)<0) exit((cout<<"No"<<'\n',0));
    cout<<"Yes"<<'\n';
    for(auto&x:a) cout<<x<<' ';
    cout<<'\n';
    for(auto&x:b) cout<<x<<' ';
    cout<<'\n';
    return 0;
}
