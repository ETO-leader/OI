#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        vector<string> s(3);
        for(auto&i:s) cin>>i;
        [&](){
            cir(i,0,3){
                if(s[i][0]==s[i][1]&&s[i][1]==s[i][2]&&s[i][0]!='.'){
                    cout<<s[i][0]<<'\n';return;
                }
                if(s[0][i]==s[1][i]&&s[1][i]==s[2][i]&&s[0][i]!='.'){
                    cout<<s[0][i]<<'\n';return;
                }
            }
            if(s[0][0]==s[1][1]&&s[1][1]==s[2][2]&&s[1][1]!='.'){
                cout<<s[1][1]<<'\n';return;
            }
            if(s[0][2]==s[1][1]&&s[1][1]==s[2][0]&&s[1][1]!='.'){
                cout<<s[1][1]<<'\n';return;
            }
            cout<<"DRAW\n";
        }();
    }
    return 0;
}
