//
//  GestureView.m
//  nsstringTxtAnimation
//
//  Created by Caichao on 16/6/22.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#import "GestureView.h"

@interface GestureView()

@property (nonatomic , retain) UIView *redView;

@end

@implementation GestureView

 - (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        UIPanGestureRecognizer *pGe = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(gestureCallBack:)];
        [self addGestureRecognizer:pGe];
        
        self.redView = [[UIView alloc] initWithFrame:self.bounds];
        self.redView.backgroundColor = [UIColor redColor];
        [self addSubview:self.redView];
    }
    return self;
}

- (void)gestureCallBack:(UIPanGestureRecognizer*)gesture
{
    NSLog(@"callback");
}

@end
