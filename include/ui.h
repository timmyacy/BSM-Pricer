#pragma once
#include "bsm.h"

BSMParameters getParams();
int getMenuChoice();
void printCSVHeader();
void printCSVResults(const BSMParameters &input, double price);
void printResults(const BSMParameters &input, double price, double pcp);
