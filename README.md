# BSM Pricer

A CLI Black-Scholes options pricer written in C++. Prices European call and put options, computes all five Greeks, verifies put-call parity, and supports batch pricing via CSV input.

## Features

- European call and put pricing via the Black-Scholes-Merton closed-form formula
- All five Greeks: Delta, Gamma, Vega, Theta, Rho
- Put-call parity verification on every calculation
- Interactive arrow-key menu for option type selection
- CSV batch mode: select a CSV file from the project directory and price all rows at once
- Google Test suite covering prices, Greeks, and mathematical properties

## Project Structure

```
BSM-Pricer/
├── main.cpp              # Entry point, orchestration only
├── include/
│   ├── bsm.h             # BSMParameters struct, pricing declarations
│   ├── greeks.h          # Greeks struct, calculate_greeks declaration
│   ├── ui.h              # Display and menu declarations
│   └── parser.h          # CSV mode declaration
├── src/
│   ├── bsm.cpp           # d1/d2, pdf, cdf, getPrice, calculatePCP
│   ├── greeks.cpp        # calculate_greeks (all five Greeks)
│   ├── ui.cpp            # getParams, getMenuChoice, printResults, printCSVResults
│   └── parser.cpp        # CSV file discovery, selection, parsing, runCSVMode
├── tests/
│   └── bsm_test.cpp      # Google Test suite
├── data1.csv             # Example CSV input
└── CMakeLists.txt
```

---

## Build

Requires CMake 3.14+ and a C++17 compiler (Apple Clang, GCC, or MSVC).

```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
```

## Run

```bash
./cmake-build-debug/main
```

You will be presented with an arrow-key menu:

```
Select option type (use arrow keys, enter to confirm):

 > CALL
   PUT
   CSV Mode
```

For single pricing, select CALL or PUT and enter the parameters when prompted:

```
Enter the current_price (S): 100
Enter your strike price (K): 100
Enter the duration (1 = 1 year, 0.5 = 6 months): 1
Enter the volatility: 0.2
Enter the risk free rate: 0.05
```

## Example Output

```
-----------------------------------
Metric                       Value
-----------------------------------
Inputs:
Spot Price                     100
Strike                         100
Time (years)                     1
Volatility                     0.2
Risk Free Rate                0.05
Call Price               10.450584
-----------------------------------
Delta                     0.636831
Gamma                     0.018762
Vega                     37.524035
Rho                      53.232482
Theta                    -6.414028
-----------------------------------
PCP Check                -0.000000
-----------------------------------
```

---

## CSV Mode

Create a CSV file in the project root with the following format i.e S, K, T, Volatility, Risk Free Rate, Option Type:

```
current_price,strike_price,time,volatility,risk_free_rate,option
100,100,1,0.2,0.05,CALL
100,110,0.5,0.25,0.05,PUT
150,120,1,0.25,0.05,CALL
```

Select `CSV Mode` from the menu, choose your file, and all rows are priced and displayed in a single table:

```
----------------------------------------------------------------------------------------------------
Type  Spot      Strike    Time    Vol     Price       Delta     Gamma     Vega      Rho       Theta
----------------------------------------------------------------------------------------------------
CALL  100.0000  100.0000  1.0000  0.2000  10.4506     0.6368    0.0188    37.5240   53.2325   -6.4140
PUT   100.0000  100.0000  1.0000  0.2000  5.5735      -0.3632   0.0188    37.5240   -41.8905  -1.6579
CALL  100.0000  110.0000  0.5000  0.2500  4.2258      0.3785    0.0215    26.8915   16.8136   -8.4042
PUT   100.0000  90.0000   0.5000  0.2500  2.2150      -0.2045   0.0160    20.0588   -11.3302  -3.8817
CALL  50.0000   50.0000   1.0000  0.3000  6.6417      0.5987    0.0258    19.3334   23.2937   -3.5988
----------------------------------------------------------------------------------------------------
```

## Tests

Tests use Google Test, downloaded automatically by CMake via FetchContent.

```bash
./cmake-build-debug/tests
```

The test suite covers:

- ATM, OTM, and ITM call prices
- ATM, OTM, and ITM put prices  
- Put-call parity holds to within 0.0001
- Delta, Gamma, Vega, Rho for ATM call
- Gamma and Vega are identical for calls and puts (mathematical property)

## Implementation Notes

**Normal CDF** is implemented via `erfc` from `<cmath>`:
```cpp
double cdf(double x) { return erfc(-x / sqrt(2)) / 2; }
```

**Normal PDF** is implemented directly:
```cpp
double pdf(double x) { return exp(-0.5 * x * x) / sqrt(2 * M_PI); }
```

All arithmetic uses `double` throughout for 15 significant digits of precision.
