#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student
 {
private:
    int roll_no;
    string name;
    float marks;

public:
    Student() : roll_no(0), marks(0.0) {}

    void input_details()
     {
        cout << "Enter Roll Number: ";
        cin >> roll_no;
        cout << "Enter Name: ";
        cin>>name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display_details()  
    {
        cout << "Roll Number: " << roll_no <<endl<< "Name: " << name <<endl<< "Marks: " << marks << endl;
    }

    void save_to_file(ofstream &outfile) const
    {
        outfile << roll_no << "\n" << name << "\n" << marks << "\n";
    }

    void load_from_file(ifstream &infile)
     {
        infile >> roll_no;
        infile.ignore();
        getline(infile, name);
        infile >> marks;
    }

    int get_roll_no()  const
    {
        return roll_no;
    }
};

void add_student(const string &filename)
 {
    Student s;
    s.input_details();

    ofstream outfile(filename, ios::app);
    if (!outfile) {
        cout << "Error in opening file!" << endl;
        return;
    }

    s.save_to_file(outfile);
    outfile.close();
    cout << "Data added!" << endl;
}

void display_all_students(const string &filename) 
{
    ifstream infile(filename);
    if (!infile)
     {
        cout << "Error in opening file for reading!" << endl;
        return;
    }

    Student s;
    while (infile>> ws , infile.peek() != EOF)
     {
        s.load_from_file(infile);
        s.display_details();
        cout << "-----------------------\n";
    }
    infile.close();
     }
void search_student(const string &filename)
 {
    int roll_no;
    cout << "Enter Roll Number you want to search: ";
    cin >> roll_no;

    ifstream infile(filename);
    if (!infile) 
    {
        cout << "Error in opening file for reading!" << endl;
        return;
    }

    Student s;
    bool found = false;
    while (infile.peek() != EOF)
     {
        s.load_from_file(infile);
        if (s.get_roll_no() == roll_no)
         {
            cout << "Student Found:\n";
            s.display_details();
            found = true;
            break;
        }
    }
    infile.close();

    if (!found)
     {
        cout << "Student with Roll Number " << roll_no << " has not been registered." << endl;
    }
}

int main() 
{
    string filename = "students.txt";
    int choice;

    do 
    {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                add_student(filename);
                break;
            case 2:
                display_all_students(filename);
                break;
            case 3:
                search_student(filename);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}