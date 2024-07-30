#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class link_cut_tree{
private:
    struct node{int siz,vsiz,vmsiz,msiz;};
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f,rev;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto getch(int u){return rs(f[u])==u;}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto push_down(int u){
        if(!rev[u]) return;
        for(auto x:{ls(u),rs(u)}) rev[x]^=true;
        swap(ls(u),rs(u));
        rev[u]=false;
    }
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+tr[u].vsiz;
        tr[u].msiz=max({tr[ls(u)].msiz,tr[rs(u)].msiz,tr[u].vmsiz});
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu],c=(int)(getch(u));
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        maintain(fu);maintain(u);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    return 0;
}
