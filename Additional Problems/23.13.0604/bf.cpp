#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int N;
vector<int> F,ced;
int p,q;
void dfs(int cx,int cost=0){
    cout<<cx<<' '<<cost<<endl;
    if(cx==N){
        p+=cost;q++;
        return;
    }
    cir(i,1,N+1) if(!ced[i]){
        auto ned=ced;
        int u=i,cnx=cx;
        while(u){
            cnx+=(!ced[u]);
            ced[u]=true;
            u=F[u];
        }
        cout<<i<<":"<<cnx<<'\n';
        dfs(cnx,cost+1);
        ced=ned;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>N;
    F.resize(N+1);ced.resize(N+1);
    cir(i,2,N+1){
        cin>>F[i];
    }
    dfs(0);
    cout<<p<<'/'<<q<<'\n';
    return 0;
}
