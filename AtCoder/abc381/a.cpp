#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    string s;cin>>s;
    if(!(s.size()&1)) exit((cout<<"No"<<'\n',0));
    cir(i,0,(int)(s.size())/2){
        if(s[i]!='1'||s[s.size()-i-1]!='2') exit((cout<<"No"<<'\n',0));
    }
    if(s[s.size()/2]!='/') exit((cout<<"No"<<'\n',0));
    cout<<"Yes\n";
    return 0;
}
