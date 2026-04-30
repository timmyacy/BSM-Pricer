#include "bsm.h"
#include "greeks.h"
#include "ui.h"

int main() {
  int choice = getMenuChoice();
  BSMParameters input = getParams();
  input.option = (choice == 0) ? CALL : PUT;
  double d1 = calculate_d1(input);
  double d2 = calculate_d2(d1, input);
  double price = getPrice(input, d1, d2);
  double pcp = calculatePCP(input, d1, d2);
  calculate_greeks(input, d1, d2);
  printResults(input, price, pcp);
  return 0;
}
