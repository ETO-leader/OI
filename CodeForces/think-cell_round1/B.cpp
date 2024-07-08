#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        deque<int> a,b;
        cir(i,1,n+1) (i&1?a:b).push_back(i);
        reverse(a.begin(),a.end());
        while(a.size()||b.size()){
            if(!a.empty()) cout<<a.front()<<' ',a.pop_front();
            if(!b.empty()) cout<<b.front()<<' ',b.pop_front();
        }
        cout<<'\n';
    }
    return 0;
}
