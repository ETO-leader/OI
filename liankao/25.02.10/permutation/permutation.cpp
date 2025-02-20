#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("permutation.in");
ofstream ouf("permutation.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
constexpr auto tri_pow(auto x){
    auto res=1;
    cir(i,0,x) res*=3;
    return res;
}
constexpr auto tri_bit(int w,int b){
    return w/tri_pow(b)%3;
}
constexpr auto tri_popcount(int w){
    auto res=0;
    while(w) res+=w%3,w/=3;
    return res;
}
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;
    vector<int> vaild;
    cir(i,0,tri_pow(9)) if(tri_popcount(i)==9&&tri_bit(i,0)<2) vaild.emplace_back(i);
    vaild.resize(n);
    vector<int> rid(tri_pow(9));
    cir(i,0,n) rid[vaild[i]]=i;
    ouf<<26<<'\n';
    cir(b,0,1){
        vector<vector<int>> ax(2);
        for(auto&x:vaild) ax[tri_bit(x,b)].emplace_back(x);
        sort(ax[0].begin(),ax[0].end());
        sort(ax[1].begin(),ax[1].end());
        for(auto&x:ax[0]) ouf<<rid[x]<<' ';
        for(auto&x:ax[1]) ouf<<rid[x]<<' ';
        ouf<<'\n';
        reverse(ax[0].begin(),ax[0].end());
        reverse(ax[1].begin(),ax[1].end());
        for(auto&x:ax[0]) ouf<<rid[x]<<' ';
        for(auto&x:ax[1]) ouf<<rid[x]<<' ';
        ouf<<'\n';
    }
    cir(b,1,9){
        vector<vector<int>> ax(3);
        for(auto&x:vaild) ax[tri_bit(x,b)].emplace_back(x);
        sort(ax[0].begin(),ax[0].end());
        sort(ax[1].begin(),ax[1].end());
        sort(ax[2].begin(),ax[2].end());
        for(auto&x:ax[0]) ouf<<rid[x]<<' ';
        for(auto&x:ax[1]) ouf<<rid[x]<<' ';
        for(auto&x:ax[2]) ouf<<rid[x]<<' ';
        ouf<<'\n';
        sort(ax[0].begin(),ax[0].end());
        reverse(ax[1].begin(),ax[1].end());
        reverse(ax[2].begin(),ax[2].end());
        for(auto&x:ax[1]) ouf<<rid[x]<<' ';
        for(auto&x:ax[0]) ouf<<rid[x]<<' ';
        for(auto&x:ax[2]) ouf<<rid[x]<<' ';
        ouf<<'\n';
        reverse(ax[0].begin(),ax[0].end());
        reverse(ax[2].begin(),ax[2].end());
        for(auto&x:ax[0]) ouf<<rid[x]<<' ';
        for(auto&x:ax[2]) ouf<<rid[x]<<' ';
        for(auto&x:ax[1]) ouf<<rid[x]<<' ';
        ouf<<'\n';
    }
    return 0;
}
