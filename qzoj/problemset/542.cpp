#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    unordered_set<string> cnt;
    string s;
    getline(cin,s);
    cir(i,0,n){
        string x;getline(cin,x);
        if(x[0]=='a'){
            cnt.emplace(x.substr(4));
        }else{
            cout<<(cnt.count(x.substr(5))?"yes":"no")<<'\n';
        }
    }
    return 0;
}
