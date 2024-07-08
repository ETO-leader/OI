#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<int> un,Nxt;
const int NN=1e7+7;
bool seven(int x){return to_string(x).find('7')!=string::npos;}
void init(){
    int lap=1;
    un.resize(NN);Nxt.resize(NN);
    cir(i,1,NN){
        if(un[i]) continue;
        if(seven(i)) for(int j=i;j<NN;j+=i) un[j]=true;
        un[i]=seven(i);if(!un[i]) Nxt[lap]=i,lap=i;
    }
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T;cin>>T;init();
    while(T--){
        int x;cin>>x;
        cout<<(un[x]?-1:Nxt[x])<<endl;
    }
	return 0;
}