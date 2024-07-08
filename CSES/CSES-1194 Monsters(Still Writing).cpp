#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct Point{
    int x,y;
    Point operator+(Point&P){
        return {x+P.x,y+P.y};
    }
};
vector<Point> mv{{1,0},{-1,0},{0,1},{0,-1}};
template<typename T>
struct extvec{
    vector<vector<T>> vec;
    void ass(int n,int m,T k=0){
        vec.assign(n,vector<T>(m,k));
    }
    T&operator[](Point P){return vec[P.x][P.y];}
    extvec(int n=0,int m=0,int k=0){ass(n,m,k);}
};
const int _inf=1e9+7;
bool inr(Point P,int n,int m){
    return P.x>=0&&P.x<n&&P.y>=0&&P.y<m;
}
extvec<char> mp;
void bfs(queue<Point>&q,extvec<int>&i,
    extvec<int>&m,int n,int mx){
    while(!q.empty()){
        auto f=q.front();q.pop();
        cout<<f.x<<' '<<f.y<<'\n'<<flush;
        for(auto&ix:mv) if(inr(f+ix,n,mx)&&mp[f+ix]!='#'){
            cout<<"    "<<(f+ix).x<<' '<<(f+ix).y<<'\n'<<flush;
            if(m[f+ix]>i[f]+1&&!i[f+ix]){
                q.push(f+ix);i[f+ix]=i[f]+1;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;mp.ass(n,m);
    queue<Point> ms,A;
    extvec<int> i(n,m,_inf),mo(n,m,_inf);
    cir(ix,0,n) cir(j,0,m){
        cin>>mp[{ix,j}];
        if(mp[{ix,j}]=='A') A.push({ix,j});
        if(mp[{ix,j}]=='M') ms.push({ix,j});
    }
    bfs(ms,i,mo,n,m);bfs(A,mo,i,n,m);
    int ans=_inf;
    cir(ix,0,n) ans=min({ans,i[{0,ix}],
        i[{n,ix}],i[{ix,0}],i[{ix,m}]});
    if(ans==_inf) cout<<"IMPOSSIBLE\n";
    else cout<<ans<<'\n';
    return 0;
}