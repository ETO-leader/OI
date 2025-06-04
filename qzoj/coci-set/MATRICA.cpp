#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    vector<int> cnt(27);
    cnt[26]=114514;
    auto sum=0;
    cir(i,0,k){
        string s;int c;cin>>s>>c;
        cnt[s[0]-'A']=c;sum+=c;
    }
    stack<int> stc;
    for(auto i=25;~i;--i) if(cnt[i]&1){
        cnt[i]-=1;
        stc.emplace(i);
    }
    int c;cin>>c;
    vector<int> exist(n);
    vector<int> rnk;
    cir(i,0,c){
        int x;cin>>x;--x;
        exist[x]=true;
        rnk.emplace_back(x);
    }
    vector<vector<char>> str(n);
    for(auto&i:rnk) str[i].resize(n);
    if(sum!=n*n||(int)(stc.size())>n||((n-(int)(stc.size()))&1)){
        cout<<"IMPOSSIBLE\n";
    }else{
        auto cur=0;
        cir(i,0,n) cir(j,i,n){
            while(!cnt[cur]) ++cur;
            if(i<j){
                if(exist[j]) str[j][i]=(char)(cur+'A');
                if(exist[i]) str[i][j]=(char)(cur+'A');
                cnt[cur]-=2;
            }else{
                if((!stc.empty())&&(stc.top()<cur+1||(int)(stc.size())+1>n-i-2)){
                    if(exist[j]) str[j][i]=(char)(stc.top()+'A');
                    if(exist[i]) str[i][j]=(char)(stc.top()+'A');
                    stc.pop();
                }else{
                    if(exist[j]) str[j][i]=(char)(cur+'A');
                    if(exist[i]) str[i][j]=(char)(cur+'A');
                    cnt[cur]-=2;
                    stc.emplace(cur);
                }
            }
        }
        cir(i,0,n){
            for(auto&x:rnk) cout<<str[x][i];
            cout<<'\n';
        }
    }
    return 0;
}
