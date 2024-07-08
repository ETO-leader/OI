#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const string dict="abcdefghijklmnopqrstuvwxyz+*/?";
using PRI=pair<int,int>;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int m;cin>>m;
        unordered_map<char,int> Ap;
        cir(i,0,m){
            string s;cin>>s;
            for(auto&i:s) Ap[i]++;
        }
        const int n=dict.size(),c=12;
        vector<vector<PRI>> D(n+1,vector<PRI>(c+1,{_inf,1}));
        //first -> val; second -> fro
        D[0][0]={0,0};
        cir(i,0,n) cir(j,0,c){
            int cnt=0;
            cir(k,i+1,n+1){
                if(D[i][j].first+(cnt+=Ap[dict[k-1]]*(k-i))<D[k][j+1].first)
                    D[k][j+1]={D[i][j].first+cnt,i};
            }
        }
        string s="\n";
        int u=n;
        for(int i=c;i-1;--i) u=D[u][i].second,s.push_back(dict[u]);
        reverse(s.begin(),s.end());
        cout<<s;
    }
    return 0;
}