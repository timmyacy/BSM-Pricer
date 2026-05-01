#include "ui.h"
#include <iomanip>
#include <iostream>
using namespace std;

BSMParameters getParams() {
  BSMParameters params{};
  cout << "Enter the current_price (S) \n";
  cin >> params.current_price;
  cout << "Enter your strike price (K) \n";
  cin >> params.strike_price;
  cout << "Enter the duration (12 months = 1) and 6 months = 0.5 etc \n";
  cin >> params.time;
  cout << "Enter the volatility \n";
  cin >> params.volatility;
  cout << "Enter the risk free rate \n";
  cin >> params.risk_free_rate;

  return params;
}
int getMenuChoice() {
  string options[] = {"CALL", "PUT", "CSV Mode"};
  int selected = 0;
  int total = 3;

  while (true) {
    cout << "\033[2J\033[H";
    cout << "Select option type (use arrow keys, enter to confirm):\n\n";

    for (int i = 0; i < total; i++) {
      if (i == selected)
        cout << " > " << options[i] << "\n";
      else
        cout << "   " << options[i] << "\n";
    }

    system("stty raw -echo");
    char c = getchar();
    system("stty cooked echo");

    if (c == '\033') {
      getchar();
      char arrow = getchar();
      if (arrow == 'A')
        selected = max(0, selected - 1);
      if (arrow == 'B')
        selected = min(total - 1, selected + 1);
    }
    if (c == '\n' || c == '\r')
      break;
  }

  return selected;
}
void printResults(const BSMParameters &input, double price, double pcp) {
  cout << string(35, '-') << "\n";
  cout << left << setw(20) << "Metric" << right << setw(12) << "Value"
       << "\n";
  cout << string(35, '-') << "\n";
  cout << "\nInputs:\n";
  cout << left << setw(20) << "Spot Price" << right << setw(12)
       << input.current_price << "\n";
  cout << left << setw(20) << "Strike" << right << setw(12)
       << input.strike_price << "\n";
  cout << left << setw(20) << "Time (years)" << right << setw(12) << input.time
       << "\n";
  cout << left << setw(20) << "Volatility" << right << setw(12)
       << input.volatility << "\n";
  cout << left << setw(20) << "Risk Free Rate" << right << setw(12)
       << input.risk_free_rate << "\n";
  cout << fixed << setprecision(6);
  cout << left << setw(20)
       << (input.option == CALL ? "Call Price" : "Put Price") << right
       << setw(12) << price << "\n";
  cout << string(35, '-') << "\n";
  cout << left << setw(20) << "Delta" << right << setw(12) << input.greeks.delta
       << "\n";
  cout << left << setw(20) << "Gamma" << right << setw(12) << input.greeks.gamma
       << "\n";
  cout << left << setw(20) << "Vega" << right << setw(12) << input.greeks.vega
       << "\n";
  cout << left << setw(20) << "Rho" << right << setw(12) << input.greeks.rho
       << "\n";
  cout << left << setw(20) << "Theta" << right << setw(12) << input.greeks.theta
       << "\n";
  cout << string(35, '-') << "\n";
  cout << left << setw(20) << "PCP Check" << right << setw(12) << pcp << "\n";
  cout << string(35, '-') << "\n";
}

void printCSVHeader() {
  cout << "\n";
  cout << string(100, '-') << "\n";
  cout << left << setw(6) << "Type" << setw(10) << "Spot" << setw(10)
       << "Strike" << setw(8) << "Time" << setw(8) << "Vol" << setw(12)
       << "Price" << setw(10) << "Delta" << setw(10) << "Gamma" << setw(10)
       << "Vega" << "Rho" << "Theta"
       << "\n";
  cout << string(100, '-') << "\n";
}
void printCSVResults(const BSMParameters &input, double price) {
  cout << fixed << setprecision(4);
  cout << left << setw(6) << (input.option == CALL ? "CALL" : "PUT") << setw(10)
       << input.current_price << setw(10) << input.strike_price << setw(8)
       << input.time << setw(8) << input.volatility << setw(12) << price
       << setw(10) << input.greeks.delta << setw(10) << input.greeks.gamma
       << setw(10) << input.greeks.vega << setw(10) << input.greeks.rho
       << input.greeks.theta << "\n";
}
