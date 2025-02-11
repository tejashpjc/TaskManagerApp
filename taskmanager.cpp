#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Task {
    int id;
    string description;
    string priority;
    bool completed;
};

vector<Task> tasks;
string filename = "tasks.csv";

void loadTasks() {
    tasks.clear();
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Task task;
        string completedStr;
        getline(ss, line, ','); task.id = stoi(line);
        getline(ss, task.description, ',');
        getline(ss, task.priority, ',');
        getline(ss, completedStr, ','); task.completed = (completedStr == "1");
        tasks.push_back(task);
    }
    file.close();
}

void saveTasks() {
    ofstream file(filename);
    for (const auto& task : tasks) {
        file << task.id << "," << task.description << "," << task.priority << "," << task.completed << "\n";
    }
    file.close();
}

void addTask() {
    Task task;
    task.id = tasks.empty() ? 1 : tasks.back().id + 1;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, task.description);
    cout << "Enter priority (Low/Medium/High): ";
    cin >> task.priority;
    task.completed = false;
    tasks.push_back(task);
    saveTasks();
    cout << "Task added successfully!\n";
}

void viewTasks() {
    cout << "\nTasks:\n";
    for (const auto& task : tasks) {
        cout << "ID: " << task.id << " | "
             << (task.completed ? "[Completed] " : "[Pending] ")
             << task.description << " (" << task.priority << ")\n";
    }
}

void completeTask() {
    int id;
    cout << "Enter task ID to mark as complete: ";
    cin >> id;
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            saveTasks();
            cout << "Task marked as completed!\n";
            return;
        }
    }
    cout << "Task not found!\n";
}

void deleteTask() {
    int id;
    cout << "Enter task ID to delete: ";
    cin >> id;
    tasks.erase(remove_if(tasks.begin(), tasks.end(), [id](Task& task) {
        return task.id == id;
    }), tasks.end());
    saveTasks();
    cout << "Task deleted!\n";
}

int main() {
    loadTasks();
    int choice;
    do {
        cout << "\nTask Manager\n1. Add Task\n2. View Tasks\n3. Complete Task\n4. Delete Task\n5. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: completeTask(); break;
            case 4: deleteTask(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    return 0;
}

