#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void write(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int id,n,k;
int a[N];
int c[N];
void add(int x,int ret){
	for(;x<=n;x+=x&-x)c[x]+=ret;
}
int ask(int x){
	int ret=0;
	for(;x;x-=x&-x)ret+=c[x];
	return ret;
}
struct node{
	int l,r;
}answer[N];
int geshu;
int tot;
int p;
signed main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout); 
	id=read(),n=read(),k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)geshu+=i-1-ask(a[i]),add(a[i],1);
	k=geshu-k;
	int tot=0;
	while(k!=0){
		memset(c,0,sizeof c);
		tot++;int now=0;
		int i=1,j=1;node ansi;int ans=0;
		for(;i<=n;i++){
			now+=i-j-ask(a[i]);
			add(a[i],1);
			if(now<=k){
				if(now>ans){
					ansi=(node){j,i};
					ans=now;
				}
			}else{
				while(j<=n && now>k){
					add(a[j],-1);
					now-=ask(a[j]);
					j++;
				}
				if(now>ans){
					ansi=(node){j,i};
					ans=now;
				}
			}
		}
		k-=ans;
		answer[tot]=ansi;
		sort(a+ansi.l,a+ansi.r+1);
	}
	write(tot);putchar('\n');
	for(int i=1;i<=tot;i++)write(answer[i].l),putchar(' '),write(answer[i].r),putchar('\n');
	return 0;
}
