#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
 
using namespace std;
 
int main() {
    int student_count, date_count;  
    //инициализация потока для парсинга входного файла
    ifstream data_input("Input.txt");
    //выброс исключения на случай если прочитать входной файл не удалось
    if (!data_input.is_open()) {
        cerr << "Error with input file!" << endl;
        return 1;
    }
 
    // чтение кол-ва студентов
    data_input >> student_count;
    string* names_students = new string[student_count];
 
    // чтение имен студентов
    for (int i = 0; i < student_count; ++i) {
        data_input >> names_students[i];
    }
 
    // чтение кол-ва дат
    data_input >> date_count;
    string* dates_list = new string[date_count];
 
    // чтение дат
    for (int i = 0; i < date_count; ++i) {
        data_input >> dates_list[i];
    }
 
    // чтение студентов с оценками
    int** marks_data = new int* [student_count];
    for (int i = 0; i < student_count; ++i) {
        marks_data[i] = new int[date_count];
        for (int j = 0; j < date_count; ++j) {
            data_input >> marks_data[i][j];
        }
    }
    data_input.close();
 
    // расчет посещаемости студентов и процента посещаемости
    int* attendance_students = new int[student_count];
    float* percentage_attendance_students = new float[student_count];
    for (int i = 0; i < student_count; ++i) {
        attendance_students[i] = 0;
        for (int j = 0; j < date_count; ++j) {
            attendance_students[i] += marks_data[i][j];
        }
        percentage_attendance_students[i] = (attendance_students[i] / float(date_count)) * 100;
    }
 
    // расчет количества студентов, присутствующих на каждую дату, и процента посещаемости на каждую дату.
    int* attendance_dates = new int[date_count];
    float* percentage_attendance_dates = new float[date_count];
    for (int j = 0; j < date_count; ++j) {
        attendance_dates[j] = 0;
        for (int i = 0; i < student_count; ++i) {
            attendance_dates[j] += marks_data[i][j];
        }
        percentage_attendance_dates[j] = (attendance_dates[j] / float(student_count)) * 100;
    }
 
    // инициализация и запись результата в файл
    ofstream output_data("Output.txt");
    if (!output_data.is_open()) {
        cerr << "Error output!" << endl;
        return 1;
    }
 
    // запись посещаемости студентов

    for (int i = 0; i < student_count; ++i) {
        output_data << attendance_students[i] << " ";
    }
    output_data << endl;
 
    // описание процента посещаемости студентов

    for (int i = 0; i < student_count; ++i) {
        output_data << fixed << setprecision(2) << percentage_attendance_students[i] << " ";
    }
    output_data << endl;
 
    // запись количества студентов, присутствующих на каждой дате.

    for (int j = 0; j < date_count; ++j) {
        output_data << attendance_dates[j] << " ";
    }
    output_data << endl;
 
    // запись процента посещаемости на каждую дату
    for (int j = 0; j < date_count; ++j) {
        output_data << fixed << setprecision(2) << percentage_attendance_dates[j] << " ";
    }
    output_data << endl;
 
    output_data.close();
 // освобождение памяти 
    delete[] names_students;
    delete[] dates_list;
    delete[] attendance_students;
    delete[] percentage_attendance_students;
    delete[] attendance_dates;
    delete[] percentage_attendance_dates;
 
    for (int i = 0; i < student_count; ++i) {
        delete[] marks_data[i];
    }
    delete[] marks_data;
 
    return 0;
}
