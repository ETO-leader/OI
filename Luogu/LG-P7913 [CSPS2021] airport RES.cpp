#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto ck(vector<pair<int,int>> tags,unordered_map<int,int> Fx,int mx){
    priority_queue<int,vector<int>,greater<int>> pq;
    vector<int> Arr(mx+1);
    cir(i,1,mx+1) pq.push(i);
    sort(tags.begin(),tags.end());
    unordered_map<int,int> um;
    for(auto&i:tags){
        if(i.second==-1&&um.count(Fx[i.first])) pq.push(um[Fx[i.first]]);
        else if((!pq.empty())&&i.second==1)
            um[i.first]=pq.top(),Arr[pq.top()]++,pq.pop();
    }
    cir(i,1,mx+1) Arr[i]+=Arr[i-1];
    return Arr;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m1,m2;cin>>n>>m1>>m2;
    vector<pair<int,int>> t1,t2;
    unordered_map<int,int> f1,f2;
    cir(i,0,m1){
        int x,y;cin>>x>>y;f1[y]=x;
        t1.push_back({x,1});t1.push_back({y,-1});
    }
    cir(i,0,m2){
        int x,y;cin>>x>>y;f2[y]=x;
        t2.push_back({x,1});t2.push_back({y,-1});
    }
    auto fc1=ck(t1,f1,n),fc2=ck(t2,f2,n);
    int ans=0;
    cir(i,0,n+1) ans=max(ans,fc1[i]+fc2[n-i]);
    cout<<ans<<endl;
    return 0;
}