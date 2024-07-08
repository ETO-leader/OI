#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;lint adall=0;
    priority_queue<lint,vector<lint>,greater<lint>> pq;
    cir(i,0,n){
        int op,x;cin>>op;
        if(op==1){
            cin>>x;pq.push(x-adall);
        }else if(op==2){
            cin>>x;adall+=x;
        }else{
            cout<<pq.top()+adall<<'\n';
            pq.pop();
        }
    }
    return 0;
}
