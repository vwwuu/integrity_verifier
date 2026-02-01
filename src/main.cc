#include "../include/statuses.h"
#include "../include/status_out.h"

#include <cctype>
#include <iostream>
#include <limits>
using namespace std;

#define ATTEMPT_LIMITS 3

int main () {
  int attempts = ATTEMPT_LIMITS;
  int modeSelected = -1;
  
  cout << "Please selected a mode:" << endl;
  cout << "(1) Record mode" << endl;
  cout << "(2) Read mode" << endl;
  cout << "(3) Verify mode" << endl;
  cout << "(Exit) Enter any key" << endl;
  cout << "Mode: ";
  cin >> modeSelected;

  while (!cin && attempts > 0) {
    cout << "Bad input.(" << attempts << " attempts remaining)"<< endl;
    --attempts;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Select mode: ";
    cin >> modeSelected;
  }
  
  print_status(modeSelected);
  return 0;
}
