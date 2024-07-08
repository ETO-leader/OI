#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;cin>>s;s+=s;
    auto n=s.size();
    int i=0,stx;
    while(i<n/2){
        int j=i+1,k=i;stx=i;
        while(j<n&&s[j]>=s[k]){
            k=(s[j]==s[k]?k+1:i);
            ++j;
        }
        while(i<=k) i+=(j-k);
    }
    cout<<s.substr(stx,n/2)<<'\n';
    return 0;
}