#include "Classes.h"
#include "IO.h"
void Interface(unordered_map<string, Doctor>& Doctors, unordered_map<string, Assistant>& Assistants, unordered_map<string, Student>& Students)
{
	int choice = 1;
	while (choice != 3) {
		system("cls");
		string view = "Welcome please Enter number [1-4] \n\n (1)SignIn\n (2)SignUp\n (3)Exit\n\nEnter: ";
		for (auto& i : view)
		{
			cout << i << flush;
			Sleep(10);
		}
		cin >> choice;
		if (choice == 1)
		{
		l:system("cls");
			view = "ID       : ";
			for (auto& i : view)
			{
				cout << i << flush;
				Sleep(10);
			}
			string Id,pass;
			cin >> Id;
			view = "Password : ";
			for (auto& i : view)
			{
				cout << i << flush;
				Sleep(10);
			}
			cin >> pass;
			if (Doctors.find(Id) != Doctors.end()&&Doctors[Id].check(Id,pass))
			{
				Doctors[Id].Interface(Doctors, Assistants, Students);
			}
			else if (Assistants.find(Id) != Assistants.end()&&Assistants[Id].check(Id, pass))
			{
				Assistants[Id].Interface(Doctors, Assistants, Students);
			}
			else if (Students.find(Id) != Students.end()&&Students[Id].check(Id, pass))
			{
				Students[Id].Interface(Doctors, Assistants, Students);
			}
			else {
				system("cls");
				view = "Invalid Data !!\n(1)Try Again\n(2)Return\nEnter: ";
				for (auto& i : view)
				{
					cout << i << flush;
					Sleep(10);
				}
				cin >> choice;
				if (choice == 2) { return; }
				goto l;
			}
		}
		else if (choice == 2)
		{
			string title,name,password,id;
			system("cls");
			view = "(1)Doctor\n(2)Assistant\n(3)Student\n(4)Return\nEnter: ";
			for (auto& i : view)
			{
				cout << i << flush;
				Sleep(4);
			}
			cin >> choice;
			switch (choice)
			{
			case 1:
				title = "Doctor";
				break;
			case 2:
				title = "Assistant";
				break;
			case 3:
				title = "Student";
				break;
			default:
				Interface(Doctors, Assistants, Students);
				break;
			}
			cout << "Enter Name     : ";
			cin >> name;
			cout << "Enter Password : ";
			cin >> password;
			id = to_string(10000 + rand() % 20001);
			cout << "YOUR ID IS >> " << id << " <<\n";
			cout << "YOU WILL NEED IT IN SIGN IN !!\n";
			if (title == "Doctor") { 
				Doctors[id] = Doctor(title, name, password, id);
			}
			else if(title == "Assistant"){ Assistants[id] = Assistant(title, name, password, id); }
			else { Students[id] = Student(title, name, password, id); }
			cout << "Welcome , " << title << " : " << name << endl;
			Sleep(9000);
			Write(Doctors, Assistants, Students);
			Interface(Doctors, Assistants, Students);
		}

	}
	HWND window;
	AllocConsole();
	window = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(window, 0);
}

int main()
{
	//system("pause");
	srand((unsigned)time(NULL));
	unordered_map<string, Doctor>Doctors;
	unordered_map<string, Assistant>Assistants;
	unordered_map<string, Student>Students;
	Read(Doctors, Assistants, Students);
	Interface(Doctors, Assistants, Students);
	Write(Doctors, Assistants, Students);
}
