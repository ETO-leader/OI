#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;string s;cin>>s;
    vector<int> posx;
    cir(i,0,n) if(s[i]=='/') posx.push_back(i);
    vector<int> pre(n),suf(n);
    cir(i,0,n) pre[i]=(s[i]=='1'),suf[i]=(s[i]=='2');
    cir(i,1,n) pre[i]+=pre[i-1];
    cir(i,1,n) suf[i]+=suf[i-1];
    cir(i,0,q) [&]{
        int l,r;cin>>l>>r;--l;--r;
        auto fl=ranges::lower_bound(posx,l)-posx.begin(),fr=ranges::upper_bound(posx,r)-posx.begin();
        if(fl>fr-1) return cout<<0<<'\n',void();
        --fr;
        const auto cfl=fl,cfr=fr;
        auto ans=fl-1;
        while(fl<fr+1){
            const auto mid=(fl+fr)/2;
            pre[posx[mid]]-(l?pre[l-1]:0)<
                suf[r]-(posx[mid]?suf[posx[mid]-1]:0)+1?
                ((fl=mid+1),(ans=mid)):(fr=mid-1);
        }
        auto rans=0;
        if(ans>cfl-1) rans=(pre[posx[ans]]-(l?pre[l-1]:0))*2+1;
        if(ans+1<cfr+1) rans=max(rans,(suf[r]-(posx[ans+1]?suf[posx[ans+1]]:0))*2+1);
        cout<<rans<<'\n';
    }();
    return 0;
}
