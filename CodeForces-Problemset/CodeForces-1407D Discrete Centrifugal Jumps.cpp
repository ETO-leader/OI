#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    for(auto&i:v) cin>>i;
    vector<int> D(n);
    stack<int> ls,gr;
    ls.push(0);gr.push(0);
    cir(i,1,n){
        D[i]=D[i-1]+1;
        while(!ls.empty()&&v[ls.top()]>=v[i]){
            if(v[ls.top()]!=v[i]&&ls.size()>1) ls.pop(),
                D[i]=min(D[i],D[ls.top()]+1);
            else ls.pop();
        }
        while(!gr.empty()&&v[gr.top()]<=v[i]){
            if(v[gr.top()]!=v[i]&&gr.size()>1) gr.pop(),
                D[i]=min(D[i],D[gr.top()]+1);
            else gr.pop();
        }
        ls.push(i);gr.push(i);
    }
    cout<<D[n-1]<<'\n';
    return 0;
}
