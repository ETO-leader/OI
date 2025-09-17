#include<bits/stdc++.h>
using namespace std;
int n,m,T,id;
string s1,s2,s3;
bool dfs(int x,int y,int p=0)
{
	//cout<<x<<" "<<y<<"\n";
	if(s1.size()+p>s2.size()||y==s2.size()&&x<s1.size()) return false;
	if(x==s1.size())
	{
		//cout<<x<<" "<<y<<"\n";
		bool f=true;
		for(int i=y;i+1<s2.size();i+=2)
			if(s2[i]!=s2[i+1])
			{
				f=false;
				break;
			}
		if(f) return true;
		return false;
	}
	if(s1[x]==s2[y]&&dfs(x+1,y+1,p)) return true;
	//cout<<y<<"\n";
	for(int i=y;i+2<s2.size();i+=2)
		if(s2[i+2]==s1[x]&&s2[i]==s2[i+1]&&dfs(x+1,i+3,p+i-y+1)) return true;
		else if(s2[i]!=s2[i+1]) break;
	return false; 
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	cin>>T>>id;
	while(T--)
	{
		cin>>s1>>s2;
		if((s2.size()-s1.size())%2==1||s2.size()<s1.size())
		{
			cout<<"NO\n";
			continue;
		}
		if(dfs(0,0)) cout<<"YES\n";
		else cout<<"NO\n";
	}
}
