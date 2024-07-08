#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        cir(i,0,n) a[i]+=i+1;
        sort(a.begin(),a.end(),greater<int>());
        int ansx=a[0]+7;
        for(auto&i:a){
            cout<<(ansx=min(ansx-1,i))<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
