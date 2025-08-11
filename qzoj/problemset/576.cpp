#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    const auto n=(int)(s.size());
    auto ns=s;s="#";
    for(auto&x:ns) (s+=x)+='#';
    vector<int> len(n*2+1);
    cir(i,1,n*2+1){
        len[i]=min(max(len[i-1]-1,0),(i-1?len[i-2]:0));
        while(i-len[i]-1>-1&&i+len[i]+1<n*2+1){
            if(s[i-len[i]-1]==s[i+len[i]+1]) ++len[i];
            else break;
        }
    }
    cout<<(*max_element(len.begin(),len.end()))<<'\n';
    return 0;
}
