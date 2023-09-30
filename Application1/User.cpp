#include "User.h"

//User
User::User(string title, string name, string password, string id) :title(title), name(name), password(password), id(id)
{
	//date
	string dat = __DATE__ " " __TIME__;
	replace(dat.begin(), dat.end(), ' ', '-');
	this->date = dat;
}

void User::set_data(string tit, string id, string nam, string pas, string dat)
{
	this->title = tit;
	this->id = id;
	this->name = nam;
	this->password = pas;
	this->date = dat;
}

void User::data()const
{
	cout << "Name       : " << this->name << endl;
	cout << "ID         : " << this->id << endl;
	cout << "Title      : " << this->title << endl;
	cout << "Date       : " << this->date << endl;
	cout << "password   : " << this->password << endl;
	cout << "________________________________________________________________________________\n\n";
}


string User::get_Id() { return id; }

string User::get_Name() { return name; }

string User::data_ptint()
{
	stringstream in;
	in << title << " " << id << " " << name << " " << password << " " << date;
	return in.str();
}

string User::get_password() { return this->password; }
bool User::check(string id, string pass) { return this->id == id && this->password == pass; }

//Degree

Degree::Degree() { degree = 0; }

Degree::Degree(string id, string name, short degree, string status)
	:id(id), name(name), degree(degree), status(status) {}

bool Degree::operator<(const Degree& other) const {
	return (this->degree) >= (other.degree);
}

string Degree::data_print()
{
	stringstream in;
	in << id << " " << name << " " << status << " " << degree;
	return in.str();
}

