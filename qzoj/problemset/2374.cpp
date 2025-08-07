#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    auto cnt=0;
    for(auto&x:s){
        cnt+=(x=='('?1:(x==')'?-1:0));
        if(cnt<0) exit((cout<<"NO"<<'\n',0));
    }
    cout<<(cnt?"NO":"YES")<<'\n';
    return 0;
}
