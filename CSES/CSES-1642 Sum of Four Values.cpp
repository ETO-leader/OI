#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct pos{int p1,p2;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x;cin>>n>>x;vector<int> v(n);
    for(auto&i:v) cin>>i;
    unordered_map<int,vector<pos>> up;
    cir(i,0,n) cir(j,i+1,n) up[v[i]+v[j]].push_back({i+1,j+1});
    for(auto&i:up){
        auto need=x-i.first;
        if(up.count(need)&&up[need].size()-(i.first==need)>0){
            auto x1=i.second[0];auto x2=up[need].begin();
            while(x2!=up[need].end()&&(x1.p1==x2->p1||x1.p1==x2->p2||
                x1.p2==x2->p1||x1.p2==x2->p2)) ++x2;
            if(x2==up[need].end()) continue;
            cout<<x1.p1<<' '<<x1.p2<<' '<<x2->p1<<' '<<x2->p2<<'\n';
            goto res;
        }
    }
    cout<<"IMPOSSIBLE\n";
    res:return 0;
}