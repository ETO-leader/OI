#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const vector<array<int,2>> nxt{
    {-1,-3},{-1,3},{1,-3},{1,3},{-3,-1},{-3,1},{3,-1},{3,1}
};
vector<array<int,2>> qc,mxn;
vector<bool> sx,sy;
auto dfs(int n,int x,int y,int dep){
    if(x>n||x<1||y>n||y<1) return;
    if(sx[x]||sy[y]) return;
    sx[x]=true;sy[y]=true;
    qc.push_back({x,y});
    auto res=[&](){
        sx[x]=false;sy[y]=false;
        qc.pop_back();
    };
    if(dep==n) throw exception();
    for(const auto&[mx,my]:nxt) dfs(n,x+mx,y+my,dep+1);
    res();
}
auto print(int n,int lc)->void{
    if(n-lc+1>12){
        if(!lc) cout<<1<<' '<<1<<'\n';
        for(auto&[mx,my]:mxn) cout<<lc+mx<<' '<<lc+my<<'\n';
        print(n,lc+6);
    }else{
        try{
            sx.resize(17);sy.resize(17);
            dfs(n-lc,1,1,1);
            abort();
        }catch(exception&){
            for(auto&[mx,my]:qc) if(mx>1||(!lc)){
                cout<<lc+mx<<' '<<lc+my<<'\n';
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    if(n>1&&n<5) exit((cout<<"IMPOSSIBLE\n",0));
    cout<<"POSSIBLE\n";
    if(n==1){
        cout<<"1 1\n";
    }else if(n==5){
        for(auto[ax,ay]:{make_pair(3,5),make_pair(4,2),
            make_pair(1,1),make_pair(2,4),make_pair(5,3)}){
            cout<<ax<<' '<<ay<<'\n';
        }
    }else{
        mxn={{2,4},{5,5},{6,2},{3,3},{4,6},{7,7}};
        print(n,0);
    }
    return 0;
}
