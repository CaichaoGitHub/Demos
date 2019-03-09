//
//  ViewController.m
//  testCustomViewControllerAnimation
//
//  Created by Caichao on 15/8/7.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "ViewController.h"
#import "ChildViewController.h"
#import "MyCoordinatorViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setBackgroundColor:[UIColor yellowColor]];
    [btn setFrame:CGRectMake(100, 100, 50, 50)];
    [btn addTarget:self action:@selector(btnClicked) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
    
}

- (void)btnClicked
{
    ChildViewController *vc = [[ChildViewController alloc] init];
    vc.modalPresentationStyle = UIModalPresentationCustom;
    self.transitioningDelegate = vc;
    //[self addChildViewController:vc];
    //[self presentViewController:vc animated:YES completion:nil];
    
    MyCoordinatorViewController *coor = [MyCoordinatorViewController new];
    [self presentViewController:coor animated:YES completion:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



@end
