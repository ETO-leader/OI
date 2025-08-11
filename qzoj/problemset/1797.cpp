#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    vector<vector<int>> s(4,vector<int>(4));
    cir(i,0,4){
        string xs;cin>>xs;
        cir(j,0,4) s[i][j]=xs[j]-'0';
    }
    vector<vector<int>> t(4,vector<int>(4));
    cir(i,0,4){
        string xs;cin>>xs;
        cir(j,0,4) t[i][j]=xs[j]-'0';
    }
    map<vector<vector<int>>,int> f;
    queue<vector<vector<int>>> q;
    q.emplace(s);
    while(!f.count(t)){
        auto u=q.front();q.pop();
        const auto w=f[u];
        cir(i,0,4) cir(j,0,3){
            swap(u[i][j],u[i][j+1]);
            if(!f.count(u)) f[u]=w+1,q.emplace(u);
            swap(u[i][j],u[i][j+1]);
        }
        cir(i,0,3) cir(j,0,4){
            swap(u[i][j],u[i+1][j]);
            if(!f.count(u)) f[u]=w+1,q.emplace(u);
            swap(u[i][j],u[i+1][j]);
        }
    }
    cout<<f[t]<<'\n';
    return 0;
}
