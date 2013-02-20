//
//  CalculatorBrain.h
//  calculator
//
//  Created by Anna Balytska on 2/14/13.
//  Copyright (c) 2013 softserve. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CalculatorBrain : NSObject
{
    double operand;
}

-(void)setOperand:(double)anOperand;
-(double)performOperation:(NSString *)operation;
//-(NSArray *)foo:(int)zap bar:(id)pow;

@end
