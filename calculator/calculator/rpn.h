//
//  rpn.h
//  calculator
//
//  Created by Anna Balytska on 2/15/13.
//  Copyright (c) 2013 softserve. All rights reserved.
//

#ifndef calculator_rpn_h
#define calculator_rpn_h

#include <string>
#include <iostream>
#include <stack>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

struct Op {
	bool is_opeartor;
	union {
		double value;
		char operator_name;
	};
};

double calculate(string my_string);

#endif
