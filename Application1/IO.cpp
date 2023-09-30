#include "IO.h"

void Read(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
{
	const string path{ "database\\data.txt" };
	fstream index{ path , ios::in };
	if (index.is_open())
	{
		string tit, id, nam, pas, dat, temp;
		while (getline(index, temp))
		{
			if ((int)temp.find('}') != -1 || (int)temp.find('{') != -1 || (int)temp.find("//") != -1) { continue; }
			stringstream inp{ temp };
			inp >> tit >> id >> nam >> pas >> dat ;
			if (tit == "Doctor") {
				Doctors[id].set_data(tit, id, nam, pas, dat);
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
				Assistants[id].set_data(tit, id, nam, pas, dat);
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
				Students[id].set_data(tit, id, nam, pas, dat);
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
		const string pathInfo{ "database\\info.txt" };
		fstream data{ pathInfo,ios::in };
		if (data.is_open())
		{
			string Id, pass;
			data >> Id >> pass;
			if (!Id.empty() && !pass.empty())
			{
				if (Doctors.find(Id) != Doctors.end() && Doctors[Id].check(Id, pass))
				{
					Doctors[Id].Interface(Doctors, Assistants, Students);
				}
				else if (Assistants.find(Id) != Assistants.end() && Assistants[Id].check(Id, pass))
				{
					Assistants[Id].Interface(Doctors, Assistants, Students);
				}
				else if (Students.find(Id) != Students.end() && Students[Id].check(Id, pass))
				{
					Students[Id].Interface(Doctors, Assistants, Students);
				}
			}
		}
	}
	else {
		cout << "FError\n";
	}
}
void Write(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
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
