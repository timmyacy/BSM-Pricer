#pragma once
#include "bsm.h"

BSMParameters getParams();
int getMenuChoice();
void printResults(const BSMParameters &input, double price, double pcp);
