#include "DoublyLinkedSortedList.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <file_path> <int1> <int2>\n";
    return 1;
  }

  std::string file_path = argv[1];
  int val1, val2;

  try {
    val1 = std::stoi(argv[2]);
    val2 = std::stoi(argv[3]);
  } catch (std::invalid_argument& e) {
    std::cerr << "Invalid integer argument: " << e.what() << "\n";
    return 2;
  } catch (std::out_of_range& e) {
    std::cerr << "Integer argument out of range: " << e.what() << "\n";
    return 3;
  }

  if (val1 >= val2) {
    std::cerr << "Usage: " << argv[0] << " <file_path> <int1> <int2>\n";
    std::cerr << "<int1> = " << val1 << ", <int2> = " << val2 << " do not satisfy <int1> < <int2>\n";
    return 4;
  }

  std::ifstream file(file_path);
  if (!file) {
    std::cerr << "Unable to open file: " << file_path << "\n";
    return 5;
  }

  /* There will be no assertions, as they are not suitable for checking runtime errors, nor input validation
   * Instead try-catch blocks, return codes and others will be used */

  DoublyLinkedSortedList list;
  std::string line;
  while (std::getline(file, line)) {
    try {
      int num = std::stoi(line);
      if (val1 <= num && num < val2) {
        list.addValue(num);
      }
    } catch (std::invalid_argument& e) {
      std::cerr << "Invalid integer in file: " << e.what() << "\n";
      return 6;
    } catch (std::out_of_range& e) {
      std::cerr << "Integer in file out of range: " << e.what() << "\n";
      return 7;
    }
  }

  std::cout << '\n';
  list.showLeftToRight();

  return 0;
}