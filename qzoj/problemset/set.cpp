#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const auto ans=vector<vector<vector<int>>>{
    vector<vector<int>>{
    },
    vector<vector<int>>{
        vector<int>{1},
        vector<int>{2},
    },
    vector<vector<int>>{
        vector<int>{1,2},
        vector<int>{1,3},
        vector<int>{1,4},
        vector<int>{2,3},
        vector<int>{2,4},
        vector<int>{3,4},
    },
    vector<vector<int>>{
        vector<int>{1,2,3},
        vector<int>{1,2,4},
        vector<int>{1,3,5},
        vector<int>{1,4,6},
        vector<int>{1,5,6},
        vector<int>{2,3,6},
        vector<int>{2,4,5},
        vector<int>{2,5,6},
        vector<int>{3,4,5},
        vector<int>{3,4,6},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4},
        vector<int>{1,2,3,5},
        vector<int>{1,4,6,7},
        vector<int>{1,5,6,7},
        vector<int>{2,4,6,8},
        vector<int>{2,5,6,8},
        vector<int>{3,4,7,8},
        vector<int>{3,5,7,8},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4,5},
        vector<int>{1,2,3,6,7},
        vector<int>{1,4,5,8,9},
        vector<int>{1,6,7,8,9},
        vector<int>{2,4,6,8,10},
        vector<int>{2,5,7,8,10},
        vector<int>{3,4,6,9,10},
        vector<int>{3,5,7,9,10},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4,5,6},
        vector<int>{1,2,3,4,7,8},
        vector<int>{1,5,6,7,8,9},
        vector<int>{2,5,7,9,10,11},
        vector<int>{2,6,8,9,10,12},
        vector<int>{3,5,8,10,11,12},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4,5,6,7},
        vector<int>{1,2,3,4,8,9,10},
        vector<int>{1,5,6,7,8,11,12},
        vector<int>{2,5,8,9,11,13,14},
        vector<int>{3,6,8,10,12,13,14},
        vector<int>{4,7,9,10,11,12,13},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4,5,6,7,8},
        vector<int>{1,2,3,4,5,6,9,10},
        vector<int>{1,7,8,9,10,11,12,13},
        vector<int>{2,7,9,11,12,14,15,16},
        vector<int>{2,8,10,11,13,14,15,16},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4,5,6,7,8,9},
        vector<int>{1,2,3,4,5,6,10,11,12},
        vector<int>{1,7,8,9,10,11,13,14,15},
        vector<int>{2,7,10,12,13,14,16,17,18},
        vector<int>{3,8,11,12,13,15,16,17,18},
    },
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        if(n>9){
            cout<<4<<'\n';
            cir(i,0,n) cout<<i+1<<' ';
            cout<<'\n';
            cir(i,0,n) cout<<i+n+1<<' ';
            cout<<'\n';
            cir(i,0,n) cout<<i*2+1<<' ';
            cout<<'\n';
            cir(i,0,n) cout<<(i+1)*2<<' ';
            cout<<'\n';
            return;
        }
        cout<<ans[n].size()<<'\n';
        for(auto&x:ans[n]){
            for(auto&i:x) cout<<i<<' ';
            cout<<'\n';
        }
    }();
    return 0;
}
