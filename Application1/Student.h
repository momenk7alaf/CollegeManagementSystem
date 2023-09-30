#pragma once
#include "main.h"
#include "Messages.h"
#include "User.h"
#include "Doctor.h"
#include "Assistant.h"
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
		ReCourse(string CourseName, string Book, string DoctorID, string DoctorName, string AssistName, string AssistID, short Chour) :
			CourseName(CourseName), Book(Book), DoctorID(DoctorID), DoctorName(DoctorName), AssistName(AssistName), AssistID(AssistID), Chour(Chour) {}
		ReCourse() { Chour = 0; }
		unordered_map<string, Exam>Exams;
		unordered_map<string, Assignment>Assignments;
	};
	short Recordedhours = 0;
	//Course Name => Course Object
	unordered_map<string, ReCourse>Courses;
public:
	Student(string title, string name, string password, string id);
	Student();
	void Write(const string path, bool& mode);
	void Filter(Doctor doctor);
	void Filter(Assistant assistant);
	void Interface(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students);
private:
	void Download();
	float Score_Of(string CourseName);
	void Show_Courses();
	void Info_save(bool mode);
	void Exam_Now(unordered_map<string, Doctor>& Doctors);
	void Do_Assignment(unordered_map<string, Assistant>& Assistants);
	void Register(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants);
	void Write(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students);
	void m_Course(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students);
};