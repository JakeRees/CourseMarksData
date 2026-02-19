/*
                              Jake Rees, 11307374
                           University of Manchester

This program reads, analyses and outputs a formatted statistical analysis on
student mark data from a given .dat file.
*/

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

struct Course 
{
  string name;
  double mark;
  int id;

  Course(string name, double mark, int id)
  {
    this->name = name;
    this->mark = mark;
    this->id = id;
  }
};

double get_standard_deviation(vector<Course>& data, double mean, int size)
{
  // Takes a vector and returns the standard deviation of the elements
  double standard_deviation = 0.0;

  for (int i = 0; i < size; ++i)
    standard_deviation += pow(data[i].mark - mean, 2);

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

char get_char_input(string message, char& extra)
{
  /* Retrieves a character input and converts to lowercase, 
  also retrieves second character of input for validation purposes */
  char input;

  cout << "\n" << message;
  cin.get(input);
  cin.get(extra);
  input = tolower(input);

  return input;
}

vector<Course> read_file(string file_name, vector<int>& bad_lines)
{
  /* Open a file and read the coloumns into three seperate vectors, 
  which are then stored using a struct */
  std::ifstream file(file_name);
  if (!file) 
  { 
    std::cerr << "\033[1;31mFailed to open file\033[0m\n";
    abort();
  }

  vector<Course> courses;
  int line_number = 0;
  string line;

  while (std::getline(file, line))
  {
    line_number += 1;
    std::istringstream converter(line);

    double mark;
    int id;
    string name;

    // Ensures data is of expected type (double, int, string)

    if (converter >> mark >> id)
    {
      std::getline(converter, name);

      // Remove leading whitespace
      name.erase(0, name.find_first_not_of(" "));

      courses.push_back(Course(name, mark, id));
    }
    else
    {
        bad_lines.push_back(line_number);
    }
  }

  return courses;
}

void analyse_data(vector<Course>& data)
{
  /* Takes a vector of course data and performs a 
  basic statistical analysis on marks of said courses */
  double sum = 0.0;
  int size = data.size();

  for (int i = 0; i < size; ++i)
    sum += data[i].mark;

  double mean = sum / size;
  
  double standard_deviation = get_standard_deviation(data, mean, size);
  double standard_error = standard_deviation/sqrt(size);

  cout  << "\nMean average of marks: " << mean;
  cout << "\nStandard deviation of marks: " << standard_deviation;
  cout << "\nStandard error of marks: " << standard_error;
}

void print_data(vector<Course>& data, string subset, vector<int>& bad_lines)
{
  // Prints values from a subset of a given dataset
  int row_count = data.size();
  cout << "\n\n\033[1m" << subset << " list of data:\n\n\033[0m";
  for (int i = 0; i < row_count; i++)
  {
    cout << data[i].name  << " ("
         << data[i].id << "): " 
         << data[i].mark << "\n";
  }

  if (!bad_lines.empty())
  {
    cout << "\033[1;33mWarning: Couldn't read data from following lines: ";
    for (int i = 0; i < bad_lines.size(); i++)
    {
      cout << bad_lines[i] << ", ";
    }

    cout << " | these lines have been skipped\033[0m\n";
  }

  analyse_data(data);
}

int main()
{
  string const file_name = "course_marks.dat";
  vector<int> bad_lines;
  vector<Course> data = read_file(file_name, bad_lines);

  string message = "Should the data be ordered by name, ID, or mark (n/i/m)?: ";

  char extra_input;
  char order = get_char_input(message, extra_input);
  // Character input validation
  while ((order != 'n' && order != 'i' && order != 'm') || extra_input != '\n')
  {
    // Ignore extra letters - only need to look at first two
    while (extra_input != '\n' && cin.get(extra_input));

    cout << "\033[1;31mError: Input must be either 'n', 'i', 'm' \033[0m\n";
    order = get_char_input(message, extra_input);
  }

  // Sorts data based on required value using lambda function
  if (order != 'i')
  {
    sort(data.begin(), data.end(),
    [order](const Course& a, const Course& b)
    {
      if (order == 'n')
        return a.name < b.name;
      else
        return a.mark < b.mark;
    });
  }

  int row_count = data.size();
  print_data(data, "Full", bad_lines);
  cout << "\nThis file has a total of " << row_count << " entries.";

  message = "\nFor what year would you like the details of?: ";
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

  row_count = year_data.size();
  bad_lines.clear();
  print_data(year_data, "Year", bad_lines);
  cout << "\nThis year has a total of " << row_count << " entries.";

  return 0;
}