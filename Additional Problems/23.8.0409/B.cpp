#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        string s;cin>>s;
        sort(s.begin(),s.end());
        cout<<(s.front()==s.back()?"-1":s)<<'\n';
    }
    return 0;
}
