#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        if(n&1){
            deque<int> cur((n+1)/2);
            ranges::iota(cur,n-(n+1)/2+1);
            vector<int> ans(n);
            for(auto pos=0;pos<n;pos+=2){
                ans[pos]=((pos>>1)&1)?cur.back():cur.front();
                ((pos>>1)&1)?cur.pop_back():cur.pop_front();
            }
            for(auto pos=1,w=n-(n+1)/2;pos<n;pos+=2,--w){
                ans[pos]=w;
            }
            swap(ans[n-1],ans[n-2]);
            println("YES");
            for(auto&i:ans) print("{} ",i);
            println();
        }else{
            deque<int> cur(n/2);
            ranges::iota(cur,n-(n+1)/2+1);
            vector<int> ans(n);
            for(auto pos=0;pos<n;pos+=2){
                ans[pos]=((pos>>1)&1)?cur.back():cur.front();
                ((pos>>1)&1)?cur.pop_back():cur.pop_front();
            }
            for(auto pos=1,w=n-(n+1)/2-1;pos<n;pos+=2,--w){
                ans[pos]=w;
            }
            ans.back()=(n-(n+1)/2);
            ans.insert(ans.begin(),ans.back());
            ans.pop_back();
            swap(ans[n-1],ans[n-2]);
            println("YES");
            for(auto&i:ans) print("{} ",i);
            println();
        }
    }();
    return 0;
}
