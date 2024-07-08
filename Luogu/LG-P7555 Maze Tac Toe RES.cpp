#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto&get(string&s,int x,int y){return s[x*3+y-4];}
void exc(string&s,char c,int x,int y){
    char&sx=get(s,x,y);sx=(sx=='n'?c:sx);
}
vector<vector<unordered_map<string,bool>>> vis;
vector<int> mx{1,-1,0,0},my{0,0,1,-1};
vector<vector<string>> mp;
unordered_set<string> Ap;
int N;
bool inner(int&c){return c>=0&&c<N;}
bool ckw(char&a,char&b,char&c){
    return (a=='M'&&b=='O'&&c=='O')|(a=='O'&&b=='O'&&c=='M');
}
bool ckwin(string&s){
    return ckw(s[0],s[1],s[2])|ckw(s[3],s[4],s[5])|ckw(s[6],s[7],s[8])
        |ckw(s[0],s[3],s[6])|ckw(s[1],s[4],s[7])|ckw(s[2],s[5],s[8])
        |ckw(s[0],s[4],s[8])|ckw(s[2],s[4],s[6]);
}
void dfs(int x,int y,string&s){
    if(vis[x][y][s]) return;
    vis[x][y][s]=true;
    if(ckwin(s)){Ap.insert(s);return;}
    cir(i,0,4){
        int nx=x+mx[i],ny=y+my[i];
        if(inner(nx)&inner(ny)) continue;
        if(mp[nx][ny]=="###") continue;
        if(mp[nx][ny]=="..."){
            if(!vis[nx][ny].count(s)) dfs(nx,ny,s);
            continue;
        }
        char put=mp[nx][ny].front();
        int ncx=mp[nx][ny][1]-'0',ncy=mp[nx][ny][2]-'0';
        char nc=get(s,ncx,ncy);
        exc(s,put,ncx,ncy);
        if(!vis[nx][ny].count(s)) dfs(nx,ny,s);
        get(s,ncx,ncy)=nc;
    }
}
const string Bessie="BBB";
int main(){
    ios::sync_with_stdio(false), cin.tie(0);
    cin>>N;mp.assign(N,vector<string>(N));
    vis.assign(N,vector<unordered_map<string,bool>>(N));
    pair<int,int> st;
    cir(i,0,N) cir(j,0,N){
        auto&s=mp[i][j];char c;
        cir(i,0,3) cin>>c,s.push_back(c);
        if(s==Bessie) st={i,j};
    }
    string s="nnnnnnnnn";
    dfs(st.first,st.second,s);
    cout<<Ap.size()<<endl;
    return 0;
}
