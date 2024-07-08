#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&]{
        string s;cin>>s;
        if(s=="()"||s.size()<2){
            cout<<"NO\n";
            return;
        }
        cout<<"YES\n";
        cir(i,0,s.size()-1){
            if(s[i]==s[i+1]){
                cir(i,0,s.size())
                    cout<<"()";
                cout<<'\n';
                return;
            }
        }
        cir(i,0,s.size()) cout<<"(";
        cir(i,0,s.size()) cout<<")";
        cout<<'\n';
    }();
    return 0;
}
