//
//  TestVolumeViewController.m
//  nsstringTxtAnimation
//
//  Created by Caichao on 16/3/21.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#import "TestVolumeViewController.h"
#import <AVFoundation/AVFoundation.h>
#import <MediaPlayer/MediaPlayer.h>


@implementation TestVolumeViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor redColor];
    
    MPVolumeView *volume = [[MPVolumeView alloc] initWithFrame:CGRectMake(100, 100, 100, 100)];
    volume.backgroundColor = [UIColor blueColor];
    [self.view addSubview:volume];
}

@end
