#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// ========== Login System ==========
unordered_map<string, string> userDatabase = {{"admin", "password"}};

bool login() {
    string username, password, choice;
    cout << "=== Hospital Management System Login ===" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register New User" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == "1") {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (userDatabase.find(username) != userDatabase.end() && userDatabase[username] == password) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Invalid credentials. Try again." << endl;
            return false;
        }
    } else if (choice == "2") {
        cout << "=== Register New User ===" << endl;
        cout << "Enter new username: ";
        cin >> username;
        if (userDatabase.find(username) != userDatabase.end()) {
            cout << "Error: Username already exists." << endl;
        } else {
            cout << "Enter new password: ";
            cin >> password;
            userDatabase[username] = password;
            cout << "User registered successfully!" << endl;
        }
    } else {
        cout << "Invalid choice. Exiting." << endl;
    }

    return false;
}

// ========== Patient Structure ==========
struct Patient {
    int id;
    string name;
    int age;
    string disease;

    Patient(int id, string name, int age, string disease)
        : id(id), name(name), age(age), disease(disease) {}
};

// ========== Linked List for Patient Management ==========
class PatientList {
private:
    struct Node {
        Patient* data;
        Node* next;
        Node(Patient* patient) : data(patient), next(nullptr) {}
    };

    Node* head;

public:
    PatientList() : head(nullptr) {}

    void addPatient(int id, string name, int age, string disease) {
        Patient* newPatient = new Patient(id, name, age, disease);
        Node* newNode = new Node(newPatient);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "Patient " << name << " added successfully!" << endl;
    }

    vector<Patient*> getPatients() {
        vector<Patient*> patients;
        Node* temp = head;
        while (temp) {
            patients.push_back(temp->data);
            temp = temp->next;
        }
        return patients;
    }

    void displayPatients() {
        Node* temp = head;
        if (!temp) {
            cout << "No patients to display!" << endl;
            return;
        }

        cout << "Patient List:" << endl;
        while (temp) {
            cout << "ID: " << temp->data->id << ", Name: " << temp->data->name
                 << ", Age: " << temp->data->age
                 << ", Disease: " << temp->data->disease << endl;
            temp = temp->next;
        }
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    ~PatientList() { clear(); }
};