//
//  MyPercentDrivenInteractiveTransition.h
//  testCustomViewControllerAnimation
//
//  Created by Caichao on 15/8/20.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MyPercentDrivenInteractiveTransition : UIPercentDrivenInteractiveTransition

@property (nonatomic, assign) BOOL interacting;
- (void)wireToViewController:(UIViewController*)viewController;

@end
