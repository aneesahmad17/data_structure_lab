#include <iostream>
#include <string>
using namespace std;

int main()
{
    const int STUDENTS = 6;
    const int SUBJECTS = 4;
    string subjects[SUBJECTS] = {"English", "Math", "Programming", "AI"};

    // 1. Store marks of 6 students in 4 subjects
    int marks[STUDENTS][SUBJECTS] = {
        {78, 85, 90, 88},
        {65, 72, 80, 70},
        {92, 88, 95, 91},
        {55, 60, 68, 62},
        {81, 94, 87, 85},
        {70, 66, 75, 79}
    };

    int total[STUDENTS];
    float average[STUDENTS];

    // 2. Display the complete marks table
    cout << "Student\t";
    for (int j = 0; j < SUBJECTS; j++)
        cout << subjects[j] << "\t";
    cout << endl;

    for (int i = 0; i < STUDENTS; i++)
    {
        cout << "S" << i + 1 << "\t";
        for (int j = 0; j < SUBJECTS; j++)
            cout << marks[i][j] << "\t";
        cout << endl;
    }

    // 3 & 4. Total and average of each student
    cout << "\nTotal and Average of Each Student:" << endl;
    for (int i = 0; i < STUDENTS; i++)
    {
        total[i] = 0;
        for (int j = 0; j < SUBJECTS; j++)
            total[i] += marks[i][j];
        average[i] = (float)total[i] / SUBJECTS;
        cout << "Student " << i + 1 << " -> Total: " << total[i]
             << "\tAverage: " << average[i] << endl;
    }

    // 5. Highest marks in each subject
    cout << "\nHighest Marks in Each Subject:" << endl;
    for (int j = 0; j < SUBJECTS; j++)
    {
        int highest = marks[0][j];
        for (int i = 1; i < STUDENTS; i++)
        {
            if (marks[i][j] > highest)
                highest = marks[i][j];
        }
        cout << subjects[j] << ": " << highest << endl;
    }

    // 6. Student with the highest total marks
    int topStudent = 0;
    for (int i = 1; i < STUDENTS; i++)
    {
        if (total[i] > total[topStudent])
            topStudent = i;
    }
    cout << "\nStudent with Highest Total: Student " << topStudent + 1
         << " (" << total[topStudent] << " marks)" << endl;

    return 0;
}
