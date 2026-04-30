#include "bsm.h"
#include <cmath>

double calculate_d1(const BSMParameters &params) {
  return log(params.current_price / params.strike_price) +
         ((pow(params.volatility, 2) / 2) + params.risk_free_rate) *
             params.time / (params.volatility * sqrt(params.time));
}

double calculate_d2(double d1, const BSMParameters &params) {
  return d1 - (params.volatility * sqrt(params.time));
}

double pdf(double x) { return exp(-0.5 * x * x) / sqrt(2 * M_PI); }

double cdf(double x) { return erfc(-x / sqrt(2)) / 2; }

double getPrice(BSMParameters &input, double d1, double d2) {
  if (input.option == CALL) {
    return (input.current_price * cdf(d1) -
            (input.strike_price * exp(-input.risk_free_rate * input.time) *
             cdf(d2)));
  } else {
    return input.strike_price * exp(-input.risk_free_rate * input.time) *
               cdf(-d2) -
           (input.current_price * cdf(-d1));
  }
}

double calculatePCP(const BSMParameters &input, double d1, double d2) {
  double call =
      input.current_price * cdf(d1) -
      input.strike_price * exp(-input.risk_free_rate * input.time) * cdf(d2);
  double put =
      input.strike_price * exp(-input.risk_free_rate * input.time) * cdf(-d2) -
      input.current_price * cdf(-d1);
  double lhs = call - put;
  double rhs = input.current_price -
               input.strike_price * exp(-input.risk_free_rate * input.time);
  return lhs - rhs;
}
