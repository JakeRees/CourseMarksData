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

const string file_name = "course_marks.dat";

int main()
{
    std::vector<float> mark_data;
    std::vector<int> course_id;
    std::vector<string> course_name;

    std::ifstream file(file_name);
    if (!file) 
    { 
        std::cerr << "Failed to open file\n"; 
        return 1; 
    }

    string line;

    int line_count = 0;
    float mark;
    int id;
    string name;
    while (file >> mark >> id)
    {
        getline(file, name);

        mark_data.push_back(mark);
        course_id.push_back(id);
        course_name.push_back(name);
        line_count++;
    }

    cout << mark_data[0] << course_id[0] << course_name[0];
    cout << "\n\n";
    cout << mark_data[1] << course_id[1] << course_name[1];

    cout << "\n\nThis file has a total of " << line_count << " entries.";

    return 0;
}