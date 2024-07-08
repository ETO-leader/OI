#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int x;cin>>x;
        cout<<(x<5?"Bob\n":"Alice\n");
    }
    return 0;
}
