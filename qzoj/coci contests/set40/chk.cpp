#include<bits/stdc++.h>
#include"testlib.h"
using namespace std;
map<char,int>dict={{'U',0},{'L',1},{'R',2},{'D',3}};
const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};
int R,S,K,f[1000001];
char maps[1000001];
bool col[1000001],vis[1000001];
int dfs(int idx)
{
    if((idx-1)%S+1==S)return col[idx];
    if(vis[idx])return -2;
    vis[idx]=true;
    int nxt=dfs(((idx-1)/S+dx[dict[maps[idx]]])*S+(idx-1)%S+dy[dict[maps[idx]]]+1);
    return f[idx]=(nxt==-2)?-2:col[idx]+nxt;
}
int main(int argc,char *argv[])
{
    registerTestlibCmd(argc,argv);
    R=inf.readInt(),S=inf.readInt(),K=inf.readInt();
    for(int i=1;i<=R;++i)
    {
        for(int j=1;j<=S;++j)
        {
            int idx=(i-1)*S+j;
            do maps[idx]=inf.readChar();
            while(!isupper(maps[idx]));
        }
    }
    if(ans.readInt()==-1)
    {
        if(ouf.readInt()==-1)quitf(_ok,"No existence");
        quitf(_wa,"No existence");
    }
    for(int i=1,A,B;i<=K;++i)
    {
        A=ouf.readInt(1,R);
        ouf.readSpace();
        B=ouf.readInt(1,S-1);
        if(i!=K)ouf.readEoln();
        int idx=(A-1)*S+B;
        if(col[idx])quitf(_wa,"Repetitive field");
        col[idx]=true;
    }
    memset(f,-1,sizeof(f));
    for(int i=1;i<=S;++i)
    {
        int idx=(i-1)*S+1;
        if(f[idx]==-1)f[idx]=dfs(idx);
        if(f[idx]!=1&&f[idx]!=-2)quitf(_wa,"Illgeal inital point (%d,1)",i);
    }
    quitf(_ok,"%d field(s)",K);
    return 0;
}
