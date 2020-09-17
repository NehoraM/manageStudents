#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 *@file manageStudents.c
 * @author nehora moshe
 * @brief system to manage students at HUJI
 *
 */
#define MAX_NAME_LENGTH 42
#define MAX_COUNTRY_LENGTH 42
#define MAX_CITY_LENGTH 42
#define  MAX_LINE_LENGTH 61
#define MAX_INDEX 6
#define MAX_STUDENTS 5500

const int TRUE = 1;
const int FALSE = 0;

const char *EXIT = "q";
const char *EXIT2 = "q\n";

const int ID_INDEX = 0;
const int NAME_INDEX = 1;
const int GRADE_INDEX = 2;
const int AGE_INDEX = 3;
const int COUNTRY_INDEX = 4;
const int CITY_INDEX = 5;


const int MIN_GRADE = 0;
const int MAX_GRADE = 100;
const long MIN_ID = 1000000000;
const long MAX_ID = 9999999999;
const int MIN_AGE = 18;
const int MAX_AGE = 120;

/**
 * Student constructor
 */
typedef struct Student
{
    long ID;
    char name[MAX_NAME_LENGTH];
    int grade;
    int age;
    char country[MAX_COUNTRY_LENGTH];
    char city[MAX_CITY_LENGTH];
} Student;

/**
 *print student information
 * @param student the student to print
 */
void printStudent(Student student);

/**
 *check if some char is letter
 * @param c the char to check is its letter
 * @return 1 if c is letter, 0 otherwise
 */
int isLetter(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return TRUE;
    }
    return FALSE;
}

/**
 *check if some char is white space
 * @param c the char to check
 * @return 1 if c is white space, 0 otherwise
 */
int isWhiteSpace(char c)
{
    if (c == ' ')
    {
        return TRUE;
    }
    return FALSE;
}

/**
 *check if some char is hyphen
 * @param c the char to check
 * @return 1 if c is hyphen, 0 otherwise
 */
int isHyphen(char c)
{
    if (c == '-')
    {
        return TRUE;
    }
    return FALSE;
}


/**
 *check if the ID legal
 * @param id the id to check
 * @param lineNum the line of the id
 * @return 1 if the id legal, 0 otherwise
 */
int idHandler(char *ID, int lineNum)
{

    long id = strtol(ID, &ID, 10);
    if (id >= MIN_ID && id <= MAX_ID)
    {
        return TRUE;
    }
    else
    {
        printf("ERROR: id must be a 10 digits number that does not start with 0\n");
        printf("in line %d\n", lineNum);
        return FALSE;
    }
}


/**
 *check if the name legal
 * @param name the name to check
 * @param lineNum the line of the name
 * @return 1 if the name legal, 0 otherwise
 */
int nameHandler(char *name, int lineNum)
{

    for (int i = 0; i < (int) strlen(name); i++)
    {
        char c = name[i];
        if (isLetter(c) || isWhiteSpace(c) || isHyphen(c))
        {
            continue;
        }
        else
        {
            printf("ERROR: name can only contain alphabetic characters, whitespaces or '-'\n");
            printf("in line %d\n", lineNum);
            return FALSE;
        }
    }
    return TRUE;
}

/**
 *check if the grade legal
 * @param grade the grade to check
 * @param lineNum the line of the grade
 * @return 1 if the grade legal, 0 otherwise
 */
int gradeHandler(const char *grade, int lineNum)
{

    if (strlen(grade) > 3)
    {
        printf("ERROR: grade must be an integer between 0 and 100\n");
        printf("in line %d\n", lineNum);
        return FALSE;
    }
    for (int i = 0; i < (int) strlen(grade); i++)
    {
        char c = grade[i];
        if (isdigit(c))
        {
            continue;
        }
        else
        {
            printf("ERROR: grade must be an integer between 0 and 100\n");
            printf("in line %d\n", lineNum);
            return FALSE;
        }
    }
    int temp = (int) strtol(grade, NULL, 10);
    if ((temp >= MIN_GRADE) && (temp <= MAX_GRADE))
    {
        return TRUE;
    }
    else
    {
        printf("ERROR: grade must be an integer between 0 and 100\n");
        printf("in line %d\n", lineNum);
        return FALSE;
    }
}

/**
 *check if the age legal
 * @param age the age to check
 * @param lineNum the line of the age
 * @return 1 if the age legal, 0 otherwise
 */
int ageHandler(const char *age, int lineNum)
{
    int g;
    sscanf(age, "%d", &g);
    if (g >= MIN_AGE && g <= MAX_AGE)
    {
        return TRUE;
    }
    else
    {
        printf("ERROR: age must be an integer between 18 and 120\n");
        printf("in line %d\n", lineNum);
        return FALSE;
    }
}

/**
 *check if the country legal
 * @param country the country to check
 * @param lineNum the line of the city
 * @return 1 if the country legal, 0 otherwise
 */
int countryHandler(char *country, int lineNum)
{

    for (int i = 0; i < (int) strlen(country); i++)
    {
        char c = country[i];
        if (isLetter(c) || isHyphen(c))
        {
            continue;
        }
        else
        {
            printf("ERROR: country can only contain alphabetic characters or '-' \n");
            printf("in line %d\n", lineNum);
            return FALSE;
        }
    }
    return TRUE;
}

/**
 *check if the city legal
 * @param city the city to check
 * @param lineNum the line of the city
 * @return 1 if the city legal, 0 otherwise
 */
int cityHandler(char *city, int lineNum)
{
    if (strcmp(city, "\n") == 0)
    {
        printf("ERROR: city can only contain alphabetic characters or '-'\n");
        printf("in line %d\n", lineNum);
        return FALSE;
    }
    for (int i = 0; i < (int) strlen(city) - 1; i++)
    {
        char c = city[i];
        if (isLetter(c) || isHyphen(c))
        {
            continue;
        }
        else
        {
            printf("ERROR: city can only contain alphabetic characters or '-'\n");
            printf("in line %d\n", lineNum);
            return FALSE;
        }
    }
    return TRUE;

}

/**
 *check if the student info is legal
 * @param splitLine the params of the student
 * @param lineNum the line of the student
 * @return 1 if the line legal, 0 otherwise
 */
int isLegalLine(char *splitLine[], int lineNum)
{

    if (idHandler(splitLine[ID_INDEX], lineNum) == FALSE)
    {
        return FALSE;
    }
    if (nameHandler(splitLine[NAME_INDEX], lineNum) == FALSE)
    {
        return FALSE;
    }
    if (gradeHandler(splitLine[GRADE_INDEX], lineNum) == FALSE)
    {
        return FALSE;
    }
    if (ageHandler(splitLine[AGE_INDEX], lineNum) == FALSE)
    {
        return FALSE;
    }
    if (countryHandler(splitLine[COUNTRY_INDEX], lineNum) == FALSE)
    {
        return FALSE;
    }
    if (cityHandler(splitLine[CITY_INDEX], lineNum) == FALSE)
    {
        return FALSE;
    }
    return TRUE;

}

/**
 *read line from the user and return if it legal
 * @param line the line to read
 * @param student the student in the line
 * @param lineNum the number of the line
 * @return 1 if the line legal, 0 otherwise
 */

int readLine(char line[], Student *student, int lineNum)
{

    if (strchr(line, ',') == NULL)
    {
        printf("ERROR: info must match specified format\n");
        printf("in line %d\n", lineNum);

        return FALSE;
    }

    char *splitLine[MAX_INDEX];
    char *field = strtok(line, ",");
    int i = 0;

    while (field != NULL)
    {
        splitLine[i] = field;
        i++;
        field = strtok(NULL, ",");
    }

    if (i > MAX_INDEX || i < MAX_INDEX)
    {
        printf("ERROR: info must match specified format\n");
        printf("in line %d\n", lineNum);
        return FALSE;
    }

    if (!isLegalLine(splitLine, lineNum))
    {
        return FALSE;
    }

    char *nothing;

    strcpy(student->name, splitLine[NAME_INDEX]);
    strcpy(student->country, splitLine[COUNTRY_INDEX]);
    strcpy(student->city, splitLine[CITY_INDEX]);
    student->ID = strtol(splitLine[ID_INDEX], &nothing, 10);
    sscanf(splitLine[AGE_INDEX], "%d", &student->age);
    sscanf(splitLine[GRADE_INDEX], "%d", &student->grade);

    return TRUE;

}

/**
 *gets all the user input and save it
 * @param studentList the list of the students
 * @return the number of students
 */
int userInput(Student studentList[])
{
    int numOfStudents = 0;
    int lineNum = 0;
    char line[MAX_LINE_LENGTH];
    printf("Enter student info. To exit press q, then enter\n");
    fgets(line, MAX_LINE_LENGTH, stdin);
    while ((strcmp(line, EXIT) != 0) && (strcmp(line, EXIT2) != 0))
    {
        Student student;
        Student *pointer = &student;
        int temp = readLine(line, pointer, lineNum);
        if (temp == TRUE)
        {
            studentList[numOfStudents] = student;
            numOfStudents++;
        }
        line[0] = '\0';
        lineNum++;
        printf("Enter student info. To exit press q, then enter\n");
        fgets(line, MAX_LINE_LENGTH, stdin);

    }

    return numOfStudents;
}

/**
 *merge sort helper
 * @param studentsList the array
 * @param left left pointer
 * @param middle middle pointer
 * @param right right pointer
 */
void merge(Student studentsList[], int left, int middle, int right)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int length1 = middle - left + 1;
    int length2 = right - middle;

    Student L[MAX_STUDENTS];
    Student R[MAX_STUDENTS];

    for (i = 0; i < length1; i++)
    {
        L[i] = studentsList[left + i];
    }

    for (j = 0; j < length2; j++)
    {
        R[j] = studentsList[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    while ((i < length1) && (j < length2))
    {

        if (L[i].grade <= R[j].grade)
        {
            studentsList[k] = L[i];
            i++;
        }
        else
        {
            studentsList[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < length1)
    {
        studentsList[k] = L[i];
        i++;
        k++;
    }

    while (j < length2)
    {
        studentsList[k] = R[j];
        j++;
        k++;
    }
}

/**
 *merge sort- merge array of student by grade
 * @param studentList the student array
 * @param l the left pointer
 * @param r the right pointer
 */
void mergeSort(Student studentList[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(studentList, l, m);
        mergeSort(studentList, m + 1, r);

        merge(studentList, l, m, r);
    }
}

/**
 *print student info
 * @param student the student to print
 */
void printStudent(Student student)
{

    printf("%ld,%s,%d,%d,%s,%s", student.ID, student.name, student.grade,
           student.age, student.country, student.city);

}

/**
 *check who the best student and print his info
 * @param studentList the student array
 * @param length the length of the array
 * @return the index of the best student or -1 if the array empty
 */

void bestHandler(Student *studentList, int length)
{

    int bestIndex = -1;
    double bestGrade = -1;
    double currentGrade;

    for (int i = 0; i < length; i++)
    {
        currentGrade = (double) (studentList[i].grade) / (studentList[i].age);
        if (currentGrade > bestGrade)
        {
            bestGrade = currentGrade;
            bestIndex = i;
        }
    }

    printf("best student info is: ");
    printStudent(studentList[bestIndex]);

}

/**
 *quickSort -sort array of students
 * @param studentList the student array to sort
 * @param i the left pointer
 * @param j the right pointer
 */
void quickSort(Student studentList[], int low, int high);

/**
 *
 * @param studentList the students array
 * @param studentNum the number of students
 */
void mergeHandler(Student studentList[], int studentNum)
{

    mergeSort(studentList, 0, studentNum - 1);
    for (int i = 0; i < studentNum; i++)
    {
        printStudent(studentList[i]);
    }
}

/**
 *
 * @param studentList the students list
 * @param studentNum the students num
 */
void quickHandler(Student studentList[], int studentNum)
{
    quickSort(studentList, 0, studentNum - 1);
    for (int i = 0; i < studentNum; i++)
    {
        printStudent(studentList[i]);
    }
}

/**
 *the main function of the program.
 *
 * @param argc the input
 * @param argv the length of the input
 * @return 0 if the program success, 1 if not.
 */
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("USAGE: manageStudents <action>\n");
        return 1;
    }
    if ((strcmp(argv[1], "best") != 0) && (strcmp(argv[1], "merge") != 0) &&
        (strcmp(argv[1], "quick") != 0))
    {
        printf("USAGE: manageStudents <action>\n");
        return 1;
    }

    Student studentList[MAX_STUDENTS];
    int studentNum = userInput(studentList);

    if (studentNum <= 0)
    {
        return 0;
    }

    else if (strcmp(argv[1], "best") == 0)
    {
        bestHandler(studentList, studentNum);
        return 0;
    }

    else if (strcmp(argv[1], "merge") == 0)
    {
        mergeHandler(studentList, studentNum);
        return 0;
    }

    else if (strcmp(argv[1], "quick") == 0)
    {
        quickHandler(studentList, studentNum);
        return 0;
    }

    return 1;
}

/**
 * swap two students
 * @param a the first student to swap
 * @param b the second student to swap
 */
void swap(Student *a, Student *b)
{
    Student t = *a;
    *a = *b;
    *b = t;
}

/**
 *quickSort helper
 * @param arr the array to partition
 * @param low the left pointer
 * @param high the right pointer
 * @return the
 */
int partition(Student arr[], int low, int high)
{
    Student pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (strcmp(arr[j].name, pivot.name) < 0)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/**
 *quickSort -sort array of students
 * @param studentList the student list to sort
 * @param low the left pointer
 * @param high the right pointer
 */
void quickSort(Student studentList[], int low, int high)
{

    if (low < high)
    {

        int middle = partition(studentList, low, high);

        quickSort(studentList, low, middle - 1);
        quickSort(studentList, middle + 1, high);
    }
}


