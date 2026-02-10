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

struct Data {
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

Data read_file()
{
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
        int i = 0;
        while (i < name.size() && std::isspace(static_cast<unsigned char>(name[i]))) {
            i++;
        }
        name.erase(0, i);

        getline(file, name);

        values.mark_data.push_back(mark);
        values.course_id.push_back(id);
        values.course_name.push_back(name);
        row_count++;
    }

    return values;
}

int main()
{
    
    Data data = read_file();
    int row_count = data.mark_data.size();
    
    cout << "\nFull list of data: ";
    for (int i = 0; i < row_count; i++)
    {
        cout << data.mark_data[i] << " "
             << data.course_id[i] << " " 
             << data.course_name[i] << "\n";
    }

    cout << "\nThis file has a total of " << row_count << " entries.";

    float standard_deviation = get_standard_deviation(data.mark_data);
    float standard_error = get_standard_error(data.mark_data, standard_deviation);

    cout << "\nStandard deviation of all marks: " << standard_deviation;
    cout << "\nStandard error of all marks: " << standard_error;

    

    return 0;
}