#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
void exch(string&s,int x,int y,char c){
    if(s[3*x-4+y]=='n') s[3*x-4+y]=c;
}
const string Bessie="BBB";
unordered_set<string> Ap;
bool ckw(char a,char b,char c){
    return (a=='M'&&b=='O'&&c=='O')||(a=='O'&&b=='O'&&c=='M');
}
bool ckwin(string&s){
    return ckw(s[0],s[1],s[2])||ckw(s[3],s[4],s[5])||ckw(s[6],s[7],s[8])
        ||ckw(s[0],s[3],s[6])||ckw(s[1],s[4],s[7])||ckw(s[2],s[5],s[8])
        ||ckw(s[0],s[4],s[8])||ckw(s[2],s[4],s[6]);
}
vector<vector<unordered_map<string,bool>>> vis;
vector<vector<string>> vs;
vector<int> mx{-1,1,0,0},my{0,0,-1,1};
int n;
bool inner(int x,int y){return x>=0&&y>=0&&x<n&&y<n;}
void dfs(int x,int y,string&s){
    if(vis[x][y][s]) return;
    if(ckwin(s)){Ap.insert(s);return;}
    vis[x][y][s]=true;
    cir(i,0,4){
        int nx=mx[i]+x,ny=my[i]+y;
        if(inner(nx,ny)&&vs[nx][ny]!="###"){
            if(isdigit(vs[nx][ny][1])){
                auto&sx=vs[nx][ny];
                int ax=sx[1]-'0',ay=sx[2]-'0';
                char lc=s[ax*3-4+ay];exch(s,ax,ay,sx[0]);
                dfs(nx,ny,s);
                s[ax*3-4+ay]=lc;
            }else{
                dfs(nx,ny,s);
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>n;vis.assign(n,vector<unordered_map<string,bool>>(n));
    vs.assign(n,vector<string>(n));
    int xi=0,yi=0,gx,gy;
    for(auto&i:vs){
        for(auto&j:i){
            char c;
            cir(k,0,3) cin>>c,j.push_back(c);
            if(j==Bessie) gx=xi,gy=yi;
            yi++;
        }
        xi++,yi=0;
    }
    string s="nnnnnnnnn";
    dfs(gx,gy,s);
    cout<<Ap.size()<<endl;
    return 0;
}