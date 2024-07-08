#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=0;i<n;++i)
using namespace std;
auto ok(string s,int c){
    if(c==4) return true;
    const auto mn=*min_element(s.begin(),s.end())-'0';
    const auto mx=*max_element(s.begin(),s.end())-'0';
    if(c==1) return mn>0&&mx<4;
    if(c==2) return mn>1&&mx<7;
    return mn>2;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        string s,sk;cin>>s;
        int ans=1;
        for(auto&i:s){
            sk.push_back(i);
            while(!ok(sk,ans)) ++ans,sk=string()+i;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
