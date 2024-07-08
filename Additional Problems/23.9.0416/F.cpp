#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
using vector_t=unordered_map<size_t,T>;
using lint=long long;
int mex(int a,int b){
    return (a&&b)?0:((a!=1&&b!=1)?1:2);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<vector_t<int>> mp(n);
    vector<lint> ans(3);
    cir(i,0,n) cin>>mp[0][i],ans[mp[0][i]]++;
    cir(i,1,n) cin>>mp[i][0],ans[mp[i][0]]++;
    cir(i,1,n) cir(j,1,(i<4?n:4)){
        mp[i][j]=mex(mp[i-1][j],mp[i][j-1]);
        if(i>3&&(j==3)||(i==3&&j>=3))
            ans[mp[i][j]]+=(min(n-i,n-j));
        else ans[mp[i][j]]++;
    }
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
