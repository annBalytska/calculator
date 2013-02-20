//
//  ViewController.m
//  calculator
//
//  Created by Anna Balytska on 2/14/13.
//  Copyright (c) 2013 softserve. All rights reserved.
//

#import "ViewController.h"
#include <string>
#include <stdexcept>
#include "rpn.h"

@interface ViewController ()

@end


@implementation ViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    _expression= [[NSMutableString alloc] init];
    _exp_to_calc= [[NSMutableString alloc] init];
    _mem= [[NSMutableString alloc] init];
    mr=false;
	// Do any additional setup after loading the view, typically from a nib.
    
    //self.display.text = @"Hello, World!";

};

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc {
    [_display release];
    [super dealloc];
    [_expression release];
    [_exp_to_calc release];
    [_mem release];
}

- (IBAction)digitPressed:(id)sender {
    NSString * tag2char[] = {
        @"1",   // tag = 0
        @"2",   // tag = 1
        @"3",   // tag = 2
        @"+",   // tag = 3
        @"4",   // tag = 4
        @"5",   // tag = 5
        @"6",   // tag = 6
        @"-",   // tag = 7
        @"7",   // tag = 8
        @"8",   // tag = 9
        @"9",   // tag = 10
        @"*",   // tag = 11
        @"0",   // tag = 12
        @"(",   // tag = 13
        @")",   // tag = 14
        @"/",   // tag = 15
        @".",   // tag = 16
        @"sin(",   // tag = 17
        @"cos(",   // tag = 18
    };
    
    UIButton *button=sender;
    int tag = button.tag;
    NSString *buttonName = tag2char[tag];
    [_expression appendString:buttonName];
    if (tag<17) 
        [_exp_to_calc appendString:buttonName];
    else if (tag==17)
        [_exp_to_calc appendString:@"s("];
    else if (tag==18)
        [_exp_to_calc appendString:@"c("];
    self.display.text= _expression;
    mr=false;
}

- (IBAction)Equal:(id)sender {
     UIButton *button=sender;
    double result;
    int res;
    bool b=true;
    std::string str = [_exp_to_calc UTF8String];
    try {
        result=calculate(str);
    } catch (const std::exception &ex) {
        NSString *errMsg = [NSString stringWithFormat:@"%s", ex.what()];
        [_expression setString:errMsg];
        self.display.text= _expression;
        b=false;
    }
   if(b==true)
   {
       res=result;
       if(result==double(res))
           self.display.text= [NSString stringWithFormat:@"%d",res];
       else if(result!=double(res))
           self.display.text= [NSString stringWithFormat:@"%f",result];

       if(button.tag==20)
           [_mem setString:_expression];
       else if(button.tag==19)
       {
           [_expression setString:@""];
           [_exp_to_calc setString:@""];
       }
    }
    mr=false;
}

- (IBAction)Clear:(id)sender {
    [_expression setString:@""];
    [_exp_to_calc setString:@""];
    self.display.text= @"";
    mr=false;
}

- (IBAction)Pop:(id)sender {
    if([_expression length]>=1)
    {
        NSString *text=[_expression substringToIndex:[_expression length] - 1];
        NSString *text1=[_exp_to_calc substringToIndex:[_exp_to_calc length] - 1];
        [_expression setString:text];
        [_exp_to_calc setString:text1];
        self.display.text= _expression;
        mr=false;
    }
}


- (IBAction)returnMem:(id)sender {
    if(mr==false)
    {
        [_expression appendString:_mem];
        [_exp_to_calc appendString:_mem];
        self.display.text= _expression;
        mr=true;
    }
}

@end
