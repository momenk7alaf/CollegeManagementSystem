#pragma once
#include "main.h"
#include "User.h"
#include "Messages.h"
class Student;
class Doctor;
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
	//Course Name => Assignments-ID's
	unordered_map<string, set<string>>Assignments_;
	friend class Student;
public:
	Assistant(string title, string name, string password, string id);
	Assistant();
	void set_Assignments(stringstream& in);
	void set_degrees(stringstream& in);
	void get_Data();
	void Show_Assignments();
	void Info_save(bool mode);
	void Write(const string path, bool& mode);
	void Delete_Assignment();
	void Add_Assignment();
	void Interface(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students);
private:
	void Show_Grades();
	void Manage();
	void Write(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students);
};