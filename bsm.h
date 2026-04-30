#pragma once

enum OptionType { CALL, PUT };
struct Greeks {
  double delta{};
  double vega{};
  double gamma{};
  double theta{};
  double rho{};
};
struct BSMParameters {
  double risk_free_rate{};
  double volatility{};
  double time{};
  double current_price{};
  double strike_price{};
  OptionType option{};
  Greeks greeks{};
};

double calculate_d1(const BSMParameters &params);
double calculate_d2(double d1, const BSMParameters &params);
double pdf(double x);
double cdf(double x);
double getPrice(BSMParameters &input, double d1, double d2);
double calculatePCP(const BSMParameters &input, double d1, double d2);
