#include <cmath>
#include <iostream>
using namespace std;
struct BSMParameters {
  double risk_free_rate{};
  double volatility{};
  int time{};
  double current_price{};
  double strike_price{};
};

BSMParameters getParams() {
  BSMParameters params{};

  cout << "Enter your price \n";
  cin >> params.strike_price;
  cout << "Enter the duration \n";
  cin >> params.time;
  cout << "Enter the volatility \n";
  cin >> params.volatility;
  cout << "Enter the risk free rate \n";
  cin >> params.risk_free_rate;
  cout << "Enter the current_price \n";
  cin >> params.current_price;

  return params;
}

double calculate_d1(const BSMParameters &params) {

  double d1{};
  d1 = log(params.current_price / params.strike_price) +
       ((pow(params.volatility, 2) / 2) + params.risk_free_rate) * params.time /
           (params.volatility * sqrt(params.time));

  return d1;
}

double calculate_d2(double d1, const BSMParameters &params) {
  double d2{};
  d2 = d1 - (params.volatility * sqrt(params.time));
  return d2;
}

int main() {
  BSMParameters input = getParams();
  double d1 = calculate_d1(input);
  double d2 = calculate_d2(d1, input);
  double call_price =
      (input.current_price * (erfc(-d1 / std::sqrt(2)) / 2) -
       (input.strike_price * exp(-input.risk_free_rate * input.time) *
        (erfc(-d2 / std::sqrt(2)) / 2)));
  cout << " The call price is " << call_price;
  return 0;
}
