#include "Assistant.h"
#include "Doctor.h"
#include "Student.h"

Assistant::Assistant(string title, string name, string password, string id) :User(title, name, password, id) {}

Assistant::Assistant() :User() {}

void Assistant::set_Assignments(stringstream& in)
{
	string id, course, did, assnm;
	short assimdgr;
	in >> id >> course >> did >> assnm >> assimdgr;
	Assigment[id].AssignmentID = id;
	Assigment[id].CourseName = course;
	Assigment[id].doctoreID = did;
	Assigment[id].AssignmentName = assnm;
	Assigment[id].AssignmentDegree = assimdgr;
	//Set data
	Assignments_[course].insert(id);
}

void Assistant::set_degrees(stringstream& in)
{
	short degr;
	string assid, course, id, name, stat;
	in >> assid >> course >> id >> name >> stat >> degr;
	Assigment[assid].degrees[id] = (Degree(id, name, degr, stat));

}

void Assistant::get_Data()
{
	for (auto& i : Assigment)
	{
		cout << i.second.AssignmentID << " " << i.second.AssignmentName << " " << i.second.AssignmentDegree << " " << i.second.doctoreID << endl;
	}
}

void Assistant::Info_save(bool mode)
{
	string path = "database\\info.txt";
	if (mode) {
		fstream data{ path,ios::out };
		if (data.is_open()) { data << this->get_Id() << " " << this->get_password() << endl; data.close(); }
		else { cout << "Failed to save !!" << endl; }
	}
	else {
		fstream data{ path,ios::out };
		data.clear();
		data.close();
	}
}

void Assistant::Write(const string path, bool& mode)
{
	fstream File;
	if (mode) {
		File.open(path, ios::out);
		mode = false;
	}
	else { File.open(path, ios::app); }
	if (File.is_open())
	{
		File << "{" << endl;
		//set user data
		File << this->data_ptint() << endl;
		//set assignments data
		for (auto& i : this->Assigment)
		{
			File << i.second.AssignmentID << " " <<
				i.second.CourseName << " " <<
				i.second.doctoreID << " " <<
				i.second.AssignmentName << " " <<
				i.second.AssignmentDegree << endl;
		}
		File << "#s" << endl;
		for (auto& i : this->Assigment)
		{
			for (auto& j : i.second.degrees)
			{
				File << i.second.AssignmentID << " " <<
					i.second.CourseName << " " <<
					j.second.data_print() << endl;
			}
		}
		File << "#e" << endl;
		File << "}" << endl;
		File.close();
	}
	else {
		cout << "FileErro in " << path << endl;
		return;
	}
}

void Assistant::Write(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
{
	const string path{ "database\\data.txt" };
	bool mode = true;
	for (auto& i : Doctors)
	{
		i.second.Write(path, mode);
	}
	for (auto& i : Assistants)
	{
		i.second.Write(path, mode);
	}
	for (auto& i : Students)
	{
		i.second.Write(path, mode);
	}
}

void Assistant::Interface(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
{
	system("cls");
	string view = "Welcome "+this->get_Name() + "\n (1)Manage\n (2)Messages\n (3)Logout\n\nEnter:";
	for (auto& i : view)
	{
		cout << i;
	}
	int choice;
	cin >> choice;
	Info_save(1);
	switch (choice)
	{
	case 1:
		Manage();
		Write(Doctors, Assistants, Students);
		break;
	case 2:
		Show_M(this->get_Id(), this->get_Name());
		break;
	default:
		Info_save(0);
		return;
	}
	Interface(Doctors, Assistants, Students);
}

void Assistant::Manage()
{
	system("cls");
	cout << "(1)Add Assignment\n(2)Delete Assignment\n(3)Show Assignments\n(4)Show Grades\n(5)Return\n Enter : ";
	short choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		Add_Assignment();
		break;
	case 2:
		Delete_Assignment();
		break;
	case 3:
		Show_Assignments();
		break;
	case 4:
		Show_Grades();
		break;
	default:
		return;
	}
}

void Assistant::Add_Assignment()
{
	system("cls");
	string nm, cnm,dri;
	short dgr;
	cout << "Enter Doctor ID : ";
	cin >> dri;
	cout << "Enter Course Name : ";
	cin >> cnm;
	cout << "Enter Assignment Name : ";
	cin >> nm;
	cout << "Enter Assignment Degree : ";
	cin >> dgr;
	string Id = to_string(10000 + rand() % 20001);
	this->Assigment[Id].AssignmentID = Id;
	this->Assigment[Id].AssignmentDegree = dgr;
	this->Assigment[Id].CourseName = cnm; 
	this->Assigment[Id].AssignmentName = nm; 
	this->Assigment[Id].doctoreID = dri; 
	this->Assignments_[cnm].insert(Id);
	//Upload Src Assignment
	string dst = "database\\Assignments\\" + Id + ".txt";
	cout << "Enter Assignment Path : ";
	cin.ignore();
	string srcfile;
	getline(cin, srcfile);
	if (srcfile.front() == '"')
	{
		srcfile.erase(0, 1);
		srcfile.pop_back();
	}
	std::filesystem::copy_file(srcfile, dst);
	cout << "Completed\n";
	Sleep(1000);
}



void Assistant::Show_Assignments()
{
	system("cls");
	for (auto& i : this->Assigment)
	{
		cout << "Course Name  >" << i.second.CourseName << endl;
		cout << "Assignment Name >" << i.second.AssignmentName << endl;
		cout << "Assignment ID >" << i.second.AssignmentID << endl;
		cout << "Assignment Degree >" << i.second.AssignmentDegree << endl;
		cout << "registered Students >" << i.second.degrees.size() << endl;
		cout << "..........................................................................\n";
	}
	cout << "(1)Return\nEnter: ";
	short s;
	cin >> s;
}

void Assistant::Delete_Assignment()
{
	string asid, cnm;
	cout << "Enter Course Name : ";
	cin >> cnm;
	cout << "Enter Assignment ID : ";
	cin >> asid;
	string Path = "database\\Assignments\\" + asid + ".txt";
	this->Assigment.erase(asid);
	this->Assignments_[cnm].erase(asid);
	remove(Path.c_str());
}

void Assistant::Show_Grades()
{
	string nm;
	cout << "Enter Course Name : ";
	cin >> nm;
	system("cls");
	for (auto& i : this->Assignments_[nm])
	{
		cout << "Assignment Name : " << this->Assigment[i].AssignmentName << " , ";
		cout << "Degree : " << this->Assigment[i].AssignmentDegree << endl;
		for (auto& j : this->Assigment[i].degrees)
		{
			cout << j.second.name << " " << j.second.degree << endl;
		}
		cout << "..........................................................................\n";
	}
	cout << "(1)Return\nEnter: ";
	short s;
	cin >> s;
}