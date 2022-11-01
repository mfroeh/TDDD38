#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  ifstream ifs{"word_length.cc"};
  string word{};
  int n{};

  cout << n << endl;

  int word_count{0};
  int len_cum{0};
  int len_min{INT_MAX};
  int len_max{INT_MIN};
  string word_max{};
  string word_min{};
  while (ifs >> word) {
    int len = word.length();
    word_count++;
    len_cum += len;

    if (len > len_max) {
      len_max = len;
      word_max = word;
    } else if (len < len_min) {
      word_min = word;
      len_min = len;
    }
  }
  cout << "There are " << word_count << " words in the file." << endl;
  cout << "The shortest word was " << word_min << " with " << len_min
       << " character(s)" << endl;
  cout << "The longest word was " << word_max << " with " << len_max
       << " character(s)" << endl;
  cout << "The average word length was "
       << static_cast<float>(len_cum) / word_count << " character(s)" << endl;

  return 0;
}
