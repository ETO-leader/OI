#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#if not defined(__DEBUG__)
ifstream inf("block.in");
ofstream ouf("block.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#define cin inf
#define cout ouf
#endif
static constexpr int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int cb,ci,cd,cc;cin>>cb>>ci>>cd>>cc;
    string a,b;cin>>a>>b;
    const int n=a.size(),m=b.size();
    vector<vector<array<int,2>>> f(
        n+1,vector<array<int,2>>(m+1,{_inf,_inf}));
    vector<vector<array<char,2>>> fr(
        n+1,vector<array<char,2>>(m+1));
    f[0][0][0]=0;
    cir(i,0,n+1) cir(j,0,m+1){
        auto&fn=f[i][j];
        if(fn[0]+cb<fn[1]){
            fn[1]=fn[0]+cb;
            fr[i][j][1]='S';
        }
        if(fn[1]<fn[0]){
            fn[0]=fn[1];
            fr[i][j][0]='E';
        }
        if(i<n&&fn[0]+cd<f[i+1][j][0]){
            f[i+1][j][0]=fn[0]+cd;
            fr[i+1][j][0]='D';
        }
        if(j<m&&fn[0]+ci<f[i][j+1][0]){
            f[i][j+1][0]=fn[0]+ci;
            fr[i][j+1][0]='I';
        }
        if(i<n&&j<m&&fn[0]+cc<f[i+1][j+1][0]&&a[i]==b[j]){
            f[i+1][j+1][0]=fn[0]+cc;
            fr[i+1][j+1][0]='C';
        }
        if(i<n&&fn[1]<f[i+1][j][1]){
            f[i+1][j][1]=fn[1];
            fr[i+1][j][1]='N';
        }
    }
    cout<<f[n][m][0]<<'\n';
    vector<pair<int,int>> dx;
    auto p=tuple(n,m,0);
    string ans;
    while(get<0>(p)||get<1>(p)){
        auto&[i,j,x](p);
        if(fr[i][j][x]=='N'){
            auto px=i;
            while(fr[px][j][x]=='N') --px;
            assert(fr[px][j][x]=='S');
            dx.push_back({px+1,i});
            p={px,j,0};
            continue;
        }
        if(fr[i][j][x]=='E'){
            p={i,j,1};continue;
        }
        ans.push_back(fr[i][j][x]);
        if(fr[i][j][x]=='D') --i;
        else if(fr[i][j][x]=='I') --j;
        else if(fr[i][j][x]=='C') --i,--j; 
    }
    sort(dx.begin(),dx.end());
    cout<<dx.size()<<'\n';
    for(const auto&[l,r]:dx) cout<<l<<' '<<r<<'\n';
    reverse(ans.begin(),ans.end());
    cout<<ans<<'\n';
    return 0;
}
