//
//  ViewController.h
//  calculator
//
//  Created by Anna Balytska on 2/14/13.
//  Copyright (c) 2013 softserve. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
{
    NSMutableString *_expression;
    NSMutableString *_exp_to_calc;
    NSMutableString *_mem;
    bool mr;
}

@property (retain, nonatomic) IBOutlet UILabel *display;
- (IBAction)digitPressed:(id)sender;
- (IBAction)Clear:(id)sender;
- (IBAction)Pop:(id)sender;
- (IBAction)Equal:(id)sender;
- (IBAction)returnMem:(id)sender;
@end
