#include "../include/status_out.h"
#include <iostream>

using namespace std;

void print_status (int status) {
  if (status == RECORD) {
    cout << "Entering Record Mode..." << endl;
  }
  else if (status == READ) {
    cout << "Entering Read Mode..." << endl;
  }
  else if (status == VERIFY) {
    cout << "Entering Verify Mode..." << endl;
  }
  else {
    cout << "Exiting..." << endl;
  }
  return;
}
