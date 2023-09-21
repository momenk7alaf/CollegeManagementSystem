#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<set>
#include<fstream>
#include<sstream>
#include<string>
#include <map>
using namespace std;

class User {
private:
	string title, id, name, password, date, status;
public:
	User() {}
	User(string title, string name, string password, string id) :title(title), name(name), password(password), id(id)
	{
		//date
		string dat = __DATE__ " " __TIME__;
		replace(dat.begin(), dat.end(), ' ', '-');
		this->date = dat;
		//status
		this->status = "1";
	}
	void set_data(string tit, string id, string nam, string pas, string dat, string status)
	{
		this->title = tit;
		this->id = id;
		this->name = nam;
		this->password = pas;
		this->date = dat;
		this->status = status;
	}
	void data()const
	{
		cout << "Name       : " << this->name << endl;
		cout << "ID         : " << this->id << endl;
		cout << "Title      : " << this->title << endl;
		cout << "Date       : " << this->date << endl;
		cout << "password   : " << this->password << endl;
		cout << "________________________________________________________________________________\n\n";
	}
	void set_status()
	{
		cout << "(1)Block\n(2)UnBlocke\nEnter--> ";
		string sted;
		cin >> sted;
		this->status = (sted == "1" ? "0" : "1");
	}
	bool get_status()const
	{
		return (this->status == "1" ? 1 : 0);
	}
	string get_Id() { return id; }
	string get_Name() { return name; }
};

class Degree
{
public:
	string id, name, status;
	short degree;
	Degree() { degree = 0; }
	Degree(string id, string name, short degree, string status)
		:id(id), name(name), degree(degree), status(status) {}
	bool operator<(const Degree& other) const {
		return (this->degree) >= (other.degree);
	}
};

class Doctor :public User {
private:
	class Exam
	{
	public:
		string examName, examID, courseName;
		short exmamDegree;
		unordered_map<string, Degree>Dgrees;
		Exam() { exmamDegree = 0; }
	};
	class Course {
	public:
		string ID;
		short  CHoure;
		string AssistName;
		string AssistID;
		unordered_map<string, Exam>Exams;//ExamName => ExamObj
		set<string>prereqForCors;//prerequisites for course
		Course() { CHoure = 0; }
	};
	unordered_map<string, Course>Courses;//Course Name => Course Object
	unordered_map<string, set<pair<string, string>>>Students;// Student id => {Course Name ,Exam Name}
public:
	Doctor(string title, string name, string password, string id) :User(title, name, password, id) {}
	Doctor() :User() {}
	friend class Student;
	string set_Courses(stringstream& index)
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
	void set_Exams(string CourseName, stringstream& index)
	{
		short ExamDegree;
		string  ExamName, ExamID;
		while (index >> ExamName >> ExamDegree >> ExamID)
		{
			this->Courses[CourseName].Exams[ExamName].examName = ExamName;
			this->Courses[CourseName].Exams[ExamName].exmamDegree = ExamDegree;
			this->Courses[CourseName].Exams[ExamName].examID = ExamID;
		}
	}
	void get_Data()
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
				cout << "----------------------------------------------------\n\n";
			}
		}
	}
	void set_pre(stringstream& in)
	{
		string cnm, tmp;
		in >> cnm;
		while (in >> tmp)
		{
			Courses[cnm].prereqForCors.insert(tmp);
		}
	}
	void set_exams_degree(stringstream& in)
	{
		short degree;
		string name, id, examname, cnm, status;
		in >> name >> id >> cnm >> examname >> degree >> status;
		Courses[cnm].Exams[examname].Dgrees[id] = (Degree(id, name, degree, status));
		Students[id].insert({ cnm,examname });
	}
	void delete_course()
	{
		string coursen;
		cout << "Enter Course Name --> ";
		cin >> coursen;
		Courses.erase(coursen);
	}
	void delete_exam()
	{
		string exnm, coursnm;
		cout << "Enter Course Name  : ";
		cin >> coursnm;
		cout << "Enter Exam Name    : ";
		cin >> exnm;
		Courses[coursnm].Exams.erase(exnm);
	}
	void add_course()
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
		cin.ignore();
		string Id = to_string(10000 + rand() % 20001);
		Courses[cnm].ID = Id;
		Courses[cnm].CHoure = hour;
		getline(cin, book);
		/*
			UPLOAD METHOD HERE !!
		*/
	}
	void add_exam()
	{
		string cnm, expath, exnm;
		cout << "Enter Course Name : ";
		cin >> cnm;
		cout << "Enter Exam Name   :";
		cin >> exnm;
		cout << "Enter The Path Of The Exam `.txt file` To Upload: ";
		cin.ignore();
		getline(cin, expath);
		string Id = to_string(10000 + rand() % 20001);
		Courses[cnm].Exams[exnm].examID = Id;
		/*
			UPLOAD METHOD HERE !!
		*/
	}

};

class Assistant : public User
{
private:
	class Assigments {
	public:
		string AssignmentID, doctoreID, AssignmentName, CourseName;
		short AssignmentDegree;
		Assigments() { AssignmentDegree = 0; }
		unordered_map<string, Degree>degrees;
		bool operator<(const Assigments& other) const {
			return stoi(this->AssignmentName) >= stoi(other.AssignmentName);
		}
	};
	//Assignment-ID =>   {Assignment-Object}
	unordered_map<string, Assigments>Assigment;
	//Student Id => Assignments-ID's
	unordered_map<string, set<string>>Student_;
public:
	Assistant(string title, string name, string password, string id) :User(title, name, password, id) {}
	Assistant() :User() {}
	friend class Student;
	void set_Assignments(stringstream& in)
	{
		string id, course, did, assnm;
		short assimdgr;
		in >> id >> course >> did >> assnm >> assimdgr;
		Assigment[id].AssignmentID = id;
		Assigment[id].CourseName = course;
		Assigment[id].doctoreID = did;
		Assigment[id].AssignmentName = assnm;
		Assigment[id].AssignmentDegree = assimdgr;
	}
	void set_degrees(stringstream& in)
	{
		short degr;
		string assid, course, id, name, stat;
		in >> assid >> course >> name >> id >> degr >> stat;
		Assigment[assid].degrees[id] = (Degree(id, name, degr, stat));
		this->Student_[id].insert(assid);
	}
	void get_Data()
	{
		for (auto& i : Assigment)
		{
			cout << i.second.AssignmentID << " " << i.second.AssignmentName << " " << i.second.AssignmentDegree << " " << i.second.doctoreID << endl;
		}

	}
};

class Student :public User
{
private:
	class Exam {
	public:
		string examName, examID;
		short exmamDegree;
		short DgreOfExam;
		Exam() { exmamDegree = DgreOfExam = 0; }
		Exam(string examName, string examID, short exmamDegree, short DgreOfExam) :
			examName(examName), examID(examID), exmamDegree(exmamDegree), DgreOfExam(DgreOfExam) {}
		bool operator<(const Exam& other) const {
			return this->DgreOfExam < other.DgreOfExam;
		}
	};
	class Assignment {
	public:
		string assName, assID;
		short assDegree;
		short DgreOfAss;
		Assignment(string assName, string assID, short assDegree, short DgreOfAss) :
			assName(assName), assID(assID), assDegree(assDegree), DgreOfAss(DgreOfAss) {}
		Assignment() { assDegree = DgreOfAss = 0; }
		bool operator<(const Assignment& other) const {
			return this->DgreOfAss < other.DgreOfAss;
		}
	};
	class ReCourse {
	public:
		string CourseName, Book, DoctorID, DoctorName, AssistName, AssistID;
		short Chour;
		ReCourse() { Chour = 0; }
		set<Exam>Exmas;
		set<Assignment>Assignments;
	};
	//int Recordedhours;
	//set<string>CompletedCore;
	//Course Name => Course Object
	unordered_map<string, ReCourse>Courses;
public:
	Student(string title, string name, string password, string id) :User(title, name, password, id) {}
	Student() :User() {}
	void Filter(Doctor Doctr)
	{
		for (auto& i : Doctr.Students[this->get_Id()])
		{
			//set couses data
			this->Courses[i.first].CourseName = i.first;
			this->Courses[i.first].Book = Doctr.Courses[i.first].ID;
			this->Courses[i.first].AssistName = Doctr.Courses[i.first].AssistName;
			this->Courses[i.first].AssistID = Doctr.Courses[i.first].AssistID;
			this->Courses[i.first].DoctorName = Doctr.get_Name(); 
			this->Courses[i.first].DoctorID = Doctr.get_Id();
			this->Courses[i.first].Chour = Doctr.Courses[i.first].CHoure;
			//cout << i.first << " " << Doctr.Courses[i.first].ID << " " << Doctr.get_Name() << " " << Doctr.get_Id() << endl;
			//set exams data
			string examName = Doctr.Courses[i.first].Exams[i.second].examName;
			string examID = Doctr.Courses[i.first].Exams[i.second].examID;
			short exmamDegree = Doctr.Courses[i.first].Exams[i.second].exmamDegree;
			short DgreOfExam = Doctr.Courses[i.first].Exams[i.second].Dgrees[this->get_Id()].degree;
			this->Courses[i.first].Exmas.insert(Exam(examName, examID, exmamDegree, DgreOfExam));

		}
	}
	void Filter(Assistant &assist)
	{
		for (auto& i : assist.Student_[this->get_Id()])
		{
			string cours = assist.Assigment[i].CourseName;
			string assName = assist.Assigment[i].AssignmentName;
			string assID = assist.Assigment[i].AssignmentID;
			short assDegree = assist.Assigment[i].AssignmentDegree;
			short DgreOfAss = assist.Assigment[i].degrees[this->get_Id()].degree;
			Courses[cours].Assignments.insert(Assignment(assName, assID, assDegree, DgreOfAss));
		}
	}
	void get_Data()
	{
		this->data();
		for (auto& i : this->Courses)
		{
			cout << i.second.DoctorName << endl;
		}
		cout << "__________________________________________\n";
	}
};
void Read(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
{
	fstream index{ "data.txt" , ios::in };
	if (index.is_open())
	{
		string tit, id, nam, pas, dat, temp, stat;
		while (getline(index, temp))
		{
			if ((int)temp.find('}') != -1 || (int)temp.find('{') != -1 || (int)temp.find("//") != -1) { continue; }
			stringstream inp{ temp };
			inp >> tit >> id >> nam >> pas >> dat >> stat;
			if (tit == "Doctor") {
				Doctors[id].set_data(tit, id, nam, pas, dat, stat);
				string input;
				//Get Courses and its exams
				while (getline(index, input))
				{
					if ((int)temp.find("//") != -1) { continue; }
					if ((int)input.find("#s") != -1) { break; }
					stringstream in{ input };
					string nameofco = Doctors[id].set_Courses(in);
					Doctors[id].set_Exams(nameofco, in);
				}
				//Get prerequisites
				while (getline(index, input))
				{
					if ((int)input.find("//") != -1 || (int)input.find("#s") != -1) { continue; }
					if ((int)input.find("#e") != -1) { break; }
					stringstream in{ input };
					Doctors[id].set_pre(in);
				}
				//Get Students Data
				while (getline(index, input))
				{
					if ((int)input.find("//") != -1 || (int)input.find("#s") != -1 || (int)input.find("#e") != -1) { continue; }
					if ((int)input.find('}') != -1) { break; }
					stringstream in{ input };
					//cout << input << endl;
					Doctors[id].set_exams_degree(in);
				}
			}
			else if (tit == "Assistant")
			{
				Assistants[id].set_data(tit, id, nam, pas, dat, stat);
				string input;
				//Get Assignments
				while (getline(index, input))
				{
					if ((int)temp.find("//") != -1) { continue; }
					if ((int)input.find("#s") != -1) { break; }
					stringstream in{ input };
					Assistants[id].set_Assignments(in);
				}
				while (getline(index, input))
				{
					if ((int)input.find("//") != -1 || (int)input.find("#s") != -1 || (int)input.find("#e") != -1) { continue; }
					if ((int)input.find('}') != -1) { break; }
					stringstream in{ input };
					Assistants[id].set_degrees(in);
				}
			}
			else {
				Students[id].set_data(tit, id, nam, pas, dat, stat);
			}
		}
		index.close();
		//Read data from doctors
		for (auto& i : Students)
		{
			for (auto& j : Doctors)
			{
				i.second.Filter(j.second);
			}
		}
		//Read data from Assistants
		for (auto& i : Students)
		{
			for (auto& j : Assistants)
			{
				i.second.Filter(j.second);
			}
		}
	}
	else {
		cout << "FError\n";
	}
}
int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	unordered_map<string, Doctor>Doctors;
	unordered_map<string, Assistant>Assistants;
	unordered_map<string, Student>Students;
	Read(Doctors, Assistants, Students);
	for (auto& i : Students)
	{
		i.second.get_Data();
	}
	Doctors["1234"].get_Data();
}
