//30% tasks
//the string only contains operator '+' or operator '*'
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int x,y;cin>>x>>y;
    string s;cin>>s;
    const auto op=(count(s.begin(),s.end(),'+')?'+':'*');
    const auto cnt=count(s.begin(),s.end(),op);
    cout<<(int)(ceill(log2l(cnt+1))*(op=='+'?x:y))<<'\n';
    return 0;
}
