#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class interactor{
public:
    auto get_n(){
        int n;cin>>n;
        return n;
    }
    auto ask(vector<int> arr){
        cout<<"? ";
        for(auto&i:arr) cout<<i<<' ';
        cout<<'\n';
        cout.flush();
        string type;cin>>type;
        return type;
    }
    auto answer(string ans){
        cout<<"! "<<ans<<'\n';
        cout.flush();
    }
} interact;
auto make_range(int l,int r){
    vector<int> res(r-l+1);
    ranges::iota(res,0);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    const auto n=interact.get_n();
    const auto bcolor=interact.ask(make_range(1,n));
    return 0;
}
