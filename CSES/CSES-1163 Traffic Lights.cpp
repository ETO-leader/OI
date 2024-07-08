#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int x,n;cin>>x>>n;
    set<int> lig;lig.insert(0);lig.insert(x);
    multiset<int,greater<int>> cnts;
    cnts.insert(x);
    while(n--){
        int pi;cin>>pi;
        auto upp=lig.upper_bound(pi),low=upp;--low;
        cnts.erase(cnts.find(*upp-*low));lig.insert(pi);
        cnts.insert(pi-*low);cnts.insert(*upp-pi);
        cout<<*cnts.begin()<<(n?' ':'\n');
    }
    return 0;
}