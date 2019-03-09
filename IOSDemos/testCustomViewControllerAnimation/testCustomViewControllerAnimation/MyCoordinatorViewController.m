//
//  MyCoordinatorViewController.m
//  testCustomViewControllerAnimation
//
//  Created by Caichao on 16/3/19.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#import "MyCoordinatorViewController.h"
#import "MyPresentationController.h"

@interface MyCoordinatorViewController()<UIViewControllerTransitioningDelegate,UIAdaptivePresentationControllerDelegate>

@property (nonatomic , retain) UIView *bbView;

@end

@implementation MyCoordinatorViewController

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        //self.view.alpha = 0.0f;
        self.view.backgroundColor = [UIColor redColor];
        self.transitioningDelegate = self;
        self.modalPresentationStyle = UIModalPresentationCustom;
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    _bbView = [[UIView alloc] initWithFrame:CGRectMake(100, 100, 100, 100)];
    _bbView.backgroundColor = [UIColor blueColor];
    _bbView.alpha = 0.0f;
    [self.view addSubview:_bbView];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    /**
     *  使用Coordinator可以在整个viewcontroller转场动画中增加一些你自己的额外的视图元素的动画
     */
    [self.transitionCoordinator animateAlongsideTransition:^(id<UIViewControllerTransitionCoordinatorContext>  _Nonnull context) {
        //self.view.alpha = 1.0f;
        _bbView.alpha = 1.0f;
    } completion:^(id<UIViewControllerTransitionCoordinatorContext>  _Nonnull context) {
        NSLog(@"completion");
    }];
    
    //当手势动结束后会回调该接口
//    [self.transitionCoordinator notifyWhenInteractionEndsUsingBlock:^(id<UIViewControllerTransitionCoordinatorContext>  _Nonnull context) {
//        NSLog(@"notifyWhenInteractionEndsUsingBlock");
//    }];
}

//自定义 presentVC动画，可以在系统的默认的动画中增加自己的小动画呢
- (nullable UIPresentationController *)presentationControllerForPresentedViewController:(UIViewController *)presented presentingViewController:(UIViewController *)presenting sourceViewController:(UIViewController *)source
{
    MyPresentationController *presentVC = [[MyPresentationController alloc] initWithPresentedViewController:presented presentingViewController:presenting];
    //presentVC.delegate = self;
    return presentVC;
}

- (UIModalPresentationStyle)adaptivePresentationStyleForPresentationController:(UIPresentationController *)controller
{
    return UIModalPresentationCustom;
}

@end
