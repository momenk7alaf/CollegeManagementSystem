#pragma once
#include "main.h"
#include "Messages.h"
#include "User.h"
#include "Assistant.h"
class Student;
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
	unordered_map<string, set<string>>S_Courses;// Student id => {Courses Name}
	friend class Student;
public:
	Doctor(string title, string name, string password, string id);
	Doctor();
	string set_Courses(stringstream& index);
	void set_Exams(string CourseName, stringstream& index);
	void get_Data();
	void set_pre(stringstream& in);
	void set_exams_degree(stringstream& in);
	void set_Registers(stringstream& in);
	void delete_course();
	void delete_exam();
	void add_course();
	void add_exam();
	void Write(const string path, bool& mode);
	void Interface(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students);
private:
	void Write(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students);
	void Info_save(bool mode);
	void Show_courses();
	void Course_In();
	void Grades();
};