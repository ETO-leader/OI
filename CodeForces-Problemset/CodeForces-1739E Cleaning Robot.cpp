#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<string> mp(2);
    for(auto&i:mp){
        cin>>i;
        i.insert(i.begin(),'0');
    }
    vector<VI> D(n+2,VI(2));
    auto gtc=[&](int x,int y){
        assert(y<2);
        assert(x<mp[y].size());
        return mp[y][x]-'0';
    };
    for(int i=n-1;~i;--i) cir(j,0,2){
        auto&d=D[i][j];
        if(!gtc(i,j^1)){
            d=D[i+1][j];
        }else if(!gtc(i+1,j)){
            d=min(D[i+1][j]+1,D[i+1][j^1]);
        }else if(!gtc(i+1,j^1)){
            d=min(D[i+2][j^1],D[i+2][j])+1;
        }else{
            d=min(D[i+2][j]+2,D[i+2][j^1]+1);
        }
    }
    cout<<[&](){
        int res=0;
        for(auto&i:mp){
            res+=count(i.begin(),i.end(),'1');
        }
        return res;
    }()-D[0][0]<<'\n';
    return 0;
}
