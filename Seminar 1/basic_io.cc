#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  cout << "Enter one integer: ";
  int number{};
  cin >> number;
  cout << "You entered the number: " << number << endl;
  cin.ignore(1000, '\n');

  cout << "Enter four integers:     ";
  int integers[4]{};
  for (int i = 0; i < 4; i++) {
    cin >> integers[i];
  }
  cout << "You entered the numbers: ";
  for (int i = 0; i < 4; i++) {
    cout << integers[i] << " ";
  }
  cout << endl;

  cout << "Enter one integer and one real number: ";
  float real{};
  cin >> number >> real;
  cout << "The real is:   " << real << endl;
  cout << "The integer is: " << number << endl;
  cin.ignore(1000, '\n');

  cout << "Enter one real and one integer number: ";
  cin >> real >> number;
  cout << "The real is:  ..." << real << endl;
  cout << "The integer is: ........" << number << endl;

  cout << "Enter a charcter: ";
  char c{};
  cin >> c;
  cout << "The character is: " << c << endl;
  cin.ignore(1000, '\n');

  cout << "Enter a word: ";
  string word{};
  cin >> word;
  cout << "The word '" << word << "' has " << word.length() << " charcter(s)."
       << endl;

  cout << "Enter an integer and a word: ";
  cin >> number >> word;
  cout << "You entered '" << number << "' and '" << word << "'." << endl;
  cin.ignore(1000, '\n');

  cout << "Enter a character and a word: ";
  cin >> c >> word;
  cout << "You entered the string \"" << word << "\" and the character '" << c
       << "'." << endl;
  cin.ignore(1000, '\n');

  cout << "Enter a word and a real number: ";
  cin >> word >> real;
  cout << "You entered \"" << word << "\" and \"" << real << "\"." << endl;
  cin.ignore(1000, '\n');

  cout << "Enter a text-line: ";
  string line{};
  getline(cin, line);
  cout << "You entered: \"" << line << "\"" << endl;

  cout << "Enter a second line of text: ";
  getline(cin, line);
  cout << "You entered: \"" << line << "\"" << endl;

  cout << "Enter three words: ";
  string words[3]{};
  for (int i = 0; i < 3; i++) {
    cin >> words[i];
  }
  cout << "You entered: '";
  for (int i = 0; i < words->length(); i++) {
    cout << words[i] << ' ';
  }
  cout << "'" << endl;

  return 0;
}
