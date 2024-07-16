#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;map<int,vector<int>> ax;
        cir(i,0,n){
            int l,r;cin>>l>>r;ax[l].push_back(r);
        }
        priority_queue<int,vector<int>,greater<int>> q;
        auto lasl=0;
        for(auto&[l,arx]:ax){
            while((!q.empty())&&(lasl++)<min(l,q.top()+1)) q.pop();
            if((!q.empty())&&q.top()<l) return cout<<"No\n",void();
            for(auto&i:arx) q.push(i);
            lasl=l;
        }
        while(!q.empty()){
            if((lasl++)>q.top()) return cout<<"No\n",void();
            q.pop();
        }
        cout<<"Yes\n";
    }();
    return 0;
}
