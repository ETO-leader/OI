#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x,cnt=0,ai;cin>>n>>x;
    multiset<int,greater<int>> chs;
    cir(i,0,n) cin>>ai,chs.insert(ai);
    while(!chs.empty()&&++cnt){
        if(chs.size()==1) break;
        int b=*chs.begin();
        auto lb=chs.lower_bound(x-b);
        if(lb==chs.begin()) ++lb;
        chs.erase(chs.begin());
        if(lb!=chs.end()&&(*lb)<=x-b) chs.erase(lb);
    }
    cout<<cnt<<'\n';
    return 0;
}