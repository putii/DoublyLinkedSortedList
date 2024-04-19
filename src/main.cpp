#include "DoublyLinkedSortedList.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

/**
 * @file main.cpp
 * @brief Main function for the Doubly Linked Sorted List program.
 */

/**
 * @brief The main function of the program.
 *
 * This function reads numerical data from a given file and places them in an ordered doubly linked list.
 * The data format is integers, and the range is user-defined. The functions of the program include:
 * - Reading the data file and number range as program execution arguments.
 * - Adding read numbers from the file to a dynamic doubly linked list ordered in ascending order.
 * - Adding to the list only numbers from the given range (inclusive of the left limit and exclusive of the right limit).
 * - Displaying the contents of the list from left to right and from right to left.
 * - Deleting the list (before the program ends).
 *
 * The program is equipped with error resilience mechanisms, including:
 * - Checking the effects of opening (or not) the indicated file.
 * - Checking the ranges of numbers read from the file using assertions.
 * - Checking pointers returned by memory allocation functions (malloc, new) using assertions.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of character pointers listing all the arguments.
 * @return int The exit code; 0 if no errors.
 */
int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <file_path> <int1> <int2>\n";
    return 1;
  }

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

  std::string file_path = argv[1];
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
      assert(val1 <= num && num < val2 && "Number out of range");
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
  list.showRightToLeft();

  return 0;
}