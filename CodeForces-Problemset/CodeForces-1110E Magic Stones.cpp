#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
void putstr(string str){
    cout<<str<<'\n';exit(0);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> s(n),t(n);
    for(auto&i:s) cin>>i;
    for(auto&i:t) cin>>i;
    if(s[0]!=t[0]||s[n-1]!=t[n-1])
        putstr("No");
    unordered_multiset<int> dls;
    cir(i,1,n) dls.insert(s[i]-s[i-1]);
    cir(i,1,n){
        if(dls.find(t[i]-t[i-1])==dls.end())
            putstr("No");
        dls.erase(dls.find(t[i]-t[i-1]));
    }
    putstr("Yes");
    return 0;
}
