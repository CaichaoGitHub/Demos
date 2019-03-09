//
//  ViewController.m
//  testStudyStoryBoard
//
//  Created by Caichao on 15/4/21.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (retain, nonatomic) IBOutlet UIImageView *weatherImageView;
@property (retain, nonatomic) IBOutlet UILabel     *cityLabel;
@property (retain, nonatomic) IBOutlet UILabel     *temperatureLable;

@end

@implementation ViewController

- (id)init
{
    self = [super init];
    return self;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    return self;
}

- (void)loadView
{
    [super loadView];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.weatherImageView.alpha = 0.0f;
    self.cityLabel.alpha        = 0.0f;
    self.temperatureLable.alpha = 0.0f;
    
    [UIView animateWithDuration:1.5 animations:^{
        self.weatherImageView.alpha = 1.0f;
        self.cityLabel.alpha        = 1.0f;
        self.temperatureLable.alpha = 1.0f;
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc
{
    [_weatherImageView release];
    [_cityLabel release];
    [_temperatureLable release];
    
    
    [super dealloc];
}
@end
