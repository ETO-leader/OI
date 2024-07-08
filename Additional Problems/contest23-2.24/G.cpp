#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;string s;cin>>n>>s;
    if(s.front()!=s.back()){
        exit((cout<<1<<'\n',0));
    }
    cir(i,0,n-1){
        if(s[i]!=s[0]&&s[i+1]!=s[0]){
            exit((cout<<2<<'\n',0));
        }
    }
    cout<<-1<<'\n';
    return 0;
}
