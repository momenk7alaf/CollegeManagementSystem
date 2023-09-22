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
class Student;
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
		set<string>RegStudent;//students ids
		unordered_map<string, Exam>Exams;//ExamName => ExamObj
		set<string>prereqForCors;//prerequisites for course
		Course() { CHoure = 0; }
	};
	unordered_map<string, Course>Courses;//Course Name => Course Object
	unordered_map<string, set<pair<string, string>>>S_Degree;// Student id => {Course Name ,Exam Name}
	unordered_map<string,  set<string>>S_Courses;// Student id => {Courses Name}
public:
	Doctor(string title, string name, string password, string id) :User(title, name, password, id) {}
	Doctor() :User() {}
	//friend  class Student;
	friend void Filter(Doctor doctor, Student &student);
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
		S_Degree[id].insert({ cnm,examname });
	}
	void set_Registers(stringstream &in)
	{
		string coursNm,tmpids;
		in >> coursNm;
		while (in >> tmpids)
		{
			this->Courses[coursNm].RegStudent.insert(tmpids);
			this->S_Courses[tmpids].insert(coursNm);
		}
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
		ReCourse(string CourseName, string Book,string DoctorID,string DoctorName,string AssistName,string AssistID, short Chour):
			CourseName(CourseName), Book(Book), DoctorID(DoctorID), DoctorName(DoctorName), AssistName(AssistName), AssistID(AssistID),Chour(Chour) {}
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
	friend void Filter(Doctor doctor, Student &student);
	void Filter(Assistant assistant)
	{
		
	}
	void get_Data()
	{
		for (auto& i : this->Courses)
		{
			cout << i.first << " " << i.second.DoctorName<<" "<<i.second.AssistName << endl;
			for (auto& j : i.second.Exmas)
			{
				 cout << this->get_Name() << " " << j.examName << " " << j.exmamDegree << " " << j.DgreOfExam << endl;
			}
		}
		cout << "************************************************\n";
	}
};
void Filter(Doctor doctor,Student &student)
{
	for (auto& i : doctor.S_Courses[student.get_Id()])
	{
		student.Courses[i].CourseName = i;
		student.Courses[i].Book = doctor.Courses[i].ID;
		student.Courses[i].DoctorID = doctor.get_Id();
		student.Courses[i].DoctorName = doctor.get_Name();
		student.Courses[i].AssistName = doctor.Courses[i].AssistName;
		student.Courses[i].AssistID = doctor.Courses[i].AssistID;
		student.Courses[i].Chour = doctor.Courses[i].CHoure;
	}
	for (auto& i : doctor.S_Degree[student.get_Id()])//Student id => {Course Name ,Exam Name}
	{
		string examName = i.second;
		string examID = doctor.Courses[i.first].Exams[examName].examID;
		short exmamDegree = doctor.Courses[i.first].Exams[examName].exmamDegree;
		short DgreOfExam = doctor.Courses[i.first].Exams[examName].Dgrees[student.get_Id()].degree;
		student.Courses[i.first].Exmas.insert(Student::Exam(examName, examID, exmamDegree, DgreOfExam));
	}
}
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
				// Get Registered Students
				while (getline(index, input))
				{
					if ((int)input.find("//") != -1 || (int)input.find("#s") != -1) { continue; }
					if ((int)input.find("#e") != -1) { break; }
					stringstream in{ input };
					Doctors[id].set_Registers(in);
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
				Filter(j.second, i.second);
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
	//Doctors["1234"].get_Data();
}
