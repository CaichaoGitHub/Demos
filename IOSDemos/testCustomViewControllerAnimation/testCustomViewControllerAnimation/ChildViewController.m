//
//  ChildViewController.m
//  testCustomViewControllerAnimation
//
//  Created by Caichao on 15/8/15.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "ChildViewController.h"
#import "MyTransation.h"
#import "MyPercentDrivenInteractiveTransition.h"
#import "NormalDismissAnimation.h"

@interface ChildViewController ()<UIAdaptivePresentationControllerDelegate>

@property (nonatomic , strong) MyTransation *trans;

@property (nonatomic , strong) MyPercentDrivenInteractiveTransition *percentTransition;

@property (nonatomic , strong) NormalDismissAnimation *normalTransition;

@end

@implementation ChildViewController

- (MyTransation *)trans
{
    if (!_trans)
    {
        _trans = [[MyTransation alloc] init];
    }
    return _trans;
}

- (MyPercentDrivenInteractiveTransition *)percentTransition
{
    if (!_percentTransition)
    {
        _percentTransition = [[MyPercentDrivenInteractiveTransition alloc] init];
    }
    return _percentTransition;
}

- (NormalDismissAnimation *)normalTransition
{
    if (!_normalTransition)
    {
        _normalTransition = [NormalDismissAnimation new];
    }
    return _normalTransition;
}

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        self.transitioningDelegate = self; //delegate指向自己
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.percentTransition wireToViewController:self];
    
    self.view.backgroundColor = [UIColor greenColor];
    
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeContactAdd];
    [btn setFrame:CGRectMake(100, 100, 100, 100)];
    [self.view addSubview:btn];
    [btn addTarget:self action:@selector(showClone) forControlEvents:UIControlEventTouchUpInside];
}

- (void)showClone
{
    [self dismissViewControllerAnimated:YES completion:nil];
//    [self presentViewController:vc animated:YES completion:^{
//        
//    }];
}

- (id <UIViewControllerAnimatedTransitioning>)animationControllerForPresentedController:(UIViewController *)presented presentingController:(UIViewController *)presenting sourceController:(UIViewController *)source
{
    return self.trans;
}

/**
 *  必须实现该接口 才能 使用 percentDriven,否则系统只会使用自己的动画
 *  动画transition 中的视图层次控制 对动画结束状态很重要
 *
 */
- (id <UIViewControllerAnimatedTransitioning>)animationControllerForDismissedController:(UIViewController *)dismissed
{
    return self.normalTransition;
}

//- (id <UIViewControllerInteractiveTransitioning>)interactionControllerForPresentation:(id <UIViewControllerAnimatedTransitioning>)animator
//{
//    return self.percentTransition.interacting ? self.percentTransition : nil;
//}

- (id<UIViewControllerInteractiveTransitioning>)interactionControllerForDismissal:(id<UIViewControllerAnimatedTransitioning>)animator
{
    return self.percentTransition.interacting ? self.percentTransition : nil;
}

//- (id <UIViewControllerInteractiveTransitioning>)interactionControllerForDismissal:(id <UIViewControllerAnimatedTransitioning>)animator
//{
//    return self.percentTransition.interacting ? self.percentTransition : nil;
//}

- (UIPresentationController *)presentationControllerForPresentedViewController:(UIViewController *)presented presentingViewController:(UIViewController *)presenting sourceViewController:(UIViewController *)source
{
    UIPresentationController *pre = [[UIPresentationController alloc] initWithPresentedViewController:presented presentingViewController:presenting];
    pre.delegate = self;
    return pre;
}

/* For iOS8.0, the only supported adaptive presentation styles are UIModalPresentationFullScreen and UIModalPresentationOverFullScreen. */
- (UIModalPresentationStyle)adaptivePresentationStyleForPresentationController:(UIPresentationController *)controller
{
    return UIModalPresentationOverFullScreen;
}

// Returning UIModalPresentationNone will indicate that an adaptation should not happen.
- (UIModalPresentationStyle)adaptivePresentationStyleForPresentationController:(UIPresentationController *)controller traitCollection:(UITraitCollection *)traitCollection
{
    return UIModalPresentationOverFullScreen;
}

/* If this method is not implemented, or returns nil, then the originally presented view controller is used. */
- (UIViewController *)presentationController:(UIPresentationController *)controller viewControllerForAdaptivePresentationStyle:(UIModalPresentationStyle)style
{
    return nil;
}

// If there is no adaptation happening and an original style is used UIModalPresentationNone will be passed as an argument.
- (void)presentationController:(UIPresentationController *)presentationController willPresentWithAdaptiveStyle:(UIModalPresentationStyle)style transitionCoordinator:(id <UIViewControllerTransitionCoordinator>)transitionCoordinator
{
    /**
     *  动画block,可以增加除系统动画之外的动画
     */
    [transitionCoordinator animateAlongsideTransition:^(id<UIViewControllerTransitionCoordinatorContext> context) {
        
        UIView *view = [context viewForKey:UITransitionContextToViewKey];
        view.backgroundColor = [UIColor redColor];
        view.alpha = 0.5;
        
        view.frame = CGRectMake(0, 0, 200, 200);
        
//        if ([context isAnimated])
//        {
//            UIView *view = [context viewForKey:UITransitionContextToViewKey];
//            [UIView animateWithDuration:3 animations:^{
//               
//                
//                
//            }];
//        }
        
    } completion:^(id<UIViewControllerTransitionCoordinatorContext> context) {
        
    }];
}


@end
