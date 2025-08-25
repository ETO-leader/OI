#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k,q;cin>>n>>k>>q;
    vector<vector<int>> a(n,vector<int>(n)),b(n,vector<int>(n));
    for(auto&x:a) for(auto&i:x) cin>>i,--i;
    for(auto&x:b) for(auto&i:x) cin>>i,--i;
    vector<vector<uint64_t>> c(n,vector<uint64_t>(n));
    vector<uint64_t> uw(n);
    mt19937_64 eng(251);
    for(auto&i:uw) i=eng();
    vector<vector<int>> w(27);
    auto id=[&](string s){
        return (s[0]-'0')*9+(s[1]-'0')*3+s[2]-'0';
    };
    vector<vector<uint64_t>> sum(n,vector<uint64_t>(n));
    auto init=[&](string s){
        vector<int> ord(3),val(3);
        cir(i,0,n) cir(j,0,n){
            ord[0]=i;
            ord[1]=j;
            ord[2]=a[i][j];
            val[0]=ord[s[0]-'0'];
            val[1]=ord[s[1]-'0'];
            val[2]=ord[s[2]-'0'];
            c[val[0]][val[1]]=b[i][j];
        }
        const auto sid=id(s);
        for(auto&x:sum) fill(x.begin(),x.end(),0);
        cir(i,0,n) cir(j,0,n) sum[j][c[i][j]]+=uw[i];
        const auto sw=accumulate(uw.begin(),uw.end(),(uint64_t)(0));
        cir(i,0,n){
            auto vw=-uw[i]*n;
            cir(j,0,n) vw+=sum[j][c[i][j]];
            if(vw==(sw-uw[i])*k) w[sid].emplace_back(i);
        }
    };
    auto check=[&](string pattern,int p){
        const auto pid=id(pattern);
        if(w[pid].empty()) return -1;
        const auto upb=lower_bound(w[pid].begin(),w[pid].end(),p);
        if(upb!=w[pid].end()) return *upb-p+1;
        return *w[pid].begin()+n-p+1;
    };
    init("012");
    init("021");
    init("102");
    init("120");
    init("201");
    init("210");
    auto x=0,y=1,z=2,dx=0,dy=0,dz=0;
    cir(i,0,q){
        char c;cin>>c;
        if(c=='X'){
            int k;cin>>k;(dy+=n-k)%=n;
        }else if(c=='Y'){
            int k;cin>>k;(dx+=n-k)%=n;
        }else if(c=='I'){
            swap(y,z);swap(dy,dz);
        }else if(c=='C'){
            swap(x,z);swap(dx,dz);
        }else{
            cout<<check((string)("")+(char)(x+'0')+(char)(y+'0')+(char)(z+'0'),dx)<<'\n';
        }
    }
    return 0;
}
