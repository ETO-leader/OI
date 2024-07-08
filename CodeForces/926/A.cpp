#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        cout<<(*max_element(a.begin(),a.end()))
            -(*min_element(a.begin(),a.end()))<<'\n';
    }
    return 0;
}
