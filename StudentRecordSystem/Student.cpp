#include "Student.h"

// ================== DISPLAY ==================
void displayStudents(StudentNode* head)
{
    cout << "\n"
        << setw(8) << "ID"
        << setw(15) << "LName"
        << setw(15) << "FName";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << setw(6) << ("A" + to_string(j + 1));

    cout << setw(8) << "AVG"
        << setw(10) << "C1"
        << setw(10) << "C2"
        << setw(10) << "C3"
        << endl;

    StudentNode* current = head;

    while (current != nullptr)
    {
        cout << setw(8) << current->data.id
            << setw(15) << current->data.lastName
            << setw(15) << current->data.firstName;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << setw(6) << current->data.assignments[j];

        cout << setw(8) << current->data.average;

        for (int j = 0; j < NUM_COURSES; j++)
            cout << setw(10) << current->data.courses[j];

        cout << endl;

        current = current->next; // move to next node
    }
}
// ================= Load Students =================
void loadStudents(StudentNode*& head)
{
    ifstream file("Students90.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    // We no longer need a tail pointer tracking block here
    Student tempStudent;

    while (file >> tempStudent.firstName
        >> tempStudent.lastName
        >> tempStudent.id)
    {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            file >> tempStudent.assignments[j];

        file >> tempStudent.average;

        for (int j = 0; j < NUM_COURSES; j++)
            file >> tempStudent.courses[j];

        // 1. Allocate a brand new node on the heap
        StudentNode* newNode = new StudentNode();
        newNode->data = tempStudent;

        // 2. Point the new node's next to whatever the current head is pointing to
        newNode->next = head;

        // 3. Move the head pointer to point to our newly created node
        head = newNode;
    }

    file.close();
}

// ================= Search by Course =================
void searchByCourse(StudentNode* head)
{
    string course;
    bool found = false;

    cout << "Enter the course: ";
    cin >> course;
    cout << endl;

    StudentNode* current = head;
    while(current!=nullptr)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (current->data.courses[j] == course)
            {
                cout << current->data.id << "\t"
                    << current->data.firstName << "\t"
                    << current->data.lastName << endl;
                found = true;
            }
        }
        current = current->next;
    }
    
    if (!found)
    {
        cout << "\nNo students enrolled in this program.\n";
    }
}

// ================= Show Assignment Average =================
void showAssignmentAverage(StudentNode* head)
{
    int numberOfStudents = 0;
    double total[NUM_ASSIGNMENTS] = { 0 };

    StudentNode* current = head;
    while(current != nullptr)
    {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            total[j] += current->data.assignments[j];
        }
        numberOfStudents++;
        current = current->next;
    }

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "A" << i + 1 << ": " << total[i] / numberOfStudents << endl;
    }
}

// ================= Show Hardest Assignment =================
void showHardestAssignment(StudentNode* head)
{
    double total[NUM_ASSIGNMENTS] = { 0 };
    int numberOfStudents = 0;

    StudentNode* current = head;
    while (current != nullptr)
    {
        for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        {
            total[i] += current->data.assignments[i];
        }
        numberOfStudents++;
        current = current->next;
    }

    int assignment = 1;
    double lowest = total[0] / numberOfStudents;

    for (int i = 1; i < NUM_ASSIGNMENTS; i++)
    {
        double currentAvg = total[i] / numberOfStudents;
        if (currentAvg < lowest)
        {
            lowest = currentAvg;
            assignment = i + 1;
        }
    }
    cout << "Hardest: A" << assignment << " (" << fixed << setprecision(2) << lowest << ")\n\n";
}

// ================= Course Enrollment =================
void courseEnrollment(StudentNode* head)
{
    int courseCount[10] = { 0 };

    StudentNode* current = head;
    while(current != nullptr)
    {
        for (int j = 0; j < NUM_COURSES ; j++)
        {
            if (current->data.courses[j] == "COMP220")
            {
                courseCount[0]++;
            }
            else if (current->data.courses[j] == "MATH102")
            {
                courseCount[1]++;
            }
            else if (current->data.courses[j] == "STAT110")
            {
                courseCount[2]++;
            }
            else if (current->data.courses[j] == "ENGL150")
            {
                courseCount[3]++;
            }
            else if (current->data.courses[j] == "HIST210")
            {
                courseCount[4]++;
            }
            else if (current->data.courses[j] == "BIOL120")
            {
                courseCount[5]++;
            }
            else
            {
                courseCount[6]++;
            }
        }
        current = current->next;
    }

    cout << "\nCOMP220: " << courseCount[0]
        << "\nMATH102: " << courseCount[1]
        << "\nSTAT110: " << courseCount[2]
        << "\nENGL150: " << courseCount[3]
        << "\nHIST210: " << courseCount[4]
        << "\nBIOL120: " << courseCount[5]
        << "\nCSCI101: " << courseCount[6] << "\n";

}

void atRiskStudents(StudentNode* head)
{
    StudentNode* current = head;
    while(current!=nullptr)
    {
        if (current->data.average >= 50 && current->data.average < 60)
        {
            for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            {
                if (current->data.assignments[j] < 50)
                {
                    cout << current->data.id << "\t" << current->data.firstName << "\t" << current->data.lastName << endl;
                    j = NUM_ASSIGNMENTS;
                }
            }
        }
        current = current->next;
    }
    cout << endl;
}

// ================= Sort By Average =================
void sortByAverage(StudentNode* head)
{
    for (StudentNode* i = head; i->next!=nullptr; i=i->next)
    {
        for (StudentNode* j = i->next; j!=nullptr; j=j->next)
        {
            if (i->data.average < j->data.average)
            {
                swap(i->data, j->data);
            }
        }
    }
}


// ================= Add Student =================
void addStudent(StudentNode*& head)
{
    StudentNode* neew = new StudentNode();
    cout << "Enter FName LName ID: ";
    cin >> neew->data.firstName >> neew->data.lastName >> neew->data.id;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "Enter A" << i + 1 << " mark: ";
        cin >> neew->data.assignments[i];
    }
    
    calculateAverage(&neew->data);
    /*for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        total += students[count].assignments[i];
    }
    students[count].average = total / NUM_ASSIGNMENTS;*/

    for (int i = 0; i < NUM_COURSES; i++)
    {
        cout << "Enter Course" << i + 1 << ": ";
        cin >> neew->data.courses[i];
    }
    neew->next = head;
    head = neew;
}

// ================= Save Student =================
void saveStudents(StudentNode* head)
{
        ofstream outFile("students90.txt");

        StudentNode* current = head;
        while(current!=nullptr)
        {
            outFile << current->data.firstName << " "
                << current->data.lastName << " "
                << current->data.id << " "
                << current->data.assignments[0] << " "
                << current->data.assignments[1] << " "
                << current->data.assignments[2] << " "
                << current->data.assignments[3] << " "
                << current->data.assignments[4] << " "
                << current->data.average << " "
                << current->data.courses[0] << " "
                << current->data.courses[1] << " "
                << current->data.courses[2] << " \n";
            current=current->next;
        }

        outFile.close();

        cout << "\nData saved to file!\n";
}

// ================= Average of a student using pointer =================
void calculateAverage(Student* s)
{
    double total = 0;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        total += s->assignments[i];
    }

    s->average = total / NUM_ASSIGNMENTS;

}

// ================= Calculate All Average =================
void calculateAllAverages(StudentNode* head)
{
    StudentNode* current = head;
    while (current != nullptr)
    {
        calculateAverage(&current->data);
        current = current->next;
    }
}


// ================= Delete List =================
void deleteList(StudentNode*& head)
{
    StudentNode* current = head;
    while (current != nullptr)
    {
        StudentNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}