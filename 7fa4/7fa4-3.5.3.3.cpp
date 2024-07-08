#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<int> a(n),D(n);
    for(auto&i:a) cin>>i;
    deque<pair<int,int>> q;
    cir(i,0,n){
        auto ub=lower_bound(q.begin()
            ,q.end(),make_pair(a[i],-1));
        if(ub==q.begin()){
            if((!q.empty())&&(q.front().first<a[i]))
                continue;
            if(!q.empty()) q.pop_front();
            D[i]=1;
            q.push_front({a[i],D[i]});
        }else if(ub==q.end()){
            D[i]=q.back().second+1;
            q.push_back({a[i],D[i]});
        }else{
            D[i]=(ub-1)->second+1;
            ub->first=min(a[i],ub->first);
        }
    }
    cout<<q.back().second<<'\n';
    return 0;
}
