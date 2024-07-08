#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n+1);
    for(auto&i:a) cin>>i;
    int cnx=0;stringstream ss;
    cir(i,0,n+1) if([&](){
        deque<int> arr;
        cir(x,0,n+1) if(x!=i)
            arr.push_back(a[x]);
        while(!arr.empty()){
            sort(arr.begin(),arr.end(),greater<int>());
            while((!arr.empty())&&(!arr.back()))
                arr.pop_back();
            if(arr.empty()) break;
            const auto f=arr.front();
            arr.pop_front();
            if(f>arr.size()) return false;
            cir(i,0,f) --arr[i];
        }
        return true;
    }()) ++cnx,ss<<'\n'<<i+1;
    cout<<cnx<<ss.str()<<'\n';
    return 0;
}