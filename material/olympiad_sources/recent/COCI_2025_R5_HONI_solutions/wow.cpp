#include <iostream>

using namespace std;

int main()
{
	int n;
	string a,b;
	cin>>n>>a>>b;
	for (int i=0;i<n;++i)
	{
		if (i==n-4 || a[i+4]=='.') cout<<'v',i+=4;
		else cout<<'w',i+=8;
	}
	cout<<endl;
}
