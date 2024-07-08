#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<vector<lint>> D;
lint dp(string&si,int u,int v,bool lim,bool isz){
    if(!(~u)) return 1;
    lint&d=D[u][v],res=0;
    if((~d)&&(!lim)&&(!isz)) return d;
    int mxi=(lim?(int)(si[u]-'0'+1):10);
    cir(i,0,mxi){
        if(i!=v||isz)
            res+=dp(si,u-1,i,lim&&(i==mxi-1),isz&&(!i));
    }
    return (((!lim)&&(!isz))?d=res:res);
}
lint run(lint x){
    if(x<=0) return (!x);
    auto sr=to_string(x);
    reverse(sr.begin(),sr.end());
    D.assign(sr.size(),vector<lint>(10,-1));
    return dp(sr,sr.size()-1,0,true,true);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint l,r;cin>>l>>r;
    cout<<run(r)-run(l-1)<<'\n';
    return 0;
}