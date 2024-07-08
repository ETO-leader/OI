#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(time(NULL));
int main(){
    int n=1000;vector<int> ans(n);
    for(auto&i:ans) i=rnd()%1000000001;
    cout<<n<<'\n';
    for(auto&i:ans) cout<<i<<' ';
}
