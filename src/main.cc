#include "../include/Statuses.h"
#include "../include/status_out.h"

#include <cctype>
#include <iostream>
#include <limits>

#define ATTEMPT_LIMITS 3

int main () {
  int attempts = ATTEMPT_LIMITS;
  std::string modeSelected = "";
  
  std::cout << "Please selected a mode:" << std::endl;
  std::cout << "(1) Record mode" << std::endl;
  std::cout << "(2) Read mode" << std::endl;
  std::cout << "(3) Verify mode" << std::endl;
  std::cout << "(Exit)" << std::endl;
  std::cout << "Mode: ";
  std::cin >> modeSelected;

  while (!std::cin && attempts > 0) {
    std::cout << "Bad input.(" << attempts << " attempts remaining)"<< std::endl;
    --attempts;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Select mode: ";
    std::cin >> modeSelected;
  }
  
  print_status(normalizeInput(modeSelected));
  return 0;
}
