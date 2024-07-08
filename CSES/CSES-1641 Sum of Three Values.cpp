#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x,xi;cin>>n>>x;
    map<int,vector<int>> Ap;
    cir(i,0,n) cin>>xi,Ap[xi].push_back(i+1);
    for(auto it1=Ap.begin();it1!=Ap.end();++it1){
        for(auto it2=it1;it2!=Ap.end();++it2){
            auto&i=*it1,&j=*it2;
            if(i.first==j.first&&i.second.size()==1) continue;
            auto need=x-i.first-j.first;
            if(Ap.count(need)&&Ap[need].size()-
                (i.first==need)-(j.first==need)>0){
                cout<<i.second.front()<<' '<<j.second[i.first==j.first]
                    <<' '<<Ap[need][(i.first==need)+(j.first==need)]<<'\n';
                goto res;
            }
        }
    }
    cout<<"IMPOSSIBLE\n";
    res:return 0;
}