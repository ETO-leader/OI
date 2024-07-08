#include<bits/stdc++.h>
using namespace std;
using lint=long long;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<VI> mp(n,VI(n));
    for(auto&i:mp) for(auto&j:i) cin>>j;
    vector<unordered_map<int,lint>> cnx(n);
    lint ans=0;
    function<void(int,int,int,int)> f=
        [&](int x,int y,int w,int tag){
        if(x+y==n-1){
            if(tag==1) cnx[y][w^mp[x][y]]++;
            else (ans+=cnx[y][w]);
            return;
        }
        f(x+tag,y,w^mp[x][y],tag);
        f(x,y+tag,w^mp[x][y],tag);
    };
    cout<<[&f,&ans](int x,int y){
        f(0,0,0,1);f(x-1,y-1,0,-1);
        return ans;
    }(n,n)<<'\n';
    return 0;
}
