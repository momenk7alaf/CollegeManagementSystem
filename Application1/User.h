#pragma once
#include "main.h"
class User {
private:
	string title, id, name, password, date;
public:
	User() {}
	User(string title, string name, string password, string id);
	void set_data(string tit, string id, string nam, string pas, string dat);
	void data() const;
	string get_Id();
	string get_Name();
	string data_ptint();
	string get_password();
	bool check(string id, string pass);
};

class Degree
{
public:
	string id, name, status;
	short degree;
	Degree();
	Degree(string id, string name, short degree, string status);
	bool operator<(const Degree& other) const;
	string data_print();
};