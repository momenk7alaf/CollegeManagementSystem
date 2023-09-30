#include "Student.h"


Student::Student() :User() { Recordedhours = 0; }
Student::Student(string title, string name, string password, string id) :User(title, name, password, id) { Recordedhours = 0; }

void Student::Write(const string path, bool& mode)
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
		File << "}" << endl;
	}
}

//Filters 

void Student::Filter(Doctor doctor)
{
	for (auto& i : doctor.S_Courses[this->get_Id()])
	{
		this->Courses[i].CourseName = i;
		this->Courses[i].Book = doctor.Courses[i].ID;
		this->Courses[i].DoctorID = doctor.get_Id();
		this->Courses[i].DoctorName = doctor.get_Name();
		this->Courses[i].AssistName = doctor.Courses[i].AssistName;
		this->Courses[i].AssistID = doctor.Courses[i].AssistID;
		this->Courses[i].Chour = doctor.Courses[i].CHoure;
		for (auto& j : doctor.Courses[i].Exams)
		{
			string examName =j.second.examName;
			string examID = j.second.examID;
			short exmamDegree = j.second.exmamDegree;
			short DgreOfExam = j.second.Dgrees[this->get_Id()].degree;
			this->Courses[i].Exams[examName] = (Student::Exam(examName, examID, exmamDegree, DgreOfExam));
		}
	}
	for (auto& i : doctor.S_Degree[this->get_Id()])//Student id => {Course Name ,Exam Name}
	{
		string examName = i.second;
		string examID = doctor.Courses[i.first].Exams[examName].examID;
		short exmamDegree = doctor.Courses[i.first].Exams[examName].exmamDegree;
		short DgreOfExam = doctor.Courses[i.first].Exams[i.second].Dgrees[this->get_Id()].degree;
		this->Courses[i.first].Exams[examName]=(Student::Exam(examName, examID, exmamDegree, DgreOfExam));
	}
}
void Student::Filter(Assistant assistant)
{
	Recordedhours = 0;
	for (auto& i : this->Courses)
	{
		for (auto& j : assistant.Assignments_[i.first])
		{
			Recordedhours += this->Courses[i.first].Chour;
			string assName = assistant.Assigment[j].AssignmentName;
			string assID = assistant.Assigment[j].AssignmentID;
			short assDegree = assistant.Assigment[j].AssignmentDegree;
			short DgreOfAss = assistant.Assigment[j].degrees[this->get_Id()].degree;
			this->Courses[i.first].AssistID = assistant.get_Id();
			this->Courses[i.first].AssistName = assistant.get_Name();
			i.second.Assignments[assName] = (Student::Assignment(assName, assID, assDegree, DgreOfAss));
		}
	}
}

void Student::Info_save(bool mode)
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
float Student::Score_Of(string CourseName)
{
	if (this->Courses.find(CourseName) != this->Courses.end())
	{
		pair<float, float>degre;
		for (auto& i : this->Courses[CourseName].Exams)
		{
			degre.first += i.second.exmamDegree;
			degre.second += i.second.DgreOfExam;
		}
		for (auto& i : this->Courses[CourseName].Assignments)
		{
			degre.first += i.second.assDegree;
			degre.second += i.second.DgreOfAss;
		}
		if (degre.first != 0)
		{
			return float((degre.second / degre.first) * 100.0);
		}
	}
	return 0.0;
}

void Student::Show_Courses()
{
	system("cls");
	for (auto& i : this->Courses)
	{
		cout << "_______________________________________________________________________\n";
		cout << "Course ID : " <<
			i.second.Book <<
			"\nCourse Name : " <<
			i.second.CourseName <<
			"\nBY Dr," << i.second.DoctorName << endl;
		cout << "Your Score -> " <<
			std::fixed << std::setprecision(2) <<
			this->Score_Of(i.second.CourseName) << " % " <<
			((this->Score_Of(i.second.CourseName) > 60) ? "COMPLETED" : "NOT COMPLETED") << endl;
		for (auto& j : i.second.Exams)
		{
			cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
			cout <<"Exam ID : " << j.second.examID << ", Exam Name : " << j.second.examName << "\nExam Degree : " << j.second.exmamDegree << "\n";
			if (j.second.DgreOfExam == 0) { cout << "Your Degree : " << "?" << endl; }
			else { cout << "Your Degree : "  << j.second.DgreOfExam << endl; }
			cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
		}
		cout << "_______________________________________________________________________\n";
	}
	int s;
	cout << "(1)Return\nEnter: ";
	cin >> s;
}

void Student::Register(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants)
{
	system("cls");
	set<pair<string,string>>check;
	for (auto& i : Doctors)
	{
		for (auto& j : i.second.Courses)
		{
			bool ok = 1;
			for (auto& z : j.second.prereqForCors)
			{
				if (this->Score_Of(j.first) < 60)
				{
					ok = 0;
					break;
				}
			}
			if (ok&&j.second.RegStudent.find(this->get_Id()) == j.second.RegStudent.end())
			{
				check.insert({ j.first,i.second.get_Id() });
				cout << "___________________________________________\n";
				cout << "Course Name : " <<
					j.first << endl << "Course ID : " << j.second.ID << endl
					<< "By Dr: " <<
					i.second.get_Name() << endl << "ID : " << i.second.get_Id() << endl;
				cout << "___________________________________________\n";
			}
		}
	}
	cout << "___________________________________________\n";
	cout << "(1)Register\n(2)Return\nEnter: ";
	short s;
	cin >> s;
	if (s == 1)
	{
		cout << "Enter Course Name : ";
		string cnm, doc;
		cin >> cnm;
		cout << "Enter Doctor ID : ";
		cin >> doc;
		if (check.find({ cnm,doc }) == check.end())
		{
			system("cls");
			cout << "Invalid ID Try Again !!" << endl;
			Sleep(5000);
			return;
		}
		if (Doctors[doc].Courses[cnm].CHoure + this->Recordedhours > 18)
		{
			cout << "YOUR FREE TIME LESS THAN REQUIRED " << endl;
			Sleep(10000);
			return;
		}
		Doctors[doc].Courses[cnm].RegStudent.insert(this->get_Id());
		Doctors[doc].S_Courses[this->get_Id()].insert(cnm);
		this->Filter(Doctors[doc]);
		this->Filter(Assistants[Doctors[doc].Courses[cnm].AssistID]);
	}
	return;
}



void Student::Write(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
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

void Student::Download()
{
	cout << "Enter Course Name : ";
	string cnm;
	cin >> cnm;
	const string dstp{ "Downloads\\"+this->Courses[cnm].CourseName+" BOOK.txt"};
	const string srcp{ "database\\Books\\" + this->Courses[cnm].Book + ".txt" };
	std::filesystem::copy_file(srcp, dstp);
	cout << "Completed !" << endl;
	cout << "Your Book Path >> " << dstp << endl;
	cout << "(1)Return\nEnter: ";
	short s; cin >> s;
}
void Student::Do_Assignment(unordered_map<string, Assistant>& Assistants)
{
	string cnm;
	cout << "Enter Course Name : ";
	cin >> cnm;
	short c = 1;
	system("cls");
	set<string>check;
	for (auto& i : this->Courses[cnm].Assignments)
	{
		if (i.second.DgreOfAss < (i.second.assDegree / 2))
		{
			check.insert(i.second.assID);
			cout << "(" << c << ") " << "Assignment name : " << i.second.assName << "  , Assignment ID : " << i.second.assID << endl;
			c++;
		}
	}
	cout << "_____________________________________________________\n";
	cout << "(1)Ready\n(2)Return\nEnter: ";
	short s;
	cin >> s;
	if (s == 2) { return; }
	cout << "Enter Assignment ID To Start : ";
	string asid;
	cin >> asid;
	if (check.find(asid) == check.end())
	{
		system("cls");
		cout << "Invalid ID Try Again !!" << endl;
		Sleep(5000);
		return;
	}
	//Exam Now
	system("cls");
	const string path{ "database\\Assignments\\" + asid + ".txt" };
	fstream src;
	src.open(path, ios::in);
	if (src.is_open()) {

		string tmp;
		int score = 0;
		char ans;
		while (getline(src, tmp))
		{
			while (!tmp.empty() && tmp.front() == ' ')
			{
				tmp.erase(0, 1);
			}
			if (tmp.find('*') != string::npos)
			{
				ans = tmp[0];
				tmp.pop_back();
			}
			if (tmp.find('{') != string::npos)
			{
				system("cls");
				continue;
			}
			else if (tmp.find('}') != string::npos)
			{
				char t;
				cin >> t;
				if (t == ans) { score++; }
				continue;
			}
			cout << tmp << endl;
		}
		string status = (score >= (Assistants[this->Courses[cnm].AssistID].Assigment[asid].AssignmentDegree / 2) ? "Passed" : "Failed");
		cout << "<<< Your Score >> " << score << " <<>> " << status << " <<>>>" << endl;
		Assistants[this->Courses[cnm].AssistID].Assigment[asid].degrees[this->get_Id()] = Degree(this->get_Id(), this->get_Name(), score, status);
		//filter data
		this->Courses[cnm].Assignments[Assistants[this->Courses[cnm].AssistID].Assigment[asid].AssignmentName].assDegree = score;
		Sleep(2000);
		src.close();
	}
	else {
		cout << "#ferror" << endl;
	}
}
void Student::Exam_Now(unordered_map<string, Doctor>& Doctors)
{
	string cnm;
	set<string>check;
	cout << "Enter Course Name : ";
	cin >> cnm;
	auto &doc = Doctors[this->Courses[cnm].DoctorID];
	system("cls");
	short c = 1;
	for (auto& i : doc.Courses[cnm].Exams)
	{
		if (i.second.Dgrees[this->get_Id()].degree <= (i.second.exmamDegree / 2))
		{
			check.insert(i.second.examName);
			cout << "(" << c << ")" << "Exam Name : " <<
				i.second.examName <<
				" ,Exam ID : " <<
				i.second.examID;
			cout << endl;
			c++;
		}
	}
	cout << "_____________________________________________________\n";
	cout << "(1)Ready\n(2)Return\nEnter: ";
	short s;
	cin >> s;
	if (s == 2) { return; }
	cout << "Enter Exam Name To Start : ";
	string exnam; 
	cin >> exnam;
	if (check.find(exnam) == check.end())
	{
		system("cls");
		cout << "Invalid ID Try Again !!" << endl;
		Sleep(5000);
		return;
	}
	system("cls");

	//ExNow
	const string path{ "database\\Exams\\" + doc.Courses[cnm].Exams[exnam].examID + ".txt"};
	fstream src;
	src.open(path, ios::in);
	if (src.is_open()) {

		string tmp;
		int score = 0;
		char ans;
		while (getline(src, tmp))
		{
			while (!tmp.empty() && tmp.front() == ' ')
			{
				tmp.erase(0, 1);
			}
			if (tmp.find('*') != string::npos)
			{
				ans = tmp[0];
				tmp.pop_back();
			}
			if (tmp.find('{') != string::npos)
			{
				system("cls");
				continue;
			}
			else if (tmp.find('}') != string::npos)
			{
				char t;
				cin >> t;
				if (t == ans) { score++; }
				continue;
			}
			cout << tmp << endl;
		}
		string status = (score >= (doc.Courses[cnm].Exams[exnam].exmamDegree / 2) ? "Passed" : "Failed");
		cout << "<<< Your Score >> " << score << " <<>> " << status << " <<>>>" << endl;
		doc.Courses[cnm].Exams[exnam].Dgrees[this->get_Id()]= Degree(this->get_Id(), this->get_Name(), score, status);	
		// Student id => {Course Name ,Exam Name}
		doc.S_Degree[this->get_Id()].insert({ cnm,exnam });
		//filter data
		this->Courses[cnm].Exams[exnam].DgreOfExam = score;
		Sleep(2000);
		src.close();
	}
	else {
		cout << "#ferror" << endl;
	}
}

void Student::m_Course(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
{
	system("cls");
	cout << "(1)Show Courses\n(2)Exam Now\n(3)Do Assignment\n(4)Download B00K\n(5)Return\n\nEnter: ";
	short s;
	cin >> s;
	switch (s)
	{
	case 1:
		Show_Courses();
		break;
	case 2:
		Exam_Now(Doctors);
		Write(Doctors, Assistants, Students);
		break;
	case 3:
		Do_Assignment(Assistants);
		Write(Doctors, Assistants, Students);
		break;
	case 4:
		Download();
		break;
	default:
		return;
	}
}

void Student::Interface(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
{
	system("cls");
	cout << "Welcome " << this->get_Name() << endl;
	cout << " (1)Courses\n (2)Messages\n (3)Register\n (4)Logout\nEnter: ";
	Info_save(1);
	short s;
	cin >> s;
	switch (s)
	{
	case 1:
		m_Course(Doctors, Assistants, Students);
		break;
	case 2:
		Show_M(this->get_Id(), this->get_Name());
		break;
	case 3:
		Register(Doctors, Assistants);
		Write(Doctors, Assistants, Students);
		break;
	default:
		Info_save(0);
		return;
	}
	Interface(Doctors, Assistants, Students);
}



