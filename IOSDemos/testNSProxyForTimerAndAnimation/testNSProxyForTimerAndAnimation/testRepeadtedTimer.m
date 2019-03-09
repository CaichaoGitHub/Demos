//
//  testRepeadtedTimer.m
//  testNSProxyForTimerAndAnimation
//
//  Created by Caichao on 15/4/28.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "testRepeadtedTimer.h"
#import "MyWeakProxy.h"

@implementation testRepeadtedTimer

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        MyWeakProxy *proxy = [MyWeakProxy weakProxyForObject:self];
        [NSTimer scheduledTimerWithTimeInterval:2
                                         target:proxy
                                       selector:@selector(showLog)
                                       userInfo:nil repeats:YES];
    }
    
    return self;
}

- (void)showLog
{
    NSLog(@"showLog");
}

- (void)dealloc
{
    NSLog(@"testRepeadtedTimer dealloc");
    [super dealloc];
}

@end
