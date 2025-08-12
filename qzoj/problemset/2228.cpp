#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<tuple<int,int,int>> x(n);
    cir(i,0,n){
        int a,b,c;cin>>a>>b>>c;
        x[i]={a+b+c,a,-(i+1)};
    }
    sort(x.begin(),x.end(),greater<>());
    cir(i,0,5){
        cout<<-get<2>(x[i])<<' '<<get<0>(x[i])<<'\n';
    }
    return 0;
}
