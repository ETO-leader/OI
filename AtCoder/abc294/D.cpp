#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;set<int> sx;
    cir(i,1,n+1) sx.insert(i);
    cir(i,0,q){
        int op;cin>>op;
        if(op==2){
            int x;cin>>x;
            if(sx.count(x))
                sx.erase(sx.find(x));
        }
        if(op==3){
            cout<<*sx.begin()<<'\n';
        }
    }
    return 0;
}
