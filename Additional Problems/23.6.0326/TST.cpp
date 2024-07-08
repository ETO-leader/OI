#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    vector<std::thread> vt;
    mt19937 rnd(time(NULL));
    for(auto&i:v){
        cin>>i;
        vt.push_back(thread([&rnd](int t){
            Sleep(500*t+(abs<int>(rnd())%300));
            cout<<t<<'\n'<<flush;
        },i));
    }
    for(auto&i:vt) i.join();
    return 0;
}
