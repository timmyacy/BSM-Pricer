#include "../include/bsm.h"
#include "../include/greeks.h"
#include <gtest/gtest.h>

BSMParameters makeParams(double S, double K, double T, double vol, double r,
                         OptionType opt) {
  BSMParameters p{};
  p.current_price = S;
  p.strike_price = K;
  p.time = T;
  p.volatility = vol;
  p.risk_free_rate = r;
  p.option = opt;
  return p;
}

TEST(BSMPrice, ATMCall) {
  auto p = makeParams(100, 100, 1, 0.2, 0.05, CALL);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  EXPECT_NEAR(getPrice(p, d1, d2), 10.4506, 0.001);
}

TEST(BSMPrice, OTMCall) {
  auto p = makeParams(100, 110, 0.5, 0.25, 0.05, CALL);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  EXPECT_NEAR(getPrice(p, d1, d2), 4.2258, 0.001);
}

TEST(BSMPrice, ITMCall) {
  auto p = makeParams(150, 120, 1, 0.25, 0.05, CALL);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  EXPECT_NEAR(getPrice(p, d1, d2), 38.1188, 0.001);
}

TEST(BSMPrice, ATMPut) {
  auto p = makeParams(100, 100, 1, 0.2, 0.05, PUT);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  EXPECT_NEAR(getPrice(p, d1, d2), 5.5735, 0.001);
}

TEST(BSMPrice, OTMPut) {
  auto p = makeParams(100, 90, 0.5, 0.25, 0.05, PUT);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  EXPECT_NEAR(getPrice(p, d1, d2), 2.2150, 0.001);
}

TEST(BSMPrice, ITMPut) {
  auto p = makeParams(75, 80, 0.5, 0.35, 0.02, PUT);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  EXPECT_NEAR(getPrice(p, d1, d2), 9.8778, 0.001);
}

TEST(BSMParity, ATM) {
  auto p = makeParams(100, 100, 1, 0.2, 0.05, CALL);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  EXPECT_NEAR(calculatePCP(p, d1, d2), 0.0, 0.0001);
}

TEST(BSMGreeks, CallDelta) {
  auto p = makeParams(100, 100, 1, 0.2, 0.05, CALL);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  calculate_greeks(p, d1, d2);
  EXPECT_NEAR(p.greeks.delta, 0.6368, 0.001);
}

TEST(BSMGreeks, PutDelta) {
  auto p = makeParams(100, 100, 1, 0.2, 0.05, PUT);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  calculate_greeks(p, d1, d2);
  EXPECT_NEAR(p.greeks.delta, -0.3632, 0.001);
}

TEST(BSMGreeks, Gamma) {
  auto p = makeParams(100, 100, 1, 0.2, 0.05, CALL);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  calculate_greeks(p, d1, d2);
  EXPECT_NEAR(p.greeks.gamma, 0.0188, 0.0001);
}

TEST(BSMGreeks, Vega) {
  auto p = makeParams(100, 100, 1, 0.2, 0.05, CALL);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  calculate_greeks(p, d1, d2);
  EXPECT_NEAR(p.greeks.vega, 37.524, 0.01);
}

TEST(BSMGreeks, CallRho) {
  auto p = makeParams(100, 100, 1, 0.2, 0.05, CALL);
  double d1 = calculate_d1(p);
  double d2 = calculate_d2(d1, p);
  calculate_greeks(p, d1, d2);
  EXPECT_NEAR(p.greeks.rho, 53.2325, 0.01);
}

TEST(BSMGreeks, GammaSameForCallAndPut) {
  auto call = makeParams(100, 100, 1, 0.2, 0.05, CALL);
  auto put = makeParams(100, 100, 1, 0.2, 0.05, PUT);
  double d1c = calculate_d1(call);
  double d1p = calculate_d1(put);
  calculate_greeks(call, d1c, calculate_d2(d1c, call));
  calculate_greeks(put, d1p, calculate_d2(d1p, put));
  EXPECT_NEAR(call.greeks.gamma, put.greeks.gamma, 0.0001);
}

TEST(BSMGreeks, VegaSameForCallAndPut) {
  auto call = makeParams(100, 100, 1, 0.2, 0.05, CALL);
  auto put = makeParams(100, 100, 1, 0.2, 0.05, PUT);
  double d1c = calculate_d1(call);
  double d1p = calculate_d1(put);
  calculate_greeks(call, d1c, calculate_d2(d1c, call));
  calculate_greeks(put, d1p, calculate_d2(d1p, put));
  EXPECT_NEAR(call.greeks.vega, put.greeks.vega, 0.0001);
}
