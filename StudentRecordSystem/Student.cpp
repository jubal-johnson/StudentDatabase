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
void searchByCourse(Student students[], int count)
{
    string course;
    bool found = false;

    cout << "Enter the course: ";
    cin >> course;
    cout << endl;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (students[i].courses[j] == course)
            {
                cout << students[i].id << "\t"
                    << students[i].firstName << "\t"
                    << students[i].lastName << endl;
                found = true;
            }
        }
    }
    
    if (!found)
    {
        cout << "\nNo students enrolled in this program.\n";
    }
}

// ================= Show Assignment Average =================
void showAssignmentAverage(Student students[], int count)
{
    double total[NUM_ASSIGNMENTS] = { 0 };

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        for (int j = 0; j < count; j++)
        {
            total[i] += students[j].assignments[i];
        }
    }

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "A"<<i+1<<": " << total[i] / count << endl;
    }
}

// ================= Show Hardest Assignment =================
void showHardestAssignment(Student students[], int count)
{
    int assignment=1;
    double total[NUM_ASSIGNMENTS] = { 0 }, avg[NUM_ASSIGNMENTS], lowest;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        for (int j = 0; j < count; j++)
        {
            total[i] += students[j].assignments[i];
        }
        avg[i] = total[i] / count;
    }

    lowest = avg[0];
    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
            if (lowest > avg[i])
            {
                lowest = avg[i];
                assignment = i + 1;
            }
    }
    cout << "Hardest: A" << assignment << " (" << lowest << ")\n\n";
}

// ================= Course Enrollment =================
void courseEnrollment(Student students[], int count)
{
    int courseCount[10] = { 0 };

    for(int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_COURSES ; j++)
        {
            if (students[i].courses[j] == "COMP220")
            {
                courseCount[0]++;
            }
            else if (students[i].courses[j] == "MATH102")
            {
                courseCount[1]++;
            }
            else if (students[i].courses[j] == "STAT110")
            {
                courseCount[2]++;
            }
            else if (students[i].courses[j] == "ENGL150")
            {
                courseCount[3]++;
            }
            else if (students[i].courses[j] == "HIST210")
            {
                courseCount[4]++;
            }
            else if (students[i].courses[j] == "BIOL120")
            {
                courseCount[5]++;
            }
            else
            {
                courseCount[6]++;
            }
        }
    }

    cout << "\nCOMP220: " << courseCount[0]
        << "\nMATH102: " << courseCount[1]
        << "\nSTAT110: " << courseCount[2]
        << "\nENGL150: " << courseCount[3]
        << "\nHIST210: " << courseCount[4]
        << "\nBIOL120: " << courseCount[5]
        << "\nCSCI101: " << courseCount[6] << "\n";

}

void atRiskStudents(Student students[], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].average >= 50 && students[i].average < 60)
        {
            for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            {
                if (students[i].assignments[j] < 50)
                {
                    cout << students[i].id << "\t" << students[i].firstName << "\t" << students[i].lastName << endl;
                    j = NUM_ASSIGNMENTS;
                }
            }
        }
    }
    cout << endl;
}

// ================= Sort By Average =================
void sortByAverage(Student students[], int count)
{
    for (int i = 0; i < count-1; i++)
    {
        for (int j = i+1; j < count; j++)
        {
            if (students[i].average < students[j].average)
            {
                swap(students[i], students[j]);
            }
        }
    }
}


// ================= Add Student =================
void addStudent(Student students[], int& count)
{
    double total = 0;
    cout << "Enter FName LName ID: ";
    cin >> students[count].firstName >> students[count].lastName >> students[count].id;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "Enter A" << i + 1 << " mark: ";
        cin >> students[count].assignments[i];
    }
    
    calculateAverage(&students[count]);
    /*for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        total += students[count].assignments[i];
    }
    students[count].average = total / NUM_ASSIGNMENTS;*/

    for (int i = 0; i < NUM_COURSES; i++)
    {
        cout << "Enter Course" << i + 1 << ": ";
        cin >> students[count].courses[i];
    }
    count++;
}

// ================= Save Student =================
void saveStudents(Student students[], int count)
{
        ofstream outFile("students90.txt");

        for (int i = 0; i < count; i++)
        {
            outFile << students[i].firstName << " "
                << students[i].lastName << " "
                << students[i].id << " "
                << students[i].assignments[0] << " "
                << students[i].assignments[1] << " "
                << students[i].assignments[2] << " "
                << students[i].assignments[3] << " "
                << students[i].assignments[4] << " "
                << students[i].average << " "
                << students[i].courses[0] << " "
                << students[i].courses[1] << " "
                << students[i].courses[2] << " \n";
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