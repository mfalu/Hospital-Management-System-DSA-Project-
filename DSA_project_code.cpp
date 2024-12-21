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
// ========== Sorting Algorithms ==========
void bubbleSort(vector<Patient*>& patients) {
    for (size_t i = 0; i < patients.size() - 1; ++i) {
        for (size_t j = 0; j < patients.size() - i - 1; ++j) {
            if (patients[j]->id > patients[j + 1]->id) {
                swap(patients[j], patients[j + 1]);
            }
        }
    }
}

void selectionSort(vector<Patient*>& patients) {
    for (size_t i = 0; i < patients.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < patients.size(); ++j) {
            if (patients[j]->id < patients[minIndex]->id) {
                minIndex = j;
            }
        }
        swap(patients[i], patients[minIndex]);
    }
}

void merge(vector<Patient*>& patients, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Patient*> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++) leftArr[i] = patients[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = patients[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i]->id <= rightArr[j]->id) {
            patients[k++] = leftArr[i++];
        } else {
            patients[k++] = rightArr[j++];
        }
    }
    while (i < n1) patients[k++] = leftArr[i++];
    while (j < n2) patients[k++] = rightArr[j++];
}

void mergeSort(vector<Patient*>& patients, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(patients, left, mid);
        mergeSort(patients, mid + 1, right);
        merge(patients, left, mid, right);
    }
}

int partition(vector<Patient*>& patients, int low, int high) {
    int pivot = patients[high]->id;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (patients[j]->id < pivot) {
            i++;
            swap(patients[i], patients[j]);
        }
    }
    swap(patients[i + 1], patients[high]);
    return i + 1;
}

void quickSort(vector<Patient*>& patients, int low, int high) {
    if (low < high) {
        int pi = partition(patients, low, high);
        quickSort(patients, low, pi - 1);
        quickSort(patients, pi + 1, high);
    }
}
// ========== Hash Map for Fast Patient Lookup ==========
class PatientHashMap {
private:
    unordered_map<int, Patient*> patientMap;

public:
    void addPatient(int id, string name, int age, string disease) {
        Patient* newPatient = new Patient(id, name, age, disease);
        patientMap[id] = newPatient;
        cout << "Patient " << name << " added to hash map!" << endl;
    }

    Patient* getPatient(int id) {
        if (patientMap.find(id) != patientMap.end()) {
            return patientMap[id];
        }
        cout << "Patient with ID " << id << " not found!" << endl;
        return nullptr;
    }
};
int main()
{
    
}