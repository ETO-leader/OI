#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int k;cin>>k;bool chg=false;
        vector<int> v;
        cir(i,0,k){
            int x;cin>>x;
            if(v.empty()||(x>=v.back()&&
                ((!chg)||x<=v.front()))){
                cout<<1;
                v.push_back(x);
            }else if((!chg)&&x<=v.front()){
                cout<<1;chg=true;
                v.push_back(x);
            }else{
                cout<<0;
            }
        }
        cout<<'\n';
    }
    return 0;
}
