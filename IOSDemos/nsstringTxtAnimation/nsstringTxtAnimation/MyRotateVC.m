//
//  MyRotateVC.m
//  nsstringTxtAnimation
//
//  Created by Caichao on 16/3/14.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#import "MyRotateVC.h"
#import "MyWindow.h"

@interface AAAUIViewController : UIViewController

@end

@implementation AAAUIViewController

- (UIInterfaceOrientationMask)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskAllButUpsideDown;
}

@end


@interface MyRotateVC()

@property (nonatomic , strong) UIWindow *maskWindow;

@end

@implementation MyRotateVC

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor redColor];
    
    UITextField *textFiedl= [[UITextField alloc] initWithFrame:CGRectMake(50, 50, 100, 50)];
    textFiedl.backgroundColor = [UIColor blueColor];
    
    [self.view addSubview:textFiedl];
    
    //[self createAWindow];
}

- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation
{
    return UIInterfaceOrientationLandscapeRight;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskLandscapeLeft|UIInterfaceOrientationMaskLandscapeRight;
}

- (BOOL)prefersStatusBarHidden
{
    return NO;
}

- (BOOL)shouldAutorotate
{
    return YES;
}

- (void)createAWindow
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        
        // Mask Window
        self.maskWindow = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
        self.maskWindow.windowLevel = UIWindowLevelStatusBar + 1;
        self.maskWindow.userInteractionEnabled = NO;
        self.maskWindow.hidden = NO;
        self.maskWindow.backgroundColor = [[UIColor blueColor] colorWithAlphaComponent:0.3];
        
        AAAUIViewController *sbViewController = [[[AAAUIViewController alloc] init] autorelease];
        self.maskWindow.rootViewController = sbViewController;
    });

}

@end
















