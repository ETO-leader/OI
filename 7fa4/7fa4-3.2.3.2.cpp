#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#define getcha() (S==T&&(T=(S=fsr)+fread(fsr,1,1<<15,stdin),S==T)?EOF:*S++)
char fsr[1<<15],*S=fsr,*T=fsr;
inline int read(){
	int r(0),w(1);char ch;
	while(ch=getcha(),ch>=58||ch<=47) w=(ch=='-'?-1:1);r=(r<<3)+(r<<1)+ch-48;
	while(ch=getcha(),ch<=57&&ch>=48) r=(r<<3)+(r<<1)+ch-48;
	return r*w;
}
inline void put(int k){
    for(auto i:to_string(k)) putchar(i);
}
int main(){
    //ios::sync_with_stdio(false),cin.tie(0);
    int n;n=read();set<int> st;
    cir(i,1,n+1) st.insert(i);
    vector<int> id(n+1),ax(n);
    cir(i,0,n){
        int ki,cnt=0;ki=read();
        if(ki>*(--st.end())) cnt+=n-ki+1,ki=1;
        auto lb=st.lower_bound(ki);
        id[*lb]=i+1;ax[i]=((*lb)-ki+1+cnt);
        st.erase(lb);
    }
    for(auto&i:ax) put(i),putchar(' ');
    putchar('\n');
    cir(i,1,n+1) put(id[i]),putchar(' ');
    putchar('\n');
    return 0;
}