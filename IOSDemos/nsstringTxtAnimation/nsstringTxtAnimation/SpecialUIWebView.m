//
//  SpecialUIWebView.m
//  nsstringTxtAnimation
//
//  Created by Caichao on 16/3/14.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#import "SpecialUIWebView.h"

@interface SpecialUIWebView()

@property (nonatomic , retain) UIWebView *webView;

@end

@implementation SpecialUIWebView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.webView = [[UIWebView alloc] initWithFrame:self.bounds];
        [self addSubview:self.webView];
        [self.webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"HTTP://BAIDU.COM"]]];
        
        UIView *view = [[UIView alloc] initWithFrame:CGRectMake(50, 50, 50, 50)];
        view.backgroundColor = [UIColor redColor];
        [self.webView.scrollView addSubview:view];
        
    }
    return self;
}

@end
