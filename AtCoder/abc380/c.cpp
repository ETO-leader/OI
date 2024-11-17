#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;int n,k;cin>>n>>k>>s;
    vector<pair<int,int>> a;
    cir(i,0,(int)(s.size())) if(s[i]=='1'){
        auto l=i;
        while(i+1<(int)(s.size())&&s[i+1]=='1') ++i;
        a.emplace_back(l,i);
    }
    a[k-2].second+=a[k-1].second-a[k-1].first+1;
    a.erase(a.begin()+k-1);
    string ans(s.size(),'0');
    for(auto&[l,r]:a) cir(i,l,r+1) ans[i]='1';
    cout<<ans<<'\n';
    return 0;
}
