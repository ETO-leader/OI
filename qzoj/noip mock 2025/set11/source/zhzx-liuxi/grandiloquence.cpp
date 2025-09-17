#include<bits/stdc++.h>
using namespace std;
#define maxn 200001
int rnk[maxn];
int siz[maxn];
int num[maxn];
int n,m,k;
int co[maxn]={0};
int subtaskid;
int fa[maxn];
vector<int>e[maxn];
int pre(int x,int fa){
	siz[x]=1;
	for(int i=0;i<e[x].size();i++){
		int to=e[x][i]; 
		siz[x]+=pre(to,x);
	}
	return siz[x];
}
int query(int x,int c){
	int sum=(co[x]==c);
	for(int i=0;i<e[x].size();i++){
		int to=e[x][i];
	    int d=query(to,c);
	    sum+=d;
	}
	return sum;
}
void Modify(int x,int c,int s){
	co[x]=(s+c-1)%k+1;
	for(int i=0;i<e[x].size();i++){
		int to=e[x][i];
		Modify(to,c,s+1);
	}
}
void Change(int x){
	if(x==0)return;
	siz[x]++;  Change(fa[x]);
}
void Update(int x,int d){
	if(x==0)return;
	num[x]+=d; Update(fa[x],d);
}
int cnt;
int main(){
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	scanf("%d",&subtaskid);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&fa[i]); e[fa[i]].push_back(i);
	}
	cnt=n;
	pre(1,fa[1]);
	if(k==1 && n>6000 && m>6000){
		int pastanswer=0;
		int opt,x,c;
		for(int i=1;i<=m;i++){
			scanf("%d%d",&opt,&x);
			if(opt==1){
				scanf("%d",&c);
				if(subtaskid%2==0)x=x xor pastanswer,c=c xor pastanswer;
				int d=siz[x]-num[x];
				Update(x,d);
			}
			else if(opt==2){
				scanf("%d",&c);
				if(subtaskid%2==0)x=x xor pastanswer,c=c xor pastanswer;
				int ans;
				if(c==1)ans=num[x];
				else ans=0;
				pastanswer=ans;
				printf("%d\n",ans);
			}
			else{
				if(subtaskid%2==0)x=x xor pastanswer;
				int p=++cnt; fa[p]=x;
				e[x].push_back(p);
				Change(p);
			}
		}
	}
	else
	{
		int pastanswer=0;
		int opt,x,c;
		for(int i=1;i<=m;i++){	
			scanf("%d%d",&opt,&x);
			if(opt==1){
				scanf("%d",&c);
				if(subtaskid%2==0)x=x xor pastanswer,c=c xor pastanswer;
				Modify(x,c,0);
			}
			else if(opt==2){
				scanf("%d",&c);
				if(subtaskid%2==0)x=x xor pastanswer,c=c xor pastanswer;
				int ans=query(x,c);
				pastanswer=ans;
				printf("%d\n",ans);
			}
			else{
				if(subtaskid%2==0)x=x xor pastanswer;
				int p=++cnt; fa[p]=x;
				e[x].push_back(p);
			}
		}		
	}
	return 0;
}