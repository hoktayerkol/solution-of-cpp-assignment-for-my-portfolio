#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
 * Replace the values inside the vector "actions" with the one of your solution.
 * The index of the vector increases from the bottom left to top right.
 * The value of the vector indicates the action to perform at the corresponding state.
 * You can show on screen your solution running the python script "show.py" in the build folder.
 */

int main()
{
    vector<string> actions = {"up", "down", "left", "right",
                       "up", "down", "left", "right",
                       "up", "down", "left", "right",
                       "up", "down", "left", "right",
                       "up", "down", "left", "right",
                       "up", "down", "left", "right"};



    // DO NOT CHANGE THE FOLLOWING CODE

    std::ofstream output_file("./actions.txt");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(actions.begin(), actions.end(), output_iterator);
    cout << "Result wrote on file actions.txt" << endl;

    return 0;
}
