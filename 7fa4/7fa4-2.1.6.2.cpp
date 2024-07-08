#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> Tp;
int bfs(int n){
    vector<int> D(n+1);
    queue<int> q;int ret=1;
    cir(i,1,n+1) if(!Tp[i]) q.push(i),D[i]=1;
    while(!q.empty()){
        auto f=q.front();q.pop();
        for(auto&i:G[f]){
            if(!(--Tp[i])) q.push(i);
            ret=max(ret,(D[i]=max(D[i],D[f]+1)));
        }
    }
    return ret;
}
const int _inf=numeric_limits<int>::max();
vector<int> mx{0,0,-1,1},my{-1,1,0,0};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<int> HT((n+7)*(m+7),_inf);
    G.resize((n+7)*(m+7));Tp.resize((n+7)*(m+7));
    auto to_line=[&](int x,int y){
        return max(m*(x-1)+y,0);
    };
    cir(i,1,n+1) cir(j,1,m+1) cin>>HT[to_line(i,j)];
    cir(i,1,n+1) cir(j,1,m+1){
        cir(k,0,4){
            auto x=i+mx[k],y=j+my[k];
            if(HT[to_line(i,j)]>HT[to_line(x,y)])
                G[to_line(i,j)].push_back(to_line(x,y)),Tp[to_line(x,y)]++;
        }
    }
    cout<<bfs(n*m)<<endl;
    return 0;
}