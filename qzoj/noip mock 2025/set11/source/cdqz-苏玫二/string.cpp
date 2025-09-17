#include<bits/stdc++.h> 
using namespace std;
const int N=1e5+50;
char x[N],s[N];
int n,m,flag;
void dfs(int xi,int si){
	if(xi>n){
		while(si<=m){
			if(s[si]!=s[si+1]) return ;
			si+=2;
		}
		flag=1;
		return ;
	}
	while(si+(n-xi)<=m){
		if(x[xi]==s[si]){
			dfs(xi+1,si+1);
			if(flag) return ;
		}
		if(s[si]==s[si+1])si+=2;
		else return ;
	}
}
int cnt[30];
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int T,id;scanf("%d %d",&T,&id);
	while(T--){
		scanf("%s",x+1);
		n=strlen(x+1);
		scanf("%s",s+1);
		m=strlen(s+1);
		if((m-n)&1) {
			printf("NO\n");
			continue;
		}
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=m;i++)
			cnt[s[i]-'a']++;
		for(int i=1;i<=m;i++)
			cnt[x[i]-'a']--;
		for(int i=0;i<26;i++){
			if(cnt[i]&1){
				printf("NO\n");
				flag=-1;
				break;
			}
 		}
 		if(flag=-1)continue;
 		cnt[0]=0;
 		for(int i=1;i<=m;i++){
 			if(s[i]==s[i+1]){
 				cnt[0]+=2;
 				i++;
			}
		}
		if(m-cnt[0]>n) {
			printf("NO\n");
			continue;
		}
		flag=0;
		dfs(1,1);
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
}
