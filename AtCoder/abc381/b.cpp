#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    if(s.size()&1) exit((cout<<"No"<<'\n',0));
    map<char,int> cnt;
    cir(i,0,(int)(s.size())/2){
        if(s[i*2]!=s[i*2+1]) exit((cout<<"No"<<'\n',0));
    }
    for(auto&i:s) ++cnt[i];
    for(auto&[a,b]:cnt) if(b!=2) exit((cout<<"No"<<'\n',0));
    cout<<"Yes\n";
    return 0;
}
