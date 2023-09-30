#include "Messages.h"
void ChatWith(const string path, string sender, string sendername, string resiver, string resivername)
{
l:  system("cls");
	fstream message(path, std::ios::in);
	string tmp;
	while (getline(message, tmp))
	{
		stringstream input{ tmp };
		string sndr, sndrname, resv, resvname,in;
		input >> sndr >> sndrname >> resv >> resvname >> in;
		replace(in.begin(), in.end(), '-', ' ');
		if (sndr == sender && resv == resiver)
		{
			cout << sndrname << " : " << in << endl;
			
		}
		else if (sndr == resiver && resv == sender)
		{
			cout << sndrname << " : " << in << endl;
		}
	}
	message.close();
	cout << "(1)Send\n(2)Refresh\n(3)Return\nEnter: ";
	short s;
	cin >> s;
	if (s == 1)
	{
		Send_M(path, sender, sendername, resiver, resivername);
	}
	else if(s==2) {
		goto l;
	}
	return;
}
void Show_M(string ID,string name)
{
	system("cls");
	unordered_map<string,set<string>>container;
	const string path = "database\\messages.txt";
	fstream message(path, std::ios::in);
	string tmp;
	unordered_map<string, string>ids;
	while (getline(message, tmp))
	{
		stringstream input{ tmp };
		string sndr, sndrname, resv, resvname;
		input >> sndr >> sndrname >> resv >> resvname;
		container[sndr].insert(resvname);
		container[resv].insert(sndrname);
		ids[sndrname] = sndr;
		ids[resvname] = resv;
	}
	message.close();
	int n = 1;
	cout << "___________________________________________________\n";
	for (auto& i : container[ID])
	{
		cout << "(" << n << ")" << i << "*" << endl;
		n++;
	}
	cout << "___________________________________________________\n";
	cout << "(1)Send Message \n(2)ChatWith\n(3)Return\nEnter: ";
	short s;
	cin >> s;
	if (s == 1)
	{
		string resiver,resname;
		cout << "Enter Resiver Name : ";
		cin >> resname;
		cout << "Enter Resiver ID : ";
		cin >> resiver;
		Send_M(path, ID, name, resiver, resname);
	}
	else if (s == 2)
	{
		string resname;
		cout << "Enter  Name : ";
		cin >> resname;
		ChatWith(path, ID, name, ids[resname], resname);
	}
	return;
}

void Send_M(const string path, string sender, string sendername, string resiver,string resivername)
{
	fstream message(path, std::ios::app);
	string content;
	cout << "ENTER CONTENT : ";
	cin.ignore();
	getline(cin, content);
	replace(content.begin(),content.end(), ' ', '-');
	message << sender << " " << sendername <<
		" " << resiver << " " 
		<< resivername << " " <<
		content << endl;
	message.close();
	ChatWith(path, sender, sendername, resiver, resivername);
}



