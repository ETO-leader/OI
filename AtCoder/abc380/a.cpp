#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    cout<<(
        ranges::count(s,'1')==1&&
        ranges::count(s,'2')==2&&
        ranges::count(s,'3')==3
    ?"Yes":"No")<<'\n';
    return 0;
}
