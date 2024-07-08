#include<bits/stdc++.h>
using namespace std;
int getmind(int n){
    for(int i=2;i*i<=n;++i)
        if(!(n%i)) return i;
    return n;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;
        cout<<(getmind(n)<=m&&(n>1)
            ?"NO\n":"YES\n");
    }
    return 0;
}
