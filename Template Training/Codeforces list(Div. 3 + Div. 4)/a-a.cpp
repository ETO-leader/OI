#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        string x;cin>>x;
        println("{}",x.size()-ranges::count(x,'0'));
        cir(i,0,(int)(x.size())) if(x[i]!='0'){
            print("{}",x[i]);
            cir(c,0,(int)(x.size())-1-i) print("0");
            print(" ");
        }
        println("");
    }();
    return 0;
}
