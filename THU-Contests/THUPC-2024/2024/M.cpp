#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;getline(cin,s);
    if(s.substr(0,19)=="You are right, but ")
        cout<<"AI\n";
    else cout<<"Human\n";
    return 0;
}
