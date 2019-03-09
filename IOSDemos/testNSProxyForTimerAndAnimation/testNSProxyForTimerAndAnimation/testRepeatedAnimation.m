//
//  testRepeatedAnimation.m
//  testNSProxyForTimerAndAnimation
//
//  Created by Caichao on 15/4/28.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "testRepeatedAnimation.h"

@interface testRepeatedAnimation()

@property (nonatomic , retain) UIView *view;

@end

@implementation testRepeatedAnimation

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        [self showRepeatedAnimation];
    }
    return self;
}

- (void)showRepeatedAnimation
{
    if (!_view)
    {
        _view = [[UIView alloc] initWithFrame:self.bounds];
        [self.view setBackgroundColor:[UIColor redColor]];
        [self addSubview:self.view];
    }
    self.view.transform = CGAffineTransformMakeScale(1, 1);

    [UIView animateWithDuration:3 delay:0.0
                        options:0
                     animations:^{
                         
                         self.view.transform = CGAffineTransformMakeScale(1.5, 1.5);
        
    } completion:^(BOOL finished) {
        [self performSelector:@selector(showLog) withObject:nil afterDelay:5];
    }];
}

- (void)showLog
{
    NSLog(@"showLog");
}

- (void)dealloc
{
    NSLog(@"testRepeatedAnimation dealloc");
    [super dealloc];
}

@end
