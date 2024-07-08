#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    unordered_map<string,int> Apt;
    cir(i,0,n){
        string s;int w;cin>>s>>w;
        if(!Apt.count(s)) Apt[s]=w;
        else Apt[s]=min(Apt[s],w);
    }
    int m;cin>>m;
    cir(i,0,m){
        string s;cin>>s;
        cout<<Apt[s]<<endl;
    }
    return 0;
}