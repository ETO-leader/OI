#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    vector<int> p;
    cir(i,0,(int)(s.size())) if(s[i]=='|') p.push_back(i);
    cir(i,1,(int)(p.size())) cout<<p[i]-p[i-1]-1<<' ';
    cout<<'\n';
    return 0;
}
