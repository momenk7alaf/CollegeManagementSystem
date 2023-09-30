#include "Doctor.h"
#include "Student.h"


Doctor::Doctor(string title, string name, string password, string id) :User(title, name, password, id) {}

Doctor::Doctor() :User() {}

string Doctor::set_Courses(stringstream& index)
{
	short houre;
	string CourseName, CourseID, Assistant, assistId;
	index >> CourseName >> CourseID >> houre >> Assistant >> assistId;
	this->Courses[CourseName].ID = CourseID;
	this->Courses[CourseName].AssistName = Assistant;
	this->Courses[CourseName].CHoure = houre;
	this->Courses[CourseName].AssistID = assistId;
	return CourseName;
}

void Doctor::set_Exams(string CourseName, stringstream& index)
{
	short ExamDegree;
	string  ExamName, ExamID;
	while (index >> ExamName >> ExamID >> ExamDegree)
	{
		this->Courses[CourseName].Exams[ExamName].examName = ExamName;
		this->Courses[CourseName].Exams[ExamName].exmamDegree = ExamDegree;
		this->Courses[CourseName].Exams[ExamName].examID = ExamID;
		this->Courses[CourseName].Exams[ExamName].courseName = CourseName;
	}
}

void Doctor::get_Data()
{
	for (auto& i : Courses)
	{
		cout << this->get_Name() << " " << i.first << " " << i.second.CHoure << " " << i.second.AssistName << " " << i.second.AssistID << endl;
		for (const auto& j : i.second.prereqForCors)
		{
			cout << j << " ";
		}cout << endl;
		for (auto& j : i.second.Exams)
		{
			cout << j.second.examName << " " << j.second.exmamDegree << " " << j.second.examID << endl;
			for (auto& z : j.second.Dgrees)
			{
				cout << z.second.name << " " << z.second.degree << endl;
			}
		}
		for (auto& j : i.second.RegStudent)
		{
			cout << j << " ";
		}cout << endl;
		cout << "----------------------------------------------------\n\n";
	}
}

void Doctor::set_pre(stringstream& in)
{
	string cnm, tmp;
	in >> cnm;
	while (in >> tmp)
	{
		Courses[cnm].prereqForCors.insert(tmp);
	}
}

void Doctor::set_exams_degree(stringstream& in)
{
	short degree;
	string name, id, examname, cnm, status;
	in >> id >> name >> status >> degree >> cnm >> examname;
	Courses[cnm].Exams[examname].Dgrees[id] = (Degree(id, name, degree, status));
	S_Degree[id].insert({ cnm,examname });
}

void Doctor::set_Registers(stringstream& in)
{
	string coursNm, tmpids;
	in >> coursNm;
	while (in >> tmpids)
	{
		this->Courses[coursNm].RegStudent.insert(tmpids);
		this->S_Courses[tmpids].insert(coursNm);
	}
}

void Doctor::delete_course()
{
	string coursen;
	cout << "Enter Course Name --> ";
	cin >> coursen;
	const string dst{ "database\\Books\\" + this->Courses[coursen].ID + ".txt" };
	for (auto& i : this->Courses[coursen].Exams)
	{
		for (auto& j : this->S_Degree)
		{
			j.second.erase({ i.second.courseName,i.second.examName });
		}
		const string dst{ "database\\Exams\\" + i.second.examID + ".txt" };
		remove(dst.c_str());
	}
	this->S_Courses.erase(coursen);
	Courses.erase(coursen);
	remove(dst.c_str());
	system("cls");
	cout << "Completed \n";
	Sleep(1000);
}

void Doctor::delete_exam()
{
	string exnm, coursnm;
	cout << "Enter Course Name  : ";
	cin >> coursnm;
	cout << "Enter Exam Name    : ";
	cin >> exnm;
	const string dst{ "database\\Exams\\" + Courses[coursnm].Exams[exnm].examID + ".txt" };
	remove(dst.c_str());
	Courses[coursnm].Exams.erase(exnm);
	system("cls");
	cout << "Completed \n";
	Sleep(1000);
}

void Doctor::add_course()
{
	cout << "Enter Course Name : ";
	short hour;
	string cnm, book, prereq, tmp, assistnam, assistid;
	cin >> cnm;
	cout << "Enter Course Time : ";
	cin >> hour;
	cout << "Enter Assistant Name : ";
	cin >> assistnam;
	cout << "Enter Assistant ID : ";
	cin >> assistid;
	Courses[cnm].AssistName = assistnam;
	Courses[cnm].AssistID = assistid;
	cout << "Enter prerequisites courses seprated by spaces  --->  ";
	cin.ignore();
	getline(cin, prereq);
	stringstream in{ prereq };
	while (in >> tmp)
	{
		Courses[cnm].prereqForCors.insert(tmp);
	}
	cout << "Enter The Path Of The Book To Upload: ";
	//cin.ignore();
	string Id = to_string(10000 + rand() % 20001);
	Courses[cnm].ID = Id;
	Courses[cnm].CHoure = hour;
	getline(cin, book);
	if (book.front() == '"')
	{
		book.erase(0, 1);
		book.pop_back();
	}
	const string dst{ "database\\Books\\" + Courses[cnm].ID + ".txt" };
	std::filesystem::copy_file(book, dst);
	system("cls");
	cout << "Completed \n";
	Sleep(1000);
}

void Doctor::add_exam()
{
	string cnm, expath, exnm;
	short examdegr;
	cout << "Enter Course Name : ";
	cin >> cnm;
	cout << "Enter Exam Name   :";
	cin >> exnm;
	cout << "Enter Exam Degree   :";
	cin >> examdegr;
	cout << "Enter The Path Of The Exam `.txt file` To Upload: ";
	cin.ignore();
	getline(cin, expath);
	if (expath.front() == '"')
	{
		expath.erase(0, 1);
		expath.pop_back();
	}
	string Id = to_string(10000 + rand() % 20001);
	Courses[cnm].Exams[exnm].examID = Id;
	Courses[cnm].Exams[exnm].examName = exnm;
	Courses[cnm].Exams[exnm].exmamDegree = examdegr;
	const string dst{ "database\\Exams\\" + Courses[cnm].Exams[exnm].examID + ".txt"};
	std::filesystem::copy_file(expath, dst);
	system("cls");
	cout << "Completed \n";
	Sleep(1000);
}

void Doctor::Write(const string path, bool& mode)
{
	fstream File;
	if (mode) {
		File.open(path, ios::out);
		mode = false;
	}
	else { File.open(path, ios::app); }
	if (File.is_open())
	{
		if (this->data_ptint().find("D") == string::npos) { return; }
		File << "{" << endl;
		//set user data
		File << this->data_ptint() << endl;
		//set courses data
		for (auto& i : this->Courses)
		{
			File << i.first << " " <<
				i.second.ID << " " <<
				i.second.CHoure << " " <<
				i.second.AssistName << " " <<
				i.second.AssistID << " ";
			for (auto& j : i.second.Exams)
			{
				File << j.second.examName << " " <<
					j.second.examID << " " <<
					j.second.exmamDegree << " ";
			}
			File << endl;
		}
		//set prerequisites For Courses
		File << "#s" << endl;
		for (auto& i : this->Courses)
		{
			if (!i.second.prereqForCors.empty()) {
				File << i.first << " ";
				for (auto& j : i.second.prereqForCors)
				{
					File << j << " ";
				}
				File << endl;
			}
		}
		File << "#e" << endl;
		//set Registered students
		File << "#s" << endl;
		for (auto& i : this->Courses)
		{
			if (!i.second.RegStudent.empty()) {
				File << i.first << " ";
				for (auto& j : i.second.RegStudent)
				{
					File << j << " ";
				}
				File << endl;
			}
		}
		File << "#e" << endl;
		//set students degrees
		File << "#s" << endl;
		for (auto& i : this->Courses)
		{
			for (auto& j : i.second.Exams)
			{
				for (auto& z : j.second.Dgrees)
				{
					File << z.second.data_print() << " " << j.second.courseName << " " << j.second.examName << endl;
				}
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


void Doctor::Show_courses()
{
	system("cls");
	int choice;
	for (auto& i : this->Courses)
	{
	cout << "____________________________________________________________________\n";
		cout << "Course Name : " << i.first << endl;
		cout << "Course ID   : " << i.second.ID << endl;
		cout << "Assistant Name: " << i.second.AssistName << endl;
		cout << "Assistant ID: " << i.second.AssistID << endl;
		cout << "Time : " << i.second.CHoure << endl;
		cout << "Registered Students : " << i.second.RegStudent.size() << endl;
		cout << "Prerequisites for Course : ";
		for (auto& j : i.second.prereqForCors)
		{
			cout << j << " ";
		}cout << endl;
		cout << "................................\n";
		cout << "Exams -> " << endl;
		for (auto& j : i.second.Exams)
		{
			cout << "Exam Name : " << j.second.examName << endl;
			cout << "Exam ID : " << j.second.examID << endl;
			cout << "Exam Degree : " << j.second.exmamDegree << endl;
			cout << "Number of Examinees : " << j.second.Dgrees.size() << endl;
			cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		}
		cout << "................................\n";
	cout << "____________________________________________________________________\n";
	}
	cout << "(1)Return\n(2)Remove Course\n(3)Remove Exam\n---= ";
	cin >> choice;
	if (choice == 2)
	{
		this->delete_course();
		Show_courses();
	}
	else if (choice == 3)
	{
		this->delete_exam();
		Show_courses();
	}
	else {
		return;
	}
}

void Doctor::Info_save(bool mode)
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

void Doctor::Course_In()
{
	system("cls");
	cout << "(1)Create Course\n(2)Add Exam\n(3)Show Course\n(4)Return\n\n---> ";
	int choise;
	cin >> choise;
	string c_id = to_string(10000 + rand() % 20001);
	if (choise == 1)
	{
		add_course();
	}
	else if (choise == 2) {
		add_exam();
	}
	else if (choise == 3)
	{
		Show_courses();
	}
}

void Doctor::Grades()
{
	string exname, cname;
	cout << "Enter Course Name : ";
	cin >> cname;
	cout << "Enter Exam Name   : ";
	cin >> exname;
	system("cls");
	for (auto& i : this->Courses[cname].Exams[exname].Dgrees)
	{
		cout << i.second.name << "\t" << i.second.degree <<"\tFrom\t"<< this->Courses[cname].Exams[exname].exmamDegree << endl;
	}
	cout << "..........................................................\n(1)Return\n";
	cin >> cname;
}

void Doctor::Interface(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
{
	system("cls");
	Info_save(1);
	string view = "Welcome Dr." + this->get_Name() + "\n (1)Manage\n (2)Grades\n (3)Messages\n (4)Logout\n\nEnter:";
	for (auto& i : view)
	{
		cout << i;
	}
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		Course_In();
		Write(Doctors, Assistants, Students);
		break;
	case 2:
		Grades();
		break;
	case 3:
		Show_M(this->get_Id(), this->get_Name());
		break;
	case 4:
		Info_save(0);
		return;
	}
	Interface(Doctors, Assistants, Students);
	Write(Doctors, Assistants, Students);
}

void Doctor::Write(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
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