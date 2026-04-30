#include "greeks.h"
#include <cmath>

void calculate_greeks(BSMParameters &params, double d1, double d2) {
  params.greeks.gamma =
      pdf(d1) / (params.current_price * params.volatility * sqrt(params.time));

  params.greeks.vega = params.current_price * pdf(d1) * sqrt(params.time);
  if (params.option == CALL) {
    params.greeks.delta = cdf(d1);
    params.greeks.theta = -(params.current_price * pdf(d1) * params.volatility /
                            (2 * sqrt(params.time))) -
                          (params.risk_free_rate * params.strike_price *
                           exp(-params.risk_free_rate * params.time) * cdf(d2));
    params.greeks.rho = params.strike_price * params.time *
                        exp(-params.risk_free_rate * params.time) * cdf(d2);
  } else {
    params.greeks.delta = cdf(d1) - 1;
    params.greeks.theta =
        -(params.current_price * pdf(d1) * params.volatility /
          (2 * sqrt(params.time))) +
        (params.risk_free_rate * params.strike_price *
         exp(-params.risk_free_rate * params.time) * cdf(-d2));
    params.greeks.rho = -(params.strike_price * params.time *
                          exp(-params.risk_free_rate * params.time) * cdf(-d2));
  }
}
