#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
ostream&operator<<(ostream&os,VI v){
    for(auto&i:v) os<<(i==_inf?-1:i)<<'\n';
    return os;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<int> v(n);
    for(auto&i:v) cin>>i;
    vector<vector<VI>> D(n+1,
        vector<VI>(m+1,VI(2,_inf)));
    cout<<[&](){
        D[0][0][1]=0;
        cir(i,0,n) cir(j,0,m+1){
            auto&d=D[i][j];
            D[i+1][j][0]=min(D[i+1][j][0],d[0]);
            if(j+v[i]<=m)
                D[i+1][j+v[i]][1]=min(D[i+1][j+v[i]][1],d[0]);
            D[i+1][j][0]=min(D[i+1][j][0],d[1]+1);
            if(j+v[i]<=m)
                D[i+1][j+v[i]][1]=min(D[i+1][j+v[i]][1],d[1]);
        }
        VI res;
        cir(i,1,m+1)
            res.push_back(min(D[n][i][0],D[n][i][1]));
        return res;
    }();
    return 0;
}
