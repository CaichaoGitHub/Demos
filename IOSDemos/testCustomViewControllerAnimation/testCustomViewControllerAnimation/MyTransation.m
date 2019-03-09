//
//  MyTransation.m
//  testCustomViewControllerAnimation
//
//  Created by Caichao on 15/8/15.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "MyTransation.h"

@implementation MyTransation

- (NSTimeInterval)transitionDuration:(id <UIViewControllerContextTransitioning>)transitionContext
{
    return 0.8;
}


- (void)animateTransition:(id <UIViewControllerContextTransitioning>)transitionContext
{
//    UIViewController *fromVC = [transitionContext viewControllerForKey:UITransitionContextFromViewControllerKey];
//    UIViewController *toVC = [transitionContext viewControllerForKey:UITransitionContextToViewControllerKey];
//    
//    [toVC.view setFrame:fromVC.view.frame];
//    
//    [[transitionContext containerView] addSubview:toVC.view];
//    
//    [UIView animateWithDuration:[self transitionDuration:transitionContext] animations:^{
//        
//        fromVC.view.backgroundColor = [UIColor redColor];
//        toVC.view.backgroundColor = [UIColor blueColor];
//        
//    } completion:^(BOOL finished) {
//        
//        [fromVC.view removeFromSuperview];
//        
//        [transitionContext completeTransition:![transitionContext transitionWasCancelled]];
//        
//    }];
    
    // 1. Get controllers from transition context
    UIViewController *toVC = [transitionContext viewControllerForKey:UITransitionContextToViewControllerKey];
    
    // 2. Set init frame for toVC
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    CGRect finalFrame = [transitionContext finalFrameForViewController:toVC];
    toVC.view.frame = CGRectOffset(finalFrame, 0, screenBounds.size.height);
    
    // 3. Add toVC's view to containerView
    UIView *containerView = [transitionContext containerView];
    [containerView addSubview:toVC.view];
    
    // 4. Do animate now
    NSTimeInterval duration = [self transitionDuration:transitionContext];
    [UIView animateWithDuration:duration
                          delay:0.0
         usingSpringWithDamping:0.6
          initialSpringVelocity:0.0
                        options:UIViewAnimationOptionCurveLinear
                     animations:^{
                         toVC.view.frame = finalFrame;
                     } completion:^(BOOL finished) {
                         // 5. Tell context that we completed.
                         [transitionContext completeTransition:YES];
                     }];
    
}

- (void)animationEnded:(BOOL) transitionCompleted
{
    NSLog(@"animationEnded %d",transitionCompleted);
}


@end
