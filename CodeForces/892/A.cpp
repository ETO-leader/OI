#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;VI a(n),b,c;
        for(auto&i:a) cin>>i;
        const int mx=*max_element(
            a.begin(),a.end());
        for(auto&i:a){
            if(i==mx) c.push_back(i);
            else b.push_back(i);
        }
        if(b.empty()){
            cout<<"-1\n";continue;
        }
        cout<<b.size()<<' '<<c.size()<<'\n';
        for(auto&i:b) cout<<i<<' ';
        cout<<'\n';
        for(auto&i:c) cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}
