#include <algorithm>
#include <cmath> // for std::sqrt
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
    return 1;
  }

  // filename is stored in argv[1]
  // implement the steps here

  ifstream ifs{argv[1]};
  if (!ifs.is_open()) {
    cerr << "No such file " << argv[1] << endl;
  }

  double dx{};
  ifs >> dx;

  vector<double> values{};
  ranges::copy(istream_iterator<double>(ifs), istream_iterator<double>(),
               back_inserter(values));

  vector<double> lengths{};
  // adjacent_difference(begin(values), end(values), back_inserter(lengths));

  // Equivalent to the above except that this stores only differences in lengths
  // For std::adjacent_difference the first element of lengths is the first
  // element of the iterator

  transform(begin(values), next(end(values), -1), next(begin(values)),
            back_inserter(lengths),
            [](auto d1, auto d2) -> double { return abs(d1 - d2); });

  ranges::transform(begin(lengths), end(lengths), begin(lengths),
                    [&dx](double dy) { return sqrt(dx * dx + dy * dy); });

  double sum{accumulate(begin(lengths), end(lengths), 0.0)};
  cout << sum << endl;
}
