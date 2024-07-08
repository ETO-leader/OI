#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct viser{int t,id,tag;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,l,r;cin>>n;vector<viser> vx;
    cir(i,0,n) cin>>l>>r,vx.push_back({l,i,0}),
        vx.push_back({r,i,1});
    priority_queue<int,vector<int>,greater<int>> T;
    sort(vx.begin(),vx.end(),[](viser&a,viser&b){
        return a.t==b.t?a.tag<b.tag:a.t<b.t;});
    vector<int> A(n),Id(n),Cg;int rcnt=0;
    for(auto&i:vx){
        if(!i.tag){
            if(T.empty()) A[i.id]=++rcnt;
            else A[i.id]=T.top(),T.pop();
            Id[i.id]=A[i.id];
        }else{
            T.push(Id[i.id]);
        }
    }
    cout<<rcnt<<'\n';
    for(auto&i:A) cout<<i<<' ';
    cout<<'\n';
    return 0;
}