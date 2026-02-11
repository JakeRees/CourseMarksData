#include<iostream>
#include<iomanip>
#include<cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::string;
using std::vector;

const string file_name = "course_marks.dat";

struct Course 
{
    string name;
    float mark;
    int id;

    Course(string name, float mark, int id)
    {
        this->name = name;
        this->mark = mark;
        this->id = id;
    }
};

float get_standard_deviation(vector<Course>& data, float mean, int size)
{
    // Takes a vector and returns the standard deviation of the elements
    float standard_deviation = 0.0;

    for (int i = 0; i < size; ++i) {
        standard_deviation += pow(data[i].mark - mean, 2);
    }

    return sqrt(standard_deviation / size);
}

int get_integer_input(string& message) 
{
  // Requests and validates input to ensure strictly positive integer type
  string line;
  int input;

  while (true) 
  {
    cout << "\n" << message;
    getline(cin, line);

    std::istringstream converter(line);
    if (converter >> input && converter.eof() && input > 0 && input < 5) 
      return input;
    else 
      cout << "\033[1;31mError: Input must be an integer between 1 and 4.\033[0m\n";
  }
}

vector<Course> read_file()
{
    /* Open a file and read the coloumns into three seperate vectors, 
    which are then stored using a struct */
    vector<float> mark_data;
    vector<int> course_id;
    vector<string> course_name;

    std::ifstream file(file_name);
    if (!file) 
    { 
        std::cerr << "Failed to open file\n";
    }

    //Data values;

    vector<Course> courses;

    int row_count = 0;
    float mark;
    int id;
    string name;
    while (file >> mark >> id)
    {
        // Remove leading whitespace
        name.erase(0, name.find_first_not_of(" "));

        getline(file, name);

        courses.push_back(Course(name, mark, id));
        row_count++;
    }

    return courses;
}

void analyse_data(vector<Course>& data)
{
    /* Takes a vector of course data and performs a 
    generic statistical analysis on marks of said data */
    float sum = 0.0;
    int size = data.size();

    for (int i = 0; i < size; ++i) {
        sum += data[i].mark;
    }

    float mean = sum / size;
    
    float standard_deviation = get_standard_deviation(data, mean, size);
    float standard_error = standard_deviation/sqrt(size);

    cout  << "\nMean average of all marks: " << mean;
    cout << "\nStandard deviation of all marks: " << standard_deviation;
    cout << "\nStandard error of all marks: " << standard_error;
}

int main()
{
    
    vector<Course> data = read_file();
    int row_count = data.size();
    
    cout << "\n\n\033[1mFull list of data:\n\n\033[0m";
    for (int i = 0; i < row_count; i++)
    {
        cout << data[i].name  << " ("
             << data[i].id << "): " 
             << data[i].mark << "\n";
    }

    cout << "\nThis file has a total of " << row_count << " entries.";

    analyse_data(data);

    string message = "\nFor what year would you like the details of?: ";
    int target_year = get_integer_input(message);

    vector<Course> year_data;
    for (int i = 0; i < row_count; i++)
    {
        int target_value = data[i].id;
        while (target_value >= 10)
        {
            target_value /= 10;
        }

        if (target_value == target_year)
        {
            year_data.push_back(data[i]);
        }
    }

    cout << "\n\n\033[1mData for year " << target_year << ":\n\n\033[0m";
    for (int i = 0; i < year_data.size(); i++)
    {
        cout << year_data[i].name  << " ("
             << year_data[i].id << "): " 
             << year_data[i].mark << "\n";
    }

    row_count = year_data.size();
    cout << "\nThis year has a total of " << row_count << " entries.";
    
    analyse_data(year_data);

    return 0;
}