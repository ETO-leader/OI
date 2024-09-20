#include<bits/stdc++.h>
#include"../Templates/tint.h"
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ulint=unsigned long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector a(m,vector<ulint>(n));
    for(auto&x:a) for(auto&i:x) cin>>i;
    vector f(1t<<m,vector(n,vector(m,vector(n,vector<ulong>(m)))));
    return 0;
}
