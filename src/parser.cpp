#include "parser.h"
#include "bsm.h"
#include "greeks.h"
#include "ui.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

vector<string> getCSVFiles() {
  vector<string> files;
  for (auto &entry : fs::directory_iterator(".")) {
    if (entry.path().extension() == ".csv") {
      files.push_back(entry.path().filename().string());
    }
  }
  return files;
}
int getCSVChoice(const vector<string> &files) {
  int selected = 0;
  int total = files.size();

  while (true) {
    cout << "\033[2J\033[H";
    cout << "Select CSV file:\n\n";
    for (int i = 0; i < total; i++) {
      cout << (i == selected ? " > " : "   ") << files[i] << "\n";
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

void runCSVMode() {
  vector<string> files = getCSVFiles();
  if (files.empty()) {
    cout << "No CSV files found in current directory\n";
    return;
  }
  int choice = getCSVChoice(files);
  string filename = files[choice];

  ifstream file(filename);

  string line;
  getline(file, line);
  printCSVHeader();
  while (getline(file, line)) {
    stringstream ss(line);
    string token;
    BSMParameters params{};
    getline(ss, token, ',');
    params.current_price = stod(token);

    getline(ss, token, ',');
    params.strike_price = stod(token);

    getline(ss, token, ',');
    params.time = stod(token);

    getline(ss, token, ',');
    params.volatility = stod(token);

    getline(ss, token, ',');
    params.risk_free_rate = stod(token);

    getline(ss, token, ',');
    params.option = (token == "CALL") ? CALL : PUT;

    // now price it
    double d1 = calculate_d1(params);
    double d2 = calculate_d2(d1, params);
    double price = getPrice(params, d1, d2);
    double pcp = calculatePCP(params, d1, d2);
    calculate_greeks(params, d1, d2);
    printCSVResults(params, price);
  }
  cout << string(80, '-') << "\n";
}
