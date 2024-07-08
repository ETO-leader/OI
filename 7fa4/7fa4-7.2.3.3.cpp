#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,a,b;cin>>n>>a>>b;
    if(a+b-1>n||1ll*a*b<n){
        exit((cout<<-1<<'\n',0));
    }
    deque<int> ax(n);
    iota(ax.begin(),ax.end(),1);
    reverse(ax.begin(),ax.end());
    vector<int> ans;
    cir(c,0,b){
        vector<int> q;
        cir(i,0,a){
            if(b-c>ax.size()) break;
            q.push_back(ax.front());
            ax.pop_front();
        }
        reverse(q.begin(),q.end());
        for(auto&i:q) ans.push_back(i);
    }
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
