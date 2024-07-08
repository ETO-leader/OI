#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;unordered_set<string> aps;
    int mx=-1,mxp=-1;
    cir(i,0,n){
        string s;int score;cin>>s>>score;
        if(aps.count(s)) continue;
        if(score>mx) mx=score,mxp=i+1;
        aps.insert(s);
    }
    cout<<mxp<<'\n';
    return 0;
}
