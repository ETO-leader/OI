#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    cout<<(s=="red"?"SSS":(s=="blue"?"FFF":(s=="green"?"MMM":"Unknown")))<<'\n';
    return 0;
}
