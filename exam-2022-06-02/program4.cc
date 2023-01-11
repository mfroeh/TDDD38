#include <iostream>
#include <fstream>
#include <vector>
#include <ranges>
#include <map>
#include <sstream>
#include <set>
#include <algorithm>

/*

Example runs:

$ ./a.out example.txt 
The following parameters are not defined:
#0
#1
#2
#3

$ ./a.out example.txt first second
The following parameters are not defined:
#2
#3

$ ./a.out example.txt first second third fourth
In this text first is a parameter, and the same is true for second
meaning that first and second can be whatever we want. Also, as a test
we add fourth as well, thus skipping the third argument (but as a test
we include third here).

*/

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "USAGE: " << argv[0] << " TEXT [PARAMETERS...]\n";
        return 1;
    }

    std::ifstream ifs { argv[1] };
    if (!ifs)
    {
        std::cerr << "Error: Unable to open file '" << argv[1] << "'\n";
        return 2;
    }

    // Recall that any container can be directly initialized with an iterator range
    vector<string> text{istream_iterator<string>{ifs}, istream_iterator<string>()};

    map<string, string> params{};
    transform(argv+2, argv+argc, inserter(params, begin(params)),
            [i=0](char* arg) mutable {
                ostringstream oss{};
                oss << "#" << i++;
                return make_pair(oss.str(), arg);
            });

    set<string> undefined{};
    ranges::copy_if(text, inserter(undefined, begin(undefined)), 
            [&params](string const& s) { 
                return s[0] == '#' && !params.contains(s); 
            });

    if (undefined.size() > 0) {
        cerr << "The following parameters are not defined:" << endl;
        ranges::copy(undefined, ostream_iterator<string>(cerr, "\n"));
        return -1;
    }

    vector<string> replaced{};
    ranges::transform(text, back_inserter(replaced), 
            [&params](string s) {
                return s[0] == '#' ? params[s] : s; 
            }); 

    ranges::copy(replaced, ostream_iterator<string>(cout, " "));
}
