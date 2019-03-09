//
//  ViewController.m
//  testNSProxyForTimerAndAnimation
//
//  Created by Caichao on 15/4/28.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "ViewController.h"
#import "testRepeatedAnimation.h"
#import "testRepeadtedTimer.h"
#import "testGCDQueue.h"

@interface ViewController ()

@property (nonatomic ,retain)testRepeatedAnimation *repeatedAnimation;

@property (nonatomic ,retain)UIView *testView1;

@property (nonatomic ,retain)testGCDQueue *queue;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIButton *show = [[UIButton alloc] initWithFrame:CGRectMake(0, CGRectGetMaxY(self.view.bounds) - 100, 100, 100)];
    [show setTitle:@"init" forState:UIControlStateNormal];
    [show setBackgroundColor:[UIColor purpleColor]];
    [show addTarget:self action:@selector(show) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:show];
    
    UIButton *hide = [[UIButton alloc] initWithFrame:CGRectMake(200, CGRectGetMaxY(self.view.bounds) - 100, 100, 100)];
    [hide setBackgroundColor:[UIColor blueColor]];
    [hide setTitle:@"dealloc" forState:UIControlStateNormal];
    [hide addTarget:self action:@selector(hide) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:hide];
}

- (void)show
{
    self.testView1 = [[[UIView alloc] initWithFrame:CGRectMake(0, 50, 100, 100)] autorelease];
    [self.view addSubview:self.testView1];
    
    testRepeatedAnimation *tt = [[[testRepeatedAnimation alloc] initWithFrame:self.testView1.bounds] autorelease];
    [self.testView1 addSubview:tt];
    
//    testRepeadtedTimer *t = [[[testRepeadtedTimer alloc] initWithFrame:self.testView1.bounds] autorelease];
//    [self.testView1 addSubview:t];
    
    
//    self.queue = [[[testGCDQueue alloc] initWithFrame:self.testView1.bounds] autorelease];
//    [self.testView1 addSubview:self.queue];
}

- (void)hide
{
    [self.testView1 removeFromSuperview];
    self.testView1 = nil;
    self.queue = nil;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
