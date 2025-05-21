#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    map<string,string> str;
    string s;
    while(getline(cin,s)){
        string cmd;
        while(s.front()!=' '){
            cmd+=s.front();
            s.erase(s.front());
        }
        s.erase(s.front());
        str[cmd]=s;
    }
    return 0;
}
