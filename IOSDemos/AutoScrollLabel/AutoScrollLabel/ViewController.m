//
//  ViewController.m
//  AutoScrollLabel
//
//  Created by Caichao on 15/10/22.
//  Copyright © 2015年 Caichao. All rights reserved.
//

#import "ViewController.h"
#import "CarouselLabel.h"

@interface ViewController ()

@property (nonatomic , retain) CarouselLabel *lay;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.view setBackgroundColor:[[UIColor blueColor] colorWithAlphaComponent:0.3]];
    
    self.lay = [[[CarouselLabel alloc] initWithFrame:CGRectMake(50, 50, 100, 50)] autorelease];
    
    self.lay.backgroundColor = [UIColor blueColor];
    self.lay.textColor = [UIColor whiteColor];
    
    [self.view addSubview:self.lay];
    
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeContactAdd];
    [btn addTarget:self action:@selector(click) forControlEvents:UIControlEventTouchUpInside];
    [btn setFrame:CGRectMake(200, 100, 50, 50)];
    [self.view addSubview:btn];
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    if (toInterfaceOrientation == UIInterfaceOrientationPortrait)
    {
        self.lay.frame = CGRectMake(50, 50, 100, 50);
    }
    else
    {
        self.lay.frame = CGRectMake(50, 50, 50, 100);
    }
}


static int counter;

- (void)click
{
    int indx = counter++%4;
    switch (indx)
    {
        case 0:
            self.lay.text = @"Copyright © 2015年 Caichao. All rights reserved.";
            break;
//        case 1:
//            self.lay.text = @"Copyright2015";
//            break;
//        case 2:
//            self.lay.text = @"南安普敦Southampton FC ：圣玛丽球场南安普敦Southampton FC ：圣玛丽球场南安普敦Southampton FC ：圣玛丽球场南安普敦Southampton FC ：圣玛丽球场南安普敦Southampton FC ：圣玛丽球场南安普敦Southampton FC ：圣玛丽球场南安普敦Southampton FC ：圣玛丽球场南安普敦Southampton FC ：圣玛丽球场南安普敦Southampton FC ：圣玛丽球场";
//            break;
        case 3:
            //self.lay.enableAutoScroll = NO;
            [self.lay removeFromSuperview];
            self.lay = nil;
            break;
            
        default:
            break;
    }
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
