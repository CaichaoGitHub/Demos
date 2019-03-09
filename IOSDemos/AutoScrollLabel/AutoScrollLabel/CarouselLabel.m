//
//  CarouselLabel.m
//  AutoScrollLabel
//
//  Created by Caichao on 15/10/22.
//  Copyright © 2015年 Caichao. All rights reserved.
//

#import "CarouselLabel.h"

@interface CarouselLabel()

@property (nonatomic , retain) UILabel *label;

@property (nonatomic , assign) BOOL isAnimating;

@end

@implementation CarouselLabel

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.enableAutoScroll = YES;
        self.clipsToBounds = YES;
        [self addSubview:self.label];
    }
    return self;
}

- (void)dealloc
{
    [self stopAnimation];
    [self.label removeFromSuperview];
    [_label release];
    _label = nil;
    
    [super dealloc];
}

- (void)setFrame:(CGRect)frame
{
    [super setFrame:frame];
    
    [self stopAnimation];
    [self playAnimationIfNeed];
}

- (void)playAnimationIfNeed
{
    if (self.enableAutoScroll)
    {
        CGSize constrainedSize = CGSizeMake(CGFLOAT_MAX, CGRectGetHeight(self.bounds));
        CGSize preferSize = [self.label.text sizeWithFont:self.label.font
                                                 constrainedToSize:constrainedSize
                                                     lineBreakMode:self.label.lineBreakMode];
        
        if (preferSize.width > CGRectGetWidth(self.bounds))
        {

            CGRect labelFrame = self.label.frame;
            labelFrame.size.width = preferSize.width;
            self.label.frame = labelFrame;

            CGRect animateFrame = self.label.frame;
            animateFrame.origin.x -= (preferSize.width - CGRectGetWidth(self.bounds));
            
            CGFloat duration = (preferSize.width - CGRectGetWidth(self.bounds))/30;
            
            CGPoint firstPoint = CGPointMake(CGRectGetMidX(labelFrame), CGRectGetMidY(labelFrame));
            CGPoint secondPoint = CGPointMake(CGRectGetMidX(animateFrame), CGRectGetMidY(animateFrame));
            
            // if (!self.isAnimating) //
            {
                
                
                CALayer *layer = self.label.layer;
                CAKeyframeAnimation *bounceAnimation = [CAKeyframeAnimation animationWithKeyPath:@"position"];
                
                bounceAnimation.values = @[[NSValue valueWithCGPoint:firstPoint],
                                           [NSValue valueWithCGPoint:firstPoint],
                                           [NSValue valueWithCGPoint:secondPoint],
                                           [NSValue valueWithCGPoint:secondPoint],
                                           [NSValue valueWithCGPoint:firstPoint]];
                
                CGFloat duration = 5;
                CGFloat waitTime = 2;
                
                CGFloat totalDuration = duration*2 + waitTime*2;
                
                CGFloat perDura = duration / totalDuration;
                CGFloat perWait = waitTime / totalDuration;
                CGFloat per0 = 0;
                CGFloat per1 = perWait;
                CGFloat per2 = per1+perDura;
                CGFloat per3 = per2 + perWait;
                CGFloat per4 = per3 + perDura;
                
                bounceAnimation.keyTimes = @[[NSNumber numberWithFloat:per0],
                                             [NSNumber numberWithFloat:per1],
                                             [NSNumber numberWithFloat:per2],
                                             [NSNumber numberWithFloat:per3],
                                             [NSNumber numberWithFloat:per4]];
                
                bounceAnimation.repeatCount = NSIntegerMax;
                bounceAnimation.duration = totalDuration;
                bounceAnimation.autoreverses = NO;
                
                //bounceAnimation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
                [layer addAnimation:bounceAnimation forKey:@"bounceAnimation"];
                
                
                
            }
            
        }
    }
}

- (void)stopAnimation
{
    [self.label.layer removeAnimationForKey:@"bounceAnimation"];
    self.label.frame = self.bounds;
    self.isAnimating = NO;
}

#pragma mark - getter

- (UILabel *)label
{
    if (!_label)
    {
        _label = [[UILabel alloc] initWithFrame:self.bounds];
        _label.autoresizingMask = UIViewAutoresizingFlexibleHeight;
        _label.numberOfLines = 1;
    }
    return _label;
}

- (void)setEnableAutoScroll:(BOOL)enableAutoScroll
{
    _enableAutoScroll = enableAutoScroll;
    if (enableAutoScroll)
    {
        [self playAnimationIfNeed];
    }
    else
    {
        [self stopAnimation];
    }
}

- (void)setText:(NSString *)text
{
    self.label.text = text;
    
    [self stopAnimation];
    [self playAnimationIfNeed];
    
}

- (NSString *)text
{
    return self.label.text;
}

- (void)setTextColor:(UIColor *)textColor
{
    self.label.textColor = textColor;
}

- (UIColor *)textColor
{
    return self.label.textColor;
}

- (void)setFont:(UIFont *)font
{
    self.label.font = font;
    
    [self stopAnimation];
    [self playAnimationIfNeed];
}

- (UIFont *)font
{
    return self.label.font;
}

- (void)setTextAlignment:(NSTextAlignment)textAlignment
{
    self.label.textAlignment = textAlignment;
}

- (NSTextAlignment)textAlignment
{
    return self.label.textAlignment;
}

- (void)setLineBreakMode:(NSLineBreakMode)lineBreakMode
{
    self.label.lineBreakMode = lineBreakMode;
    
    [self stopAnimation];
    [self playAnimationIfNeed];
}

- (NSLineBreakMode)lineBreakMode
{
    return self.label.lineBreakMode;
}

@end







