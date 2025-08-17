#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    priority_queue<int,vector<int>,greater<>> q;
    cir(i,0,n){
        int op;cin>>op;
        if(op==1){
            int w;cin>>w;
            q.emplace(w);
        }else{
            cout<<q.top()<<'\n';
            q.pop();
        }
    }
    return 0;
}
