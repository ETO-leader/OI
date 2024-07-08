#include<bits/stdc++.h>
using namespace std;
int main(int argc,char*argv[]){
    const auto n=atoi(argv[1]);
    const auto seed=atoi(argv[2]);
    mt19937 rnd(seed);
    vector<int> a(n);
    iota(a.begin(),a.end(),1);
    shuffle(a.begin(),a.end(),rnd);
    cout<<n<<'\n';
    for(auto&i:a) cout<<i<<' ';
    cout<<'\n';
}
