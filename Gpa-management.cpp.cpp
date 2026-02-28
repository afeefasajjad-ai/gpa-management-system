#include <iostream>
#include <fstream>
using namespace std;

const int Max_Students = 100;
const int Max_Courses = 10;
const int Name_Length = 50;
const int Course_Length = 20;

void Strcpy(char* dest, const char* src)
{
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
}

void Getline(char* buffer, int bufferSize)
{
	char c;
	int i = 0;
	while (i < bufferSize - 1)
	{
		c = getchar();
		if (c == '\n' || c == EOF)
		{
			break;
		}
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

void loadStudentData(char StudentNames[Max_Students][Name_Length], int StudentIds[Max_Students], int NumOfCourses[Max_Students],
	char StudentCourses[Max_Students * Max_Courses][Course_Length], char StudentGrades[Max_Students * Max_Courses], int* NumOfStudents)
{
	const char* filename = "students.txt";
	ifstream file(filename);
	if (!file)
	{
		cout << "Error opening file for reading: " << filename << endl;
		return;
	}

	*NumOfStudents = 0;
	while (file >> StudentNames[*NumOfStudents] >> StudentIds[*NumOfStudents] >> NumOfCourses[*NumOfStudents])
	{
		for (int i = 0; i < NumOfCourses[*NumOfStudents]; i++)
		{
			file >> StudentCourses[*NumOfStudents * Max_Courses + i] >> StudentGrades[*NumOfStudents * Max_Courses + i];
		}
		(*NumOfStudents)++;
	}

	file.close();
}

void saveStudentData(const char* filename, char StudentNames[Max_Students][Name_Length], int StudentIds[Max_Students],
	int NumOfCourses[Max_Students], char StudentCourses[Max_Students * Max_Courses][Course_Length],
	char StudentGrades[Max_Students * Max_Courses], int NumOfStudents)
{
	ofstream file(filename);
	if (!file)
	{
		cout << "Error opening file for writing: " << filename << endl;
		return;
	}

	for (int i = 0; i < NumOfStudents; i++)
	{
		file << StudentNames[i] << " " << StudentIds[i] << " " << NumOfCourses[i];
		for (int j = 0; j < NumOfCourses[i]; j++)
		{
			file << " " << StudentCourses[i * Max_Courses + j] << " " << StudentGrades[i * Max_Courses + j];
		}
		file << endl;
	}
	file.close();
}

void addStudent(char StudentNames[Max_Students][Name_Length], int StudentIds[Max_Students], int NumOfCourses[Max_Students],
	int* NumOfStudents)
{
	char name[Name_Length];
	int id;

	cout << "Enter student name: ";
	cin.ignore();
	Getline(name, Name_Length);

	cout << "Enter student ID: ";
	cin >> id;

	if (*NumOfStudents < Max_Students)
	{
		Strcpy(StudentNames[*NumOfStudents], name);
		StudentIds[*NumOfStudents] = id;
		NumOfCourses[*NumOfStudents] = 0;
		(*NumOfStudents)++;
	}
	else
	{
		cout << "Maximum number of students reached!" << endl;
	}
}

void enterGrades(char StudentNames[Max_Students][Name_Length], int StudentIds[Max_Students], int NumOfCourses[Max_Students],
	char StudentCourses[Max_Students * Max_Courses][Course_Length], char StudentGrades[Max_Students * Max_Courses], int NumOfStudents)
{
	int id;
	cout << "Enter student ID: ";
	cin >> id;

	int studentIndex = -1;
	for (int i = 0; i < NumOfStudents; i++)
	{
		if (StudentIds[i] == id)
		{
			studentIndex = i;
			break;
		}
	}

	if (studentIndex == -1)
	{
		cout << "Student with ID " << id << " not found!" << endl;
		return;
	}

	int numCourses;
	cout << "Enter number of courses: ";
	cin >> numCourses;

	for (int i = 0; i < numCourses && NumOfCourses[studentIndex] < Max_Courses; i++)
	{
		cout << "Enter course name: ";
		cin.ignore();
		Getline(StudentCourses[studentIndex * Max_Courses + NumOfCourses[studentIndex]], Course_Length);

		cout << "Enter grade (A-F): ";
		cin >> StudentGrades[studentIndex * Max_Courses + NumOfCourses[studentIndex]];
		++NumOfCourses[studentIndex];
	}
}

float calculateGPA(char StudentGrades[Max_Students * Max_Courses], int NumOfCourses[Max_Students], int studentIndex)
{
	float totalPoints = 0.0;
	for (int i = 0; i < NumOfCourses[studentIndex]; i++)
	{
		switch (StudentGrades[studentIndex * Max_Courses + i])
		{
		case 'A':
			totalPoints += 4.0;
			break;
		case 'B':
			totalPoints += 3.0;
			break;
		case 'C':
			totalPoints += 2.0;
			break;
		case 'D':
			totalPoints += 1.0;
			break;
		case 'F':
			totalPoints += 0.0;
			break;
		}
	}
	return totalPoints / NumOfCourses[studentIndex];
}

void viewGPA(char StudentNames[Max_Students][Name_Length], int StudentIds[Max_Students], char StudentGrades[Max_Students * Max_Courses],
	int NumOfCourses[Max_Students], int NumOfStudents)
{
	int id;
	cout << "Enter student ID: ";
	cin >> id;

	int studentIndex = -1;
	for (int i = 0; i < NumOfStudents; i++)
	{
		if (StudentIds[i] == id)
		{
			studentIndex = i;
			break;
		}
	}

	if (studentIndex != -1)
	{
		cout << "GPA of " << StudentNames[studentIndex] << " (ID: " << StudentIds[studentIndex] << ") is ";
		cout << calculateGPA(StudentGrades, NumOfCourses, studentIndex) << endl;
	}
	else
	{
		cout << "Student with ID " << id << " not found!" << endl;
	}
}

void showMenu()
{
	cout << "1. Add Students" << endl;
	cout << "2. Enter Grades" << endl;
	cout << "3. Calculate GPA" << endl;
	cout << "4. View GPA" << endl;
	cout << "5. Exit" << endl;
	cout << "Choose an option: ";
}

int main()
{
	char StudentNames[Max_Students][Name_Length];
	int StudentIds[Max_Students];
	int NumOfCourses[Max_Students];
	char StudentCourses[Max_Students * Max_Courses][Course_Length];
	char StudentGrades[Max_Students * Max_Courses];
	int NumOfStudents = 0;

	loadStudentData(StudentNames, StudentIds, NumOfCourses, StudentCourses, StudentGrades, &NumOfStudents);

	int choice;
	while (true)
	{
		showMenu();
		cin >> choice;

		switch (choice)
		{
		case 1:
			addStudent(StudentNames, StudentIds, NumOfCourses, &NumOfStudents);
			break;
		case 2:
			enterGrades(StudentNames, StudentIds, NumOfCourses, StudentCourses, StudentGrades, NumOfStudents);
			break;
		case 3:
			// Calculate GPA does nothing directly in the menu, it's calculated when viewing GPA
			cout << "To calculate GPA, please view GPA for a student." << endl;
			break;
		case 4:
			viewGPA(StudentNames, StudentIds, StudentGrades, NumOfCourses, NumOfStudents);
			break;
		case 5:
			saveStudentData("students.txt", StudentNames, StudentIds, NumOfCourses, StudentCourses, StudentGrades, NumOfStudents);
			cout << "Exiting the program." << endl;
			system("pause");
			return 0;
		default:
			cout << "Invalid choice! Please choose again." << endl;
		}
	}

	system("pause");
	return 0;
}
