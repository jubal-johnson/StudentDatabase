#include "Student.h"

// ================== DISPLAY ==================
void displayStudents(Student students[], int count)
{
    cout << "\nID\tLName\t\tFName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << "A" << j + 1 << "\t";

    cout << "AVG\tC1\tC2\tC3\n";

    for (int i = 0; i < count; i++)
    {
        cout << students[i].id << "\t"
            << students[i].lastName << "      \t"
            << students[i].firstName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << students[i].assignments[j] << "\t";

        cout << students[i].average << "\t";

        for (int j = 0; j < NUM_COURSES; j++)
            cout << students[i].courses[j] << "\t";

        cout << endl;
    }
}

// ================= Load Students =================
void loadStudents(Student students[], int& count)
{
    ifstream inputFile("Students90.txt");

    while (count < STUDENT_MAX &&
        inputFile >> students[count].firstName
        >> students[count].lastName
        >> students[count].id)
    {
        for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        {
            inputFile >> students[count].assignments[i];
        }
        
        inputFile >> students[count].average;

        for (int i = 0; i < NUM_COURSES; i++)
        {
            inputFile >> students[count].courses[i];
        }

        count++;
    }

    inputFile.close();
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
    
    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        total += students[count].assignments[i];
    }
    students[count].average = total / NUM_ASSIGNMENTS;

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