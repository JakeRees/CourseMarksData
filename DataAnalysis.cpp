#include<iostream>
#include<iomanip>
#include<cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::string;
using std::vector;

const string file_name = "course_marks.dat";

struct Data 
{
    vector<float> mark_data;
    vector<int> course_id;
    vector<string> course_name;
};

float get_standard_deviation(vector<float> data)
{
    // Takes a vector and returns the standard deviation of the elements
    double sum = 0.0, mean, standardDeviation = 0.0;

    int size = data.size();

    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }

    mean = sum / size;

    for (int i = 0; i < size; ++i) {
        standardDeviation += pow(data[i] - mean, 2);
    }

    return sqrt(standardDeviation / size);
}

float get_standard_error(vector<float> data, float standard_deviation)
{
    int size = data.size();
    return standard_deviation/sqrt(size);
}

int get_integer_input(const string& message) 
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

Data read_file()
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

    string line;
    Data values;

    int row_count = 0;
    float mark;
    int id;
    string name;
    while (file >> mark >> id)
    {
        // Remove leading whitespace
        name.erase(0, name.find_first_not_of(" "));

        getline(file, name);

        values.mark_data.push_back(mark);
        values.course_id.push_back(id);
        values.course_name.push_back(name);
        row_count++;
    }

    return values;
}

void analyse_data(vector<float> data)
{
    
    float standard_deviation = get_standard_deviation(data);
    float standard_error = get_standard_error(data, standard_deviation);

    cout << "\nStandard deviation of all marks: " << standard_deviation;
    cout << "\nStandard error of all marks: " << standard_error;
    
}

int main()
{
    
    Data data = read_file();
    int row_count = data.mark_data.size();
    
    cout << "\n\n\u001b[1mFull list of data:\n\n\033[0m";
    for (int i = 0; i < row_count; i++)
    {
        cout << data.mark_data[i] << " "
             << data.course_id[i] << " " 
             << data.course_name[i] << "\n";
    }

    cout << "\nThis file has a total of " << row_count << " entries.";

    analyse_data(data.mark_data);

    string message = "\nFor what year would you like the details of?: ";
    int target_year = get_integer_input(message);

    Data year_data;
    for (int i = 0; i < row_count; i++)
    {
        int target_value = data.course_id[i];
        while (target_value >= 10)
        {
            target_value /= 10;
        }

        if (target_value == target_year)
        {
            year_data.mark_data.push_back(data.mark_data[i]);
            year_data.course_id.push_back(data.course_id[i]);
            year_data.course_name.push_back(data.course_name[i]);
        }
    }

    cout << "\n\n\u001b[1mData for year " << target_year << ":\n\n\033[0m";
    for (int i = 0; i < year_data.mark_data.size(); i++)
    {
        cout << year_data.mark_data[i] << " "
             << year_data.course_id[i] << " " 
             << year_data.course_name[i] << "\n";
    }

    row_count = year_data.mark_data.size();
    cout << "\nThis file has a total of " << row_count << " entries.";
    
    analyse_data(year_data.mark_data);

    return 0;
}