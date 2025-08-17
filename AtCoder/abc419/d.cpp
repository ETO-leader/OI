#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    string s,t;cin>>s>>t;
    vector<int> op(n+1);
    cir(i,0,q){
        int l,r;cin>>l>>r;--l;
        op[l]^=1;
        op[r]^=1;
    }
    cir(i,1,n+1) op[i]^=op[i-1];
    cir(i,0,n) if(op[i]) swap(s[i],t[i]);
    cout<<s<<'\n';
    return 0;
}
