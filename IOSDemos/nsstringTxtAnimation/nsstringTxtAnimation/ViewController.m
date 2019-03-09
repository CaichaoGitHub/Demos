//
//  ViewController.m
//  nsstringTxtAnimation
//
//  Created by Caichao on 16/2/22.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#import "ViewController.h"
#import "MyViewController.h"
#import <AVFoundation/AVFoundation.h>
#import <AVKit/AVKit.h>
#import "AVPlayerDemoPlaybackViewController.h"
#import "AVPlayerDemoPlaybackView.h"
#import <Foundation/Foundation.h>
#import "MyWorkerClass.h"
#import "UIViewController+xxx.h"
#import "MyRotateVC.h"
#import "SpecialUIWebView.h"
#import "TestVolumeViewController.h"
#import "RotateViewController.h"
#import "GestureView.h"

NSString * const kTracksKey         = @"tracks";
NSString * const kPlayableKey		= @"playable";
NSString * const kCommonMetadataKey = @"commonMetadata";
NSString * const kDurationKey       = @"duration";

@interface TestView : UIView

@property (nonatomic , retain) NSString *text;
@property (nonatomic , retain) UIFont *font;
//@property (nonatomic , retain) UIColor *bkColor;
@property (nonatomic , retain) UIColor *topColor;
@property (nonatomic , retain) UIColor *bottomColor;
@property (nonatomic , assign) CGSize textPreferSize;

@end

@implementation TestView

- (id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame])
    {
        self.backgroundColor = [UIColor clearColor];
        self.topColor = [[UIColor redColor] colorWithAlphaComponent:0.1];
        self.bottomColor = [UIColor redColor];
    }
    return self;
}

- (void)setText:(NSString *)text
{
    if (_text != text)
    {
        [_text release];
        _text = [text retain];
        self.textPreferSize = [self preferedTextCGSize:text font:self.font width:CGFLOAT_MAX];
    }
}

- (CGSize)preferedTextCGSize:(NSString *)text font:(UIFont *)font width:(CGFloat)width
{
    CGSize containerSize = CGSizeMake(width, CGFLOAT_MAX);
    CGSize fitSize = CGSizeZero;
    fitSize = [text boundingRectWithSize:containerSize options:NSStringDrawingUsesFontLeading|NSStringDrawingTruncatesLastVisibleLine|NSStringDrawingUsesLineFragmentOrigin attributes:@{NSFontAttributeName:font} context:NULL].size;
    
    return  fitSize;
}

- (void)drawRect:(CGRect)rect
{
    CGColorSpaceRef baseSpace = CGColorSpaceCreateDeviceRGB();
    CGColorRef ref[2] = {self.topColor.CGColor,self.bottomColor.CGColor};
    CFArrayRef array = CFArrayCreate(NULL, (void *)ref, 2, NULL);
    CGGradientRef gradient = CGGradientCreateWithColors(baseSpace, array, NULL);
    CFRelease(array), array = NULL;
    CGColorSpaceRelease(baseSpace), baseSpace = NULL;
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSaveGState(context);

    CGPoint startPoint = CGPointMake(CGRectGetMidX(rect), CGRectGetMinY(rect));
    CGPoint endPoint = CGPointMake(CGRectGetMidX(rect), CGRectGetMaxY(rect));
    
    CGContextDrawLinearGradient(context, gradient, startPoint, endPoint, 0);
    CGGradientRelease(gradient), gradient = NULL;
    
    CGContextSetBlendMode(context, kCGBlendModeDestinationOut); // R = D*(1-sa)
    [self.text drawAtPoint:CGPointMake(CGRectGetMidX(rect) - self.textPreferSize.width/2, CGRectGetMidY(rect) - self.textPreferSize.height) withAttributes:@{NSFontAttributeName:self.font}];
    
    CGContextRestoreGState(context);
}

@end

@interface VVView : UIView

@end

@implementation VVView

- (void)drawRect:(CGRect)rect
{
    [[UIColor redColor] setFill];
    
    CGFloat width = CGRectGetWidth(self.bounds);
    CGFloat height = CGRectGetHeight(self.bounds);
    CGFloat radius = width > height ? height/2 : width/2;
    [[UIBezierPath bezierPathWithRoundedRect:self.bounds cornerRadius:radius] fill];
}

@end


@interface ViewController ()<AVAssetResourceLoaderDelegate,NSPortDelegate>

@property (nonatomic , retain) UIWindow *tpwindow;

@property (nonatomic , retain) AVURLAsset *asset;

@property (nonatomic , retain) AVPlayer *player;
@property (nonatomic , retain) AVPlayerItem *playerItem;

@property (nonatomic , retain) AVPlayerDemoPlaybackView *playBackView;

@property (nonatomic , assign) BOOL abcd;

@property (nonatomic , retain) UITapGestureRecognizer *singleGesture;
@property (nonatomic , retain) UITapGestureRecognizer *doubleGesture;

@end

@implementation ViewController

- (void)singleGestureCallback
{
    NSLog(@"singleGestureCallback");
}

- (void)doubleGestureCallback
{
    NSLog(@"doubleGestureCallback");
}

- (void)myLable
{
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 100, 100, 100)];
    label.backgroundColor = [[UIColor blueColor] colorWithAlphaComponent:0.3];
    //label.text = @"中文的哦";
//    label.textColor = [UIColor redColor];
//    label.textAlignment = NSTextAlignmentCenter;
//    label.font = [UIFont italicSystemFontOfSize:10];
    [self.view addSubview:label];
    
    NSString *text = @"中文的哦";
    NSMutableAttributedString *mutableAttributedString = [[NSMutableAttributedString alloc] initWithString:text];
    [mutableAttributedString addAttribute:NSForegroundColorAttributeName
                                    value:[UIColor redColor]
                                    range:NSMakeRange(0, text.length)];
    
    UIFont *font = [UIFont fontWithName:@"PingFangSC-Semibold" size:13];
    if (!font)
    {
        font = [UIFont fontWithName:@"STHeitiSC-Medium" size:13];
    }
    //CGAffineTransform matrix = CGAffineTransformMake(1, 0, tanf(kFontAngle * (CGFloat)M_PI / 180), 1, 0, 0);
    //UIFontDescriptor *desc = [font.fontDescriptor fontDescriptorWithMatrix:matrix];
    //font = [UIFont fontWithDescriptor:desc size:kFontSize];
    [mutableAttributedString addAttribute:NSFontAttributeName value:font range:NSMakeRange(0, text.length)];
    [mutableAttributedString addAttribute:NSKernAttributeName value:@(3) range:NSMakeRange(0, text.length)];
    label.attributedText = mutableAttributedString;
}

- (void)volumeViewTest
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        
        TestVolumeViewController *vc = [TestVolumeViewController new];
        [self presentViewController:vc animated:YES completion:nil];
        
    });
}

- (void)buttonClicked
{
    RotateViewController *rvc = [[RotateViewController alloc] init];
    
    [self presentViewController:rvc animated:YES completion:nil];

}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self testMyVC];
    
    return ;
    
    [MyWorkerClass new];
    
    GestureView *v = [[GestureView alloc] initWithFrame:CGRectMake(100, 100, 100, 100)];
    [self.view addSubview:v];
    
    return;
    UIButton *decoV = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 100, 100)];
    decoV.backgroundColor = [UIColor redColor];
    [decoV addTarget:self action:@selector(buttonClicked) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:decoV];

    
    return;
    //[self vidoeT];
    [self testLongPressGesture];
    
    return ;
    
//    UIView *view = [[UIView alloc] initWithFrame:CGRectMake(100, 100, 100, 100)];
//    view.backgroundColor = [UIColor redColor];
//    [self.view addSubview:view];
//    
//    view.layer.shadowColor = [UIColor blackColor].CGColor;
//    view.layer.shadowOffset = CGSizeMake(-8, 0);
//    view.layer.shadowOpacity = 0.1;
    
    NSArray *colors = @[(id)[UIColor redColor].CGColor,(id)[UIColor blueColor].CGColor];
    CAGradientLayer *gLayer = [CAGradientLayer layer];
    gLayer.bounds = CGRectMake(100, 100, 100, 100);
    gLayer.startPoint = CGPointMake(0, 0.5);
    gLayer.endPoint = CGPointMake(1, 0.5);
    gLayer.colors = colors;
    [self.view.layer addSublayer:gLayer];
    
    return;
    
    [self loadVideoIndex:1];
    
    return;
    
    
    //[self testMyVC];
    
    self.singleGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(singleGestureCallback)];
    [self.view addGestureRecognizer:self.singleGesture];
    
    self.doubleGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(doubleGestureCallback)];
    self.doubleGesture.numberOfTapsRequired = 2;
    [self.view addGestureRecognizer:self.doubleGesture];
    
    [self.singleGesture requireGestureRecognizerToFail:self.doubleGesture];
    [self.doubleGesture requireGestureRecognizerToFail:self.singleGesture];
    
    [self myLable];
    
    //[self testSpecialView];
    
    [self volumeViewTest];
    
    return;
    
    self.abcd = NO;
    [self addObserver:self forKeyPath:@"abcd" options:NSKeyValueObservingOptionNew context:nil];
    
    self.abcd = NO;
    
    return;
    
    [self textMask];
    return;
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self loadVideoIndex:0];
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [self loadVideoIndex:1];
        });
        
    });
    
    return;
    
    
    NSMutableAttributedString *attr = [[NSMutableAttributedString alloc] initWithString:@"你好，中国！"];
    [attr setAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:5],NSForegroundColorAttributeName:[UIColor blueColor]} range:NSMakeRange(0, 6)];
    
    UILabel *lable = [[UILabel alloc] initWithFrame:CGRectMake(0, 50, 50, 200)];
    lable.backgroundColor = [UIColor redColor];
    lable.textColor = [UIColor blueColor];
    lable.numberOfLines = 3;
    lable.textAlignment = NSTextAlignmentCenter;
    lable.lineBreakMode = NSLineBreakByWordWrapping;
    lable.font = [UIFont boldSystemFontOfSize:10];
    //lable.attributedText = attr;
    [self.view addSubview:lable];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        
//        [UIView transitionWithView:self.view duration:2 options:UIViewAnimationOptionTransitionFlipFromTop animations:^{
//            //[attr beginEditing];
//            [attr addAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:20],NSForegroundColorAttributeName:[UIColor whiteColor]} range:NSMakeRange(0, 6)];
//            //[attr endEditing];
//            lable.attributedText = attr;
//        } completion:nil];
//        [UIView animateWithDuration:2 delay:0 options:UIViewAnimationOptionCurveEaseInOut animations:^{
//            //[attr beginEditing];
//            [attr addAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:20],NSForegroundColorAttributeName:[UIColor blackColor]} range:NSMakeRange(0, 6)];
//            //[attr endEditing];
//            lable.attributedText = attr;
//            
//        } completion:nil];
        
        // configure parentview cover the system's statusbar
        self.tpwindow = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        [self.tpwindow setRootViewController:[MyViewController new]];
        self.tpwindow.hidden = NO;
        //self.tpwindow.backgroundColor = [UIColor redColor];
        self.tpwindow.windowLevel = UIWindowLevelStatusBar + 1;
        self.tpwindow.userInteractionEnabled = YES;
        
    });
    
    NSString *xs = @"xyz ollectManager sharedInstance].loginHanl";
    NSUInteger length = [self simpleTxtBinarySearch:xs fontSize:10 maxWidth:self.view.frame.size.width];
    lable.text = xs;//[xs substringWithRange:NSMakeRange(0, length)];
    NSLog(@"%@ ---- %@",lable.text,[xs substringWithRange:NSMakeRange(length, [xs length] - length)]);
    // Do any additional setup after loading the view, typically from a nib.
    
    [UIView animateWithDuration:5 delay:3 options:0 animations:^{
        lable.transform = CGAffineTransformMakeScale(0.01, 0.01);
    } completion:^(BOOL finished) {
        lable.transform = CGAffineTransformIdentity;
        return;
    }];
    
    [self testArrayCopy];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(playerItemDidPlayToEndTimeNotification)
                                                 name:AVPlayerItemDidPlayToEndTimeNotification
                                               object:nil];

    
    //[self specialView];
    //[self vidoeT];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSString *,id> *)change context:(void *)context
{
    
}

- (void)playerItemDidPlayToEndTimeNotification
{
    dispatch_async(dispatch_get_main_queue(), ^{
        //[self loadVideoIndex:1];
    });
    
}

- (void)testArrayCopy
{
    NSMutableArray *array = [NSMutableArray arrayWithObjects:[NSObject new], nil];
    NSMutableArray *arry2 = [array copy];
    return;
}

- (void)setURL:(NSURL*)URL
{
   // if (mURL != URL)
    {
       // mURL = [URL copy];
        
        /*
         Create an asset for inspection of a resource referenced by a given URL.
         Load the values for the asset key "playable".
         */
        AVURLAsset *asset = [AVURLAsset URLAssetWithURL:URL options:nil];
        
        NSArray *requestedKeys = @[@"playable"];
        
        /* Tells the asset to load the values of any of the specified keys that are not already loaded. */
        [asset loadValuesAsynchronouslyForKeys:requestedKeys completionHandler:
         ^{
             dispatch_async( dispatch_get_main_queue(),
                            ^{
                                /* Create a new instance of AVPlayerItem from the now successfully loaded AVAsset. */
                                self.playerItem = [AVPlayerItem playerItemWithAsset:asset];
                                
                                /* Create new player, if we don't already have one. */
                                if (!self.player)
                                {
                                    /* Get a new AVPlayer initialized to play the specified player item. */
                                    [self setPlayer:[AVPlayer playerWithPlayerItem:self.playerItem]];
                                    AVPlayerViewController *vc = [[AVPlayerViewController alloc] init];
                                    vc.player = self.player;
                                    [self presentViewController:vc animated:YES completion:^{
                                        
                                    }];
                                }
                                
                                if (self.player.currentItem != self.playerItem)
                                {
                                    [self.player replaceCurrentItemWithPlayerItem:self.playerItem];
                                }
                                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                                    [self.player play];
                                });
                                
                            });
         }];
    }
}

- (void)loadVideoIndex:(NSInteger)index
{
    NSURL *url  = nil;//[NSURL URLWithString:@"http://ips.ifeng.com/video19.ifeng.com/video09/2016/02/29/3870755-102-000-2309.mp4"];
    switch (index) {
        case 0:
            url = [NSURL URLWithString:@"http://pl.youku.com/playlist/m3u8?vid=XMTQ4NjI0MTAyNA==&type=flv&ts=1456816918&keyframe=0&ep=eyaRHEGMUMcB7SLagD8bM3q2IHMNXJZ3kn6B%2F4gbAMZAOaHB6DPcqJmxSvs%3D&sid=945681691815812dfdd42&token=4144&ctype=12&ev=1&oip=244858954&uc_param_str=xk&xk=OTRkZDY0ZmFlM2RjMTM1ZV8xNDU2ODE2OTE3XzRhMGY0ZmJjMmY3NDJmZTk5MTZlZjAwMDMwNjZlZGM2"];
            break;
        case 1:
            url = [NSURL URLWithString:@"http://100.84.85.202/1.mp4"];
            break;
        default:
            break;
    }
    
    [self setURL:url];
    
    return;
    
    NSArray *requestedKeys = @[@"playable"];
    AVURLAsset *as = [AVURLAsset URLAssetWithURL:url options:nil];
    [as loadValuesAsynchronouslyForKeys:requestedKeys completionHandler:^{
        
        dispatch_async(dispatch_get_main_queue(), ^{
            
            self.playerItem = [AVPlayerItem playerItemWithAsset:as];
            [self tryPlay:self.playerItem];
        });
        
    }];
    
//    self.playerItem = [AVPlayerItem playerItemWithURL:url];
//    [self.playerItem addObserver:self forKeyPath:@"status" options:NSKeyValueObservingOptionNew context:nil];
//    [self.player replaceCurrentItemWithPlayerItem:nil];
//    [self.player replaceCurrentItemWithPlayerItem:self.playerItem];
}

- (void)tryPlay:(AVPlayerItem*)item
{
    if (!self.player)
    {
        self.player = [AVPlayer playerWithPlayerItem:item];
        AVPlayerViewController *vc = [[AVPlayerViewController alloc] init];
        vc.player = self.player;
        [self presentViewController:vc animated:YES completion:nil];
    }
    
    if (self.player.currentItem != item)
    {
        [self.player replaceCurrentItemWithPlayerItem:item];
    }
    [self.player play];
}

//- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSString *,id> *)change context:(void *)context
//{
//    NSLog(@"%@",change);
//    
//    if ([keyPath isEqualToString:@"status"])
//    {
//        //the status will callback several times , so more conditions
//        if ([[change objectForKey:NSKeyValueChangeOldKey] integerValue] != AVPlayerItemStatusReadyToPlay)
//        {
//            //[self.player play];
//        }
//    }
//    else if ([keyPath isEqualToString:@"currentItem"])
//    {
//        AVPlayerItem *newPlayerItem = [change objectForKey:NSKeyValueChangeNewKey];
//        if (newPlayerItem != nil)
//        {
//            [self.playBackView setPlayer:self.player];
//            [self.playBackView setVideoFillMode:AVLayerVideoGravityResizeAspect];
//        }
//    }
//    else
//    {
//        [super observeValueForKeyPath:keyPath
//                             ofObject:object
//                               change:change
//                              context:context];
//    }
//    
//}

- (void)vidoeT
{
    //http://v.iask.com/v_play_ipad.php?vid=139812910
    self.asset = [AVURLAsset URLAssetWithURL:[NSURL URLWithString:@"my_scheme://v.iask.com/v_play_ipad.php?vid=139812910"] options:nil];
    AVAssetResourceLoader *loder = self.asset.resourceLoader;
    [loder setDelegate:self queue:dispatch_get_main_queue()];
    [self.asset loadValuesAsynchronouslyForKeys:@[@"playable"] completionHandler:^{
        NSLog(@"loadValuesAsynchronouslyForKeys");
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [self tryPlay:[AVPlayerItem playerItemWithAsset:self.asset]];
        });

        
    }];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(15 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        //[self.asset cancelLoading];
    });
}

- (BOOL)resourceLoader:(AVAssetResourceLoader *)resourceLoader shouldWaitForLoadingOfRequestedResource:(AVAssetResourceLoadingRequest *)loadingRequest
{
    NSLog(@"shouldWaitForLoadingOfRequestedResource");
    return YES;
}


- (BOOL)resourceLoader:(AVAssetResourceLoader *)resourceLoader shouldWaitForRenewalOfRequestedResource:(AVAssetResourceRenewalRequest *)renewalRequest
{
    NSLog(@"shouldWaitForRenewalOfRequestedResource");
    return YES;
}

- (void)resourceLoader:(AVAssetResourceLoader *)resourceLoader didCancelLoadingRequest:(AVAssetResourceLoadingRequest *)loadingRequest
{
    NSLog(@"didCancelLoadingRequest");
}



- (void)specialView
{
    CGMutablePathRef path = CGPathCreateMutable();
    //把绘图信息添加到路径里
    //绘制圆形路径
    CGPoint points[5] = {{0,0},{50, 25},{50, 50},{0, 50},{0, 0}};
    CGPathAddLines(path, nil, points, 5);
    //CGPathAddArc(path, nil, pathPointArcCenter.x, pathPointArcCenter.y, radius, 0, M_PI*2, NO);
    
    CAShapeLayer *shape = [CAShapeLayer layer];
    [shape setFrame:CGRectMake(0, 0, 50, 50)];
    
//    UIBezierPath *path = [UIBezierPath bezierPath];
//    [path moveToPoint:CGPointMake(0, 0)];
//    [path addLineToPoint:CGPointMake(50, 25)];
//    [path moveToPoint:CGPointMake(50, 25)];
//    [path addLineToPoint:CGPointMake(50, 50)];
//    [path moveToPoint:CGPointMake(50, 50)];
//    [path addLineToPoint:CGPointMake(0, 50)];
//    [path moveToPoint:CGPointMake(0, 50)];
//    [path addLineToPoint:CGPointMake(0, 0)];
    shape.path = path;
    //shape.strokeColor = [[UIColor yellowColor] CGColor];
    shape.fillColor = [[UIColor blackColor] CGColor];
    
    UIView *textView = [[UIView alloc] initWithFrame:CGRectMake(100, 100, 50, 50)];
    [textView.layer addSublayer:shape];
    textView.layer.mask = shape;
    textView.backgroundColor = [UIColor brownColor];
    [self.view addSubview:textView];
    
    //释放前面创建的路径
    CGPathRelease(path);
    
    [UIView animateWithDuration:5 animations:^{
        
        textView.transform = CGAffineTransformMakeScale(5, 5);
    } completion:nil];
    
}

- (CGSize)preferedTextCGSize:(NSString *)text font:(UIFont *)font width:(CGFloat)width
{
    CGSize containerSize = CGSizeMake(width, CGFLOAT_MAX);
    CGSize fitSize = CGSizeZero;
    if ([text respondsToSelector:@selector(boundingRectWithSize:options:attributes:context:)])
    {
        fitSize = [text boundingRectWithSize:containerSize options:NSStringDrawingUsesFontLeading|NSStringDrawingTruncatesLastVisibleLine|NSStringDrawingUsesLineFragmentOrigin attributes:@{NSFontAttributeName:font} context:NULL].size;
    }
    else
    {
        //fitSize = [text sizeWithFont:font constrainedToSize:containerSize lineBreakMode:NSLineBreakByWordWrapping];
    }
    
    return  fitSize;
}


- (NSUInteger)simpleTxtBinarySearch:(NSString*)text fontSize:(CGFloat)fontSize maxWidth:(CGFloat)maxWidth
{
    UIFont *font = [UIFont systemFontOfSize:fontSize];
    NSUInteger lowIdx = 1;
    NSUInteger hightIdx = [text length];
    NSUInteger midIdx = 0;
    
    NSString *subS1 = [text substringWithRange:NSMakeRange(0,hightIdx)];
    CGSize size1 = [self preferedTextCGSize:subS1 font:font width:maxWidth];
    if (size1.height < fontSize*2)
    {
        return hightIdx;
    }
    else
    {
        while (lowIdx <= hightIdx)
        {
            midIdx = lowIdx+((hightIdx-lowIdx)/2);
            NSString *subS2 = [text substringWithRange:NSMakeRange(0,midIdx)];
            NSString *subS3 = [text substringWithRange:NSMakeRange(0,midIdx+1)];
            CGSize size2 = [self preferedTextCGSize:subS2 font:font width:maxWidth];
            CGSize size3 = [self preferedTextCGSize:subS3 font:font width:maxWidth];
            if (size3.height >= fontSize*2 && size2.height < fontSize *2)
            {
                return midIdx;
            }
            else
            {
                if (size2.height < fontSize*2) //小了
                {
                    lowIdx = midIdx + 1;
                }
                else //大了
                {
                    hightIdx = midIdx - 1;
                }
            }
        }
    }
    return 0;
}

- (UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

- (BOOL)prefersStatusBarHidden
{
    return NO;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)textMask
{
    self.view.backgroundColor = [UIColor whiteColor];
    
    UILabel* label = [[UILabel alloc] initWithFrame:self.view.bounds];
    label.text = @"Label Text";
    label.font = [UIFont systemFontOfSize:70];
    label.textAlignment = NSTextAlignmentCenter;
    label.textColor = [UIColor blackColor];
    
    label.backgroundColor = [UIColor clearColor];
    
//    UIView *panelView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 500, 500)];
//    panelView.backgroundColor = [UIColor purpleColor];
//    [self.view addSubview:panelView];
//    
//    UIView *vv2 = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 500, 500)];
//    vv2.backgroundColor = [UIColor orangeColor];
//    [self.view addSubview:vv2];
//    
//    
//    vv2.maskView = label;
//
    UIImageView* overlayView = [[UIImageView alloc] initWithFrame:self.view.bounds];
    overlayView.image = [UIImage imageNamed:@"1.jpg"];
    //overlayView.maskView = label;
    [self.view addSubview:overlayView];
    
    TestView *tv = [[TestView alloc] initWithFrame:CGRectMake(0, 100, 200, 200)];
    //tv.bkColor = [UIColor redColor];
    tv.font = [UIFont systemFontOfSize:20];
    tv.text = @"hello world";
   [self.view addSubview:tv];
    
    VVView *v = [[VVView alloc] initWithFrame:CGRectMake(0, 100, 100, 100)];
    v.backgroundColor = [UIColor clearColor];
    //[self.view addSubview:v];
}

- (void)testMyVC
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        MyRotateVC *rvc = [MyRotateVC new];
        //UIViewController *rvc = [UIViewController new];
        rvc.view.backgroundColor = [UIColor redColor];
        [self presentViewController:rvc animated:YES completion:nil];
    });
    
}

- (void)testSpecialView
{
    SpecialUIWebView *view = [[SpecialUIWebView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:view];
}

- (void)testLongPressGesture
{
    UILongPressGestureRecognizer *ges = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(gestureRecognized:)];
    ges.minimumPressDuration = 5;
    [self.view addGestureRecognizer:ges];
}

- (void)gestureRecognized:(UILongPressGestureRecognizer*)ges
{
    NSLog(@"%zd",ges.state);
}

- (BOOL)shouldAutorotate
{
    return NO;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskPortrait;
}

@end
