#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// TODO: Figure out what containers to use

using namespace std;

auto read_table(istream &is) {
  // /* appropriate associative container */ result { };
  map<string, set<string>> result{};

  string line;
  while (getline(is, line)) {
    istringstream iss{line};
    string entry{};
    string tag{};

    // /* appropriate container */ tags { };
    set<string> tags{};

    iss >> entry;
    while (iss >> tag) {
      /* insert 'tag' into 'tags' */;
      tags.insert(tag);
    }

    /* store an association between 'entry' and 'tags' into 'result' */
    result[entry] = tags;
  }
  return result;
}

/* Expected output:

   $ ./a.out names.txt Male Female
   Alex
   Austin
   Avery
   Blake
   Brooklyn
   Charlie
   Drew
   Jordan
   Kennedy
   Parker
   Taylor

   $ ./a.out names.txt Female
   Abigail
   Alex
   Amelia
   Austin
   Ava
   Avery
   Blake
   Brooklyn
   Camila
   Charlie
   Charlotte
   Drew
   Eleanor
   Elizabeth
   Ella
   Emma
   Evelyn
   Gianna
   Harper
   Isabella
   Jordan
   Kennedy
   Luna
   Mia
   Olivia
   Parker
   Scarlett
   Sofia
   Sophia
   Taylor

*/

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    cerr << "Usage: " << argv[0] << " FILE [TAGS...]" << endl;
    return 1;
  }

  ifstream ifs{argv[1]};
  // /* appropriate container */ tags { &argv[2], &argv[argc] };
  set<string> tags{&argv[2], &argv[argc]};

  auto table = read_table(ifs);

  /* implement the program here */
  auto filter = [&tags](auto pair) -> bool {
    // All of the tags are in pair.second
    return ranges::includes(pair.second, tags);
  };

  auto extract = [](auto pair) -> string { return pair.first; };

  std::ranges::copy(table | ranges::views::filter(filter) |
                        ranges::views::transform(extract),
                    std::ostream_iterator<string>(std::cout, "\n"));
}
