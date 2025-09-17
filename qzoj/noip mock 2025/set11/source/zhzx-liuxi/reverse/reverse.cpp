#include<bits/stdc++.h>
using namespace std;
#define maxn 1001
#define rank ran
int num[maxn];
int siz[maxn];
int v[maxn];
int son[maxn][2];
int a[maxn];
int n,id,k;
int p=0;
int cnt=0;
int rd[maxn];
void pushup(int x){
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+num[p];
}
void rotate(int &p,int d){
	int k=son[p][d^1];
	son[p][d^1]=son[k][d];
	son[k][d]=p;
	pushup(p);
	pushup(k);
	p=k;
}
void insert(int &p,int x){
	if(!p){
		p=++cnt;
		num[p]=siz[p]=1;
		v[p]=x; rd[p]=rand(); return;
	}
	if(v[p]==x){
		num[p]++; siz[p]++; return;
	}
	int d=(x>v[p]);
	insert(son[p][d],x);
	if(rd[p]<rd[son[p][d]])rotate(p,d^1);
	pushup(p);
}
int rank(int p,int x){
	if(!p)return 1;
	if(v[p]==x)return siz[son[p][0]]+1;
	if(v[p]>x)return rank(son[p][0],x);
	if(v[p]<x)return siz[son[p][0]]+num[p]+rank(son[p][1],x);
}
int main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%d%d%d",&id,&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}

	int ra[maxn]; int sum=0;
	for(int i=1;i<=n;i++){
		insert(p,a[i]);
		ra[i]=rank(p,a[i]);	
		ra[i]=i-ra[i];
		sum+=ra[i];
	}
	int rest=sum-k;	
	if(id==3 || rest==0){
		printf("0\n"); return 0;
	}
	else if(id==0 || id==1 || id==2){
		int cnt=0; vector<int>l,r;
		while(rest){
			for(int i=1;i<=n-1;i++){
				if(rest==0)break;
				if(a[i]>a[i+1])rest--,cnt++,l.push_back(i),r.push_back(i+1);
			}
		}
		cout<<cnt<<endl;
		for(int i=0;i<cnt;i++){
			cout<<l[i]<<" "<<r[i]<<endl;
		}
		return 0;
	}
	int ans=0;
	int l[10001],r[10001];  r[0]=-1;
	for(int i=1;i<=n;i++){
		if(!rest)break;		
		while(ra[i]>rest)i++;
		rest-=ra[i];
		if(r[ans]+1==i)r[ans]=i;
		else{
			l[++ans]=i; r[ans]=i; 
		}		
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++){
		printf("%d %d\n",l[i],r[i]);
	}
	return 0;
}