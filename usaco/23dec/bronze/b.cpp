#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;string s;cin>>s;
    int cnt=0,mn=n+1,len=0;
    vector<int> lx;
    int cnti=0;
    for(auto&i:s){
        if(i=='1') ++cnti;
        else break;
    }
    if(cnti) s=string(cnti-1,'1')+s;
    for(auto&i:s){
        if(i=='0'){
            if(len){
                mn=min(mn,len-(!(len&1)));
                lx.push_back(len);len=0;
            }
        }else{
            ++len;++cnt;
        }
    }
    if(len){
        lx.push_back(len);
        if(len<s.size()) mn=min(mn,len*2-1);
        else mn=len;
    }
    if(cnti) (lx.front()+=1)/=2;
    if(!cnt) exit((cout<<0<<'\n',0));
    int ans=0;
    for(auto&i:lx) ans+=(i+mn-1)/mn;
    cout<<ans<<'\n';
    return 0;
}
