#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Class representing a user
class User {
public:
    string username;
    string password;
    string role;

    User(string u, string p, string r) : username(u), password(p), role(r) {}
};

// Class representing employee personal data
class Employee {
public:
    string name;
    string address;
    double salary;

    Employee(string n, string a, double s) : name(n), address(a), salary(s) {}
};

// Function to load users from a file
vector<User> loadUsersFromFile(string filename) {
    vector<User> users;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string username = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            string password = line.substr(0, pos);
            line.erase(0, pos + 1);
            string role = line;

            users.push_back(User(username, password, role));
        }
    }

    file.close();
    return users;
}

// Function to load employee data from a file
vector<Employee> loadEmployeesFromFile(string filename) {
    vector<Employee> employees;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            string address = line.substr(0, pos);
            line.erase(0, pos + 1);
            double salary = stod(line);

            employees.push_back(Employee(name, address, salary));
        }
    }

    file.close();
    return employees;
}

// Function to save employee data to a file
void saveEmployeesToFile(const vector<Employee> &employees, const string &filename) {
    ofstream file(filename);
    for (const Employee &employee : employees) {
        file << employee.name << "," << employee.address << "," << employee.salary << endl;
    }
    file.close();
}

// Function to display employee data
void displayEmployeeData(const vector<Employee> &employees, const string &role) {
    cout << "Employee personal data:" << endl;
    for (const Employee &employee : employees) {
        if (role == "manager" || role == "employee") {
            cout << "Name: " << employee.name << endl;
            cout << "Address: " << employee.address << endl;
            if (role == "manager") {
                cout << "Salary: " << employee.salary << endl;
            }
            cout << endl;
        }
    }
}

// Function for login
bool login(vector<User> users, string username, string password, string &role) {
    for (User &user : users) {
        if (user.username == username && user.password == password) {
            role = user.role;
            return true;
        }
    }

    cout << "Invalid login credentials" << endl;
    return false;
}

int main() {
    vector<User> users = loadUsersFromFile("users.txt");
    vector<Employee> employees = loadEmployeesFromFile("employees.txt");

    string role;
    while (true) {
        cout << "Enter your username: ";
        string username;
        cin >> username;
        cout << "Enter your password: ";
        string password;
        cin >> password;

        if (login(users, username, password, role)) {
            cout << "Logged in as " << role << endl;

            while (true) {
                displayEmployeeData(employees, role);

                if (role == "manager") {
                    cout << "Do you want to edit employee data? (Y/N): ";
                    char choice;
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        string nameToEdit;
                        cout << "Enter the name of the employee you want to edit: ";
                        cin.ignore();
                        getline(cin, nameToEdit);

                        for (Employee &employee : employees) {
                            if (employee.name == nameToEdit) {
                                cout << "New address: ";
                                getline(cin, employee.address);
                                cout << "New salary: ";
                                cin >> employee.salary;
                                saveEmployeesToFile(employees, "employees.txt");
                                break;
                            }
                        }
                    }
                }

                cout << "Do you want to exit? (Y/N): ";
                char choice;
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    break;
                }
            }
            break;
        }
    }

    return 0;
}
