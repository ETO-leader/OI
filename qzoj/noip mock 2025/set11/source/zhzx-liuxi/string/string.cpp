#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int T,id;
	scanf("%d%d",&T,&id);
	while(T--)
	{
		int n,m;  	                    	
		string s1,s2;
		cin>>s1>>s2;
		n=s1.size();  m=s2.size();
		int f[n+1][m+1];
		memset(f,0,sizeof(f));
		f[0][0]=1;
		for(int i=0;i<=n;i++){
			for(int j=1;j<=m;j++){			
				if(s1[i-1]==s2[j-1])f[i][j]=max(f[i][j],f[i-1][j-1]);
				if(j>=2 && s2[j-1]==s2[j-2])f[i][j]=max(f[i][j],f[i][j-2]);
			}
		}
		if(f[n][m])printf("YES\n");
		else printf("NO\n");		
	}
	return 0;
}