#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x,cnt=0;cin>>n>>x;
    vector<int> v(n);
    map<int,vector<int>> us;
    for(auto&i:v) cin>>i,us[i].push_back(++cnt);
    cnt=0;
    for(auto&i:v){
        ++cnt;
        if(us[x-i].size()>1||us[x-i].size()==1&&x-i!=i)
            cout<<cnt<<' '<<us[x-i].back()<<'\n',exit(0);
    }
    cout<<"IMPOSSIBLE\n";
    return 0;
}
