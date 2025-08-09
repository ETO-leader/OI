#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    vector<int> a(10);
    iota(a.begin(),a.end(),0);
    vector<int> ok(10000);
    cir(i,0,100) ok[i*i]=true;
    do{
        if(ok[a[0]]&&ok[a[1]*10+a[2]]&&ok[a[3]*100+a[4]*10+a[5]]&&ok[a[6]*1000+a[7]*100+a[8]*10+a[9]]&&a[1]&&a[3]&&a[6]){
            cout<<a[0]<<' ';
            cout<<a[1]<<a[2]<<' ';
            cout<<a[3]<<a[4]<<a[5]<<' ';
            cout<<a[6]<<a[7]<<a[8]<<a[9]<<'\n';
        }
    }while(next_permutation(a.begin(),a.end()));
    return 0;
}
