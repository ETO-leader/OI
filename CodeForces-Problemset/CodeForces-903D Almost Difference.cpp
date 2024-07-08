#include<bits/stdc++.h>
using namespace std;
using __int=__int128_t;
istream&operator>>(istream&is,__int&v){
    string s;is>>s;v=0;
    for(auto c:s) (v*=10)+=(c-'0');
    return is;
}
ostream&operator<<(ostream&os,__int v){
    if(v<0) cout<<'-',v=-v;
    if(v>9) os<<v/10;
    return (os<<(int)(v%10));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    __int n;cin>>n;vector<__int> v(n);
    map<__int,__int> cnx;
    for(auto&i:v) cin>>i,cnx[i]++;
    reverse(v.begin(),v.end());
    auto cnt=accumulate(v.begin()
        ,v.end(),(__int)(0));
    __int ans=0,iter=n;
    for(auto&i:v){
        cnt-=i;iter--;cnx[i]--;
        (ans+=iter*i-cnt+cnx[i+1])-=cnx[i-1];
    }
    cout<<ans<<'\n';
    return 0;
}
