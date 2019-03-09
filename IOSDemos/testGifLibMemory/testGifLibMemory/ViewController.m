//
//  ViewController.m
//  testGifLibMemory
//
//  Created by Caichao on 15/4/23.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "ViewController.h"
#import "FLAnimatedImageView.h"
#import "FLAnimatedImage.h"
#import "UIImage+GIF.h"
#import <ImageIO/ImageIO.h>

@interface ViewController ()

@property (nonatomic) FLAnimatedImageView *imageView1;

@property (nonatomic) UIView *animateView;

@property (nonatomic , strong) NSMutableArray *views;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    UIScrollView *scrollView = [[UIScrollView alloc] initWithFrame:self.view.bounds];
    self.view = scrollView;
    [scrollView setContentSize:CGSizeMake(CGRectGetWidth(self.view.bounds), CGRectGetHeight(self.view.bounds) + 100)];
    scrollView.backgroundColor = [UIColor purpleColor];
    scrollView.alwaysBounceVertical = YES;
    scrollView.bounces = YES;
    scrollView.scrollEnabled = YES;
    
    
    
//    if (!self.imageView1) {
//        self.imageView1 = [[FLAnimatedImageView alloc] init];
//        self.imageView1.contentMode = UIViewContentModeScaleAspectFill;
//        self.imageView1.clipsToBounds = YES;
//    }
//    [self.view addSubview:self.imageView1];
//    self.imageView1.frame = CGRectMake(0.0, 120.0, self.view.bounds.size.width, 447.0);
//    
//    NSURL *url1 = [[NSBundle mainBundle] URLForResource:@"max" withExtension:@"gif"];
//    NSData *data1 = [NSData dataWithContentsOfURL:url1];
    //FLAnimatedImage *animatedImage1 = [FLAnimatedImage animatedImageWithGIFData:data1];
    //self.imageView1.animatedImage = animatedImage1;
    
   // UIImageView *view = [[UIImageView alloc] initWithFrame:CGRectMake(0.0, 120.0, self.view.bounds.size.width, 447.0)];
   // [self.view addSubview:view];
    
    //view.image = [UIImage sd_animatedGIFWithData:data1];
    
//    int wC = 1;
//    int hC = 1;
//    
//    double width = (CGRectGetWidth(self.view.bounds))/wC;
//    double height = (CGRectGetHeight(self.view.bounds))/hC;
//    
//    for (int i = 0; i < wC; i++)
//    {
//        for (int j = 0; j < hC; j++)
//        {
//            FLAnimatedImageView *imageView = [[FLAnimatedImageView alloc] initWithFrame:CGRectMake(width*i, height*j, width, height)];
//            [self.view addSubview:imageView];
//            NSURL *url1 = [[NSBundle mainBundle] URLForResource:@"max" withExtension:@"gif"];
//            NSData *data1 = [NSData dataWithContentsOfURL:url1];
//            FLAnimatedImage *animatedImage = [FLAnimatedImage animatedImageWithGIFData:data1];
//            imageView.animatedImage = animatedImage;
//        }
//    }
    
    UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(0, CGRectGetHeight(self.view.bounds), 100, 50)];
    [btn setBackgroundColor:[UIColor redColor]];
    [btn setTitle:@"remove" forState:UIControlStateNormal];
    [self.view addSubview:btn];
    [btn addTarget:self action:@selector(removeAllViews) forControlEvents:UIControlEventTouchUpInside];
    
    UIButton *btn1 = [[UIButton alloc] initWithFrame:CGRectMake(200, CGRectGetHeight(self.view.bounds), 100, 50)];
    [btn1 setBackgroundColor:[UIColor redColor]];
    [btn1 setTitle:@"add" forState:UIControlStateNormal];
    [self.view addSubview:btn1];
    [btn1 addTarget:self action:@selector(addTestViews) forControlEvents:UIControlEventTouchUpInside];

//    for (int i = 0; i < 4; i++)
//    {
//        for (int j = 0; j < 6; j++)
//        {
//            UIImageView *imageView = [[UIImageView alloc] initWithFrame:CGRectMake(width*i, height*j, width, height)];
//            [self.view addSubview:imageView];
//            NSURL *url1 = [[NSBundle mainBundle] URLForResource:@"max" withExtension:@"gif"];
//            NSData *data1 = [NSData dataWithContentsOfURL:url1];
//            imageView.image = [UIImage sd_animatedGIFWithData:data1];
//        }
//    }
    
    
    UIView *testView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
    [testView setBackgroundColor:[UIColor blackColor]];
    [self.view addSubview:testView];
    
    UIView *mmView = [[UIView alloc] initWithFrame:CGRectMake(50, 50, 300, 300)];
    [mmView setBackgroundColor:[UIColor redColor]];
    //[self.view addSubview:mmView];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        
        [UIView transitionFromView:testView
                            toView:mmView
                          duration:2
                           options:UIViewAnimationOptionTransitionCurlUp
                        completion:^(BOOL finished) {
                            
                            NSLog(@"abcdefg = %@  defhigk = %@",mmView.superview,testView.superview);
        }];
        
//        [UIView transitionWithView:self.view duration:2 options:UIViewAnimationOptionTransitionCurlUp animations:^{
//            
//            [self.view addSubview:mmView];
//            
//        } completion:^(BOOL finished) {
//            
//        }];
        
    });
}

- (void)addTestViews
{
    self.views = [[NSMutableArray alloc] init];
    int wC = 1;
    int hC = 1;
    
    double width = (CGRectGetWidth(self.view.bounds))/wC;
    double height = (CGRectGetHeight(self.view.bounds))/hC;
    
    for (int i = 0; i < wC; i++)
    {
        for (int j = 0; j < hC; j++)
        {
            FLAnimatedImageView *imageView = [[FLAnimatedImageView alloc] initWithFrame:CGRectMake(width*i, height*j, width, height)];
            [self.view addSubview:imageView];
            NSURL *url1 = [[NSBundle mainBundle] URLForResource:@"max" withExtension:@"gif"];
            NSData *data1 = [NSData dataWithContentsOfURL:url1];
            FLAnimatedImage *animatedImage = [FLAnimatedImage animatedImageWithGIFData:data1];
            imageView.animatedImage = animatedImage;
            [self.views addObject:imageView];
        }
    }
    
}

- (void)removeAllViews
{
    for (UIView *view in self.views)
    {
        ((FLAnimatedImageView*)view).animatedImage = nil;
    }
    //[self.views removeAllObjects];
}

- (float)sd_frameDurationAtIndex:(NSUInteger)index source:(CGImageSourceRef)source {
    float frameDuration = 0.1f;
    CFDictionaryRef cfFrameProperties = CGImageSourceCopyPropertiesAtIndex(source, index, nil);
    NSDictionary *frameProperties = (__bridge NSDictionary *)cfFrameProperties;
    NSDictionary *gifProperties = frameProperties[(NSString *)kCGImagePropertyGIFDictionary];
    
    NSNumber *delayTimeUnclampedProp = gifProperties[(NSString *)kCGImagePropertyGIFUnclampedDelayTime];
    if (delayTimeUnclampedProp) {
        frameDuration = [delayTimeUnclampedProp floatValue];
    }
    else {
        
        NSNumber *delayTimeProp = gifProperties[(NSString *)kCGImagePropertyGIFDelayTime];
        if (delayTimeProp) {
            frameDuration = [delayTimeProp floatValue];
        }
    }
    
    // Many annoying ads specify a 0 duration to make an image flash as quickly as possible.
    // We follow Firefox's behavior and use a duration of 100 ms for any frames that specify
    // a duration of <= 10 ms. See <rdar://problem/7689300> and <http://webkit.org/b/36082>
    // for more information.
    
    if (frameDuration < 0.011f) {
        frameDuration = 0.100f;
    }
    
    CFRelease(cfFrameProperties);
    return frameDuration;
}

- (void)test
{
    
    NSURL *url1 = [[NSBundle mainBundle] URLForResource:@"max" withExtension:@"gif"];
    NSData *data1 = [NSData dataWithContentsOfURL:url1];
    CGImageSourceRef source = CGImageSourceCreateWithData((__bridge CFDataRef)data1, NULL);
    
    size_t count = CGImageSourceGetCount(source);
    
    UIImage *animatedImage;
    
    if (count <= 1) {
        animatedImage = [[UIImage alloc] initWithData:data1];
    }
    else {
        NSMutableArray *images = [NSMutableArray array];
        
        NSMutableArray *frameDelayTimes = [NSMutableArray array];
        
        NSTimeInterval duration = 0.0f;
        
        for (size_t i = 0; i < count; i++) {
            CGImageRef image = CGImageSourceCreateImageAtIndex(source, i, NULL);
            
            float dur = [self sd_frameDurationAtIndex:i source:source];
            
            [frameDelayTimes addObject:@(dur)];
            
            duration += dur;
            
            UIImage *image1 = [UIImage imageWithCGImage:image scale:[UIScreen mainScreen].scale orientation:UIImageOrientationUp];
            
            [images addObject:image1];
            
            CGImageRelease(image);
        }
        
        if (!duration) {
            duration = (1.0f / 10.0f) * count;
        }
        
       // animatedImage = [UIImage animatedImageWithImages:images duration:duration];
        

        CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:@"contents"];
        
        NSMutableArray *times = [NSMutableArray arrayWithCapacity:[images count]];
        CGFloat currentTime = 0;
        int count = frameDelayTimes.count;
        for (int i = 0; i < count; ++i) {
            [times addObject:[NSNumber numberWithFloat:(currentTime / duration)]];
            currentTime += [[frameDelayTimes objectAtIndex:i] floatValue];
        }
        [animation setKeyTimes:times];
        
//        NSMutableArray *images = [NSMutableArray arrayWithCapacity:3];
//        for (int i = 0; i < count; ++i) {
//            [images addObject:[_frames objectAtIndex:i]];
//        }
        
        [animation setValues:images];
        [animation setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear]];
        animation.duration = duration;
        //animation.delegate = self;
        animation.repeatCount = 5;
        
        [self.animateView.layer addAnimation:animation forKey:@"gifAnimation"];
        
    }
    
    CFRelease(source);
    
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
