//
//  CarouselLabel.h
//  AutoScrollLabel
//
//  Created by Caichao on 15/10/22.
//  Copyright © 2015年 Caichao. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CarouselLabel : UIView

/**
 *  是否播放动画
 */
@property (nonatomic , assign) BOOL enableAutoScroll;

@property (nonatomic , retain) NSString *text;

@property (nonatomic , retain) UIColor *textColor;

@property (nonatomic , retain) UIFont *font;

@property (nonatomic , assign) NSTextAlignment textAlignment;

@property (nonatomic , assign) NSLineBreakMode lineBreakMode;

@end
