//
//  rpn.cpp
//  calculator
//
//  Created by Anna Balytska on 2/15/13.
//  Copyright (c) 2013 softserve. All rights reserved.
//

#include "rpn.h"
#include "math.h"
#include <stdexcept>

// RPN.cpp : Defines the entry point for the console application.
//


string signs="*/+-()sc";
string digits="0123456789.";

double evaluate_rpn(list<Op> &exp)
{
    stack <double> my_stack;
    double a,b;
    double res;
    for(list<Op>::iterator it=exp.begin(); it!=exp.end(); ++it)
    {
        if(it->is_opeartor==false)
            my_stack.push(it->value);
        
        else if(it->is_opeartor==true)
        {
            if(it->operator_name=='*')
            {
                a=my_stack.top();
                my_stack.pop();
                b=my_stack.top();
                my_stack.pop();
                my_stack.push(a*b);
            }
            // blablabla
            else if(it->operator_name=='/')
            {
                a=my_stack.top();
                my_stack.pop();
                b=my_stack.top();
                my_stack.pop();
                my_stack.push(b/a);
            }
            
            else if(it->operator_name=='+')
            {
                a=my_stack.top();
                my_stack.pop();
                b=my_stack.top();
                my_stack.pop();
                my_stack.push(a+b);
            }
            
            else if(it->operator_name=='-')
            {
                a=my_stack.top();
                my_stack.pop();
                b=my_stack.top();
                my_stack.pop();
                my_stack.push(b-a);
            }
            
            else if(it->operator_name=='s')
            {
                a=my_stack.top();
                my_stack.pop();
                my_stack.push(sin(a));
            }
            
            else if(it->operator_name=='c')
            {
                a=my_stack.top();
                my_stack.pop();
                my_stack.push(cos(a));
            }
        }
    }
    res=my_stack.top();
    return res;
}


list<Op> convert_to_rpn(list<Op> &ops)
{
	list<Op> rpn;
	Op elem;
	stack <char> my_stack;
    int num=0;
	for(list<Op>::iterator it=ops.begin(); it!=ops.end(); ++it)
	{
		if(it->is_opeartor==false)
		{
			elem.is_opeartor=it->is_opeartor;
			elem.value=it->value;
			rpn.push_back(elem);
		}
		else if(it->is_opeartor==true)
        {
			if(it->operator_name=='(')
            {
                my_stack.push(it->operator_name);
                num++;
            }
            
            else if(it->operator_name==')')
            {
                num--;
                while (!my_stack.empty() && my_stack.top()!='(')
                {
                    elem.is_opeartor=true;
                    elem.operator_name=my_stack.top();
                    rpn.push_back(elem);
                    my_stack.pop();
                }
                
                if (!my_stack.empty() && my_stack.top() == '(') 
                    my_stack.pop();
                else
                    throw std::runtime_error("Expected (");
            }
            
            else if((it->operator_name!='(')&&(it->operator_name!=')'))
            {
                if(my_stack.empty())
                    my_stack.push(it->operator_name);
                else if(!my_stack.empty())
                {
                    if ((my_stack.top()=='*')||(my_stack.top()=='/'))
                    {
                        elem.is_opeartor=true;
                        elem.operator_name=my_stack.top();
                        rpn.push_back(elem);
                        my_stack.pop();
                        my_stack.push(it->operator_name);
                    }
                    else if (((my_stack.top()=='+')||(my_stack.top()=='-'))&&((elem.operator_name=='+')||(elem.operator_name=='-')))
                    {
                        elem.is_opeartor=true;
                        elem.operator_name=my_stack.top();
                        rpn.push_back(elem);
                        my_stack.pop();
                        my_stack.push(it->operator_name);
                    }
                    else
                    {
                        my_stack.push(it->operator_name);
                    }
                }
            }
        }
	}
    while(!my_stack.empty())
    {
        elem.is_opeartor=true;
        elem.operator_name=my_stack.top();
        rpn.push_back(elem);
        my_stack.pop();
    }

    if(num!=0)
        throw  std::runtime_error("Expected )");
	return rpn;
}

list<Op> parse_expression(const string &exp)
{
	list<Op> ops;
	Op elem;
	string stemp;
	double dtemp;
	unsigned int end=0;
	for(size_t i=0;i<exp.size();i++)
	{
		if(signs.find_first_of(exp[i])!=string::npos)
		{
			elem.is_opeartor=true;
			elem.operator_name=exp[i];
			ops.push_back(elem);
		}
		else if(digits.find_first_of(exp[i])!=string::npos)
		{
			end=exp.find_first_not_of(digits,i);
			if(end!=exp.npos)
			{
				stemp=exp.substr(i,end-i);
				i=end-1;
			}
			else if(end==exp.npos)
			{
				stemp=exp.substr(i,exp.size());
				i=exp.size();
			}
			dtemp = (double)atof(stemp.c_str());
			elem.is_opeartor=false;
			elem.value=dtemp;
			ops.push_back(elem);
		}
	}
    
	return ops;
}

double calculate(string my_string)
{
    double result;
    if(my_string.empty())
    {
        return 0;
    }
    list<Op> mylist=parse_expression(my_string);
    list<Op> rpn=convert_to_rpn(mylist);
    result=evaluate_rpn(rpn);
	return result;
}

