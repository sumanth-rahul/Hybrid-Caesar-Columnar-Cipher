#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cctype>
using namespace std;
string sanitize(string s) {
    string res = "";
    for (char c : s) {
        if (isalpha(c)) res += toupper(c);
        else if (isspace(c)) res += ' ';
    }
    return res;
}
string encrypt(string name,string hint){
	name=sanitize(name);
	hint=sanitize(hint);
	int n=hint.size(),m=(name.size()+hint.size()-1)/hint.size();
	vector<pair<char,int>> v;
	for(int i=0;i<hint.size();i++){
		v.push_back({hint[i],i});
	}
	sort(v.begin(),v.end());
	string pname="";
	for(int i=0;i<n*m;i++){
		if(i<name.size()){
			if(isspace(name[i]))
				pname+='0';
			else
				pname+=(char)((name[i]-'A'+hint.size())%26 +'A');
		}
		if(i>=name.size())
			pname+='1';
	}
	char pcode[m][n];
	string code="";
	int x=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			pcode[i][j]=pname[x];
			x++;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			int order=v[i].second;
			code+=pcode[j][order];
		}
	}
	return code;

}
string decrypt(string code,string hint){
	hint=sanitize(hint);
	int n=hint.size(),m=code.size()/hint.size();
	vector<pair<char,int>> v;
	for(int i=0;i<hint.size();i++){
		v.push_back({hint[i],i});
	}
	sort(v.begin(),v.end());
	char pcode[m][n];
	int x=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			pcode[j][i]=code[x];
			x++;
		}
	}
	string name="";
	char pname[m][n];
	for(int i=0;i<n;i++){
		int k =v[i].second;
		for(int j=0;j<m;j++){
			pname[j][k]=pcode[j][i];
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(pname[i][j]=='0')
				name+=' ';
			else if(pname[i][j]=='1'){
				continue;
			}
			else
				name+=(char)((pname[i][j]-'A'-hint.size()+26)%26+'A');
		}
	}
	return name;
}
//LENGTH OF HINT SHOULD BE LESS THAN OR EQUAL TO LENGTH OF THE CODE
int main(){
	int n;
	cout<<"1.encrypt\n2.decrypt\nenter your choice: ";
	cin>>n;
	if(n==1){
		string code,hint,scode;
		cin.ignore();
		cout<<"enter code: ";
		getline(cin,code);
		cout<<"enter hint: ";
		cin>>hint;
		cin.ignore();
		scode=encrypt(code,hint);
		cout<<scode<<"\n";
	}
	else if(n==2){
		string scode,hint,code;
		cin.ignore();
		cout<<"enter sender code: ";
		getline(cin,scode);
		cout<<"enter hint: ";
		cin>>hint;
		cin.ignore();
		code=decrypt(scode,hint);
		cout<<code<<"\n";
	}
	else
		cout<<"invalid choice";

	return 0;
}
