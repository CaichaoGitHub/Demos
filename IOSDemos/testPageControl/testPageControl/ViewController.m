//
//  ViewController.m
//  testPageControl
//
//  Created by Caichao on 15/9/17.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()<UIScrollViewDelegate>
{
    UIScrollView* helpScrView;
    UIPageControl* pageCtrl;
}

@end


@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    CGRect bounds = self.view.frame;  //获取界面区域
    
    //加载蒙板图片，限于篇幅，这里仅显示一张图片的加载方法
    UIImageView* imageView1 = [[UIImageView alloc] initWithFrame:CGRectMake(0, bounds.origin.y, bounds.size.width, bounds.size.height)];  //创建UIImageView，位置大小与主界面一样。
    [imageView1 setImage:[UIImage imageNamed:@"bg.png"]];  //加载图片help01.png到imageView1中。
    //imageView1.alpha = 0.5f;  //将透明度设为50%。
    UIImageView* imageView2 = [[UIImageView alloc] initWithFrame:CGRectMake(1*bounds.size.width, bounds.origin.y, bounds.size.width, bounds.size.height)];  //创建UIImageView，位置大小与主界面一样。
    [imageView2 setImage:[UIImage imageNamed:@"bg.png"]];
    //继续加载图片
    //。。。。
    
    UIView *view1 = [[UIView alloc] initWithFrame:CGRectMake(0, bounds.origin.y, bounds.size.width, bounds.size.height)];
    view1.backgroundColor = [UIColor redColor];
    
    UIView *view2 = [[UIView alloc] initWithFrame:CGRectMake(1*bounds.size.width, bounds.origin.y, bounds.size.width, bounds.size.height)];
    view2.backgroundColor = [UIColor blueColor];
    
    UIView *view3 = [[UIView alloc] initWithFrame:CGRectMake(2*bounds.size.width, bounds.origin.y, bounds.size.width, bounds.size.height)];
    view3.backgroundColor = [UIColor yellowColor];
    
    //创建UIScrollView
    helpScrView = [[UIScrollView alloc] initWithFrame:CGRectMake(bounds.origin.x, bounds.origin.y, bounds.size.width, 300)];  //创建UIScrollView，位置大小与主界面一样。
    [helpScrView setContentSize:CGSizeMake(bounds.size.width * 3, 300)];  //设置全部内容的尺寸，这里帮助图片是3张，所以宽度设为界面宽度*3，高度和界面一致。
    helpScrView.pagingEnabled = YES;  //设为YES时，会按页滑动
    helpScrView.bounces = YES; //取消UIScrollView的弹性属性，这个可以按个人喜好来定
    [helpScrView setDelegate:self];//UIScrollView的delegate函数在本类中定义
    helpScrView.showsHorizontalScrollIndicator = YES;  //因为我们使用UIPageControl表示页面进度，所以取消UIScrollView自己的进度条。
    [helpScrView addSubview:view1];
    [helpScrView addSubview:view2];//将UIImageView添加到UIScrollView中。
    [helpScrView addSubview:view3];
    [self.view addSubview:helpScrView]; //将UIScrollView添加到主界面上。
    
    //创建UIPageControl
    pageCtrl = [[UIPageControl alloc] initWithFrame:CGRectMake(0, 400, bounds.size.width, 30)];  //创建UIPageControl，位置在屏幕最下方。
    pageCtrl.numberOfPages = 6;//总的图片页数
    pageCtrl.currentPage = 0; //当前页
    [pageCtrl addTarget:self action:@selector(pageTurn:) forControlEvents:UIControlEventValueChanged];  //用户点击UIPageControl的响应函数
    //[self.view addSubview:pageCtrl];  //将UIPageControl添加到主界面上。
}

//其次是UIScrollViewDelegate的scrollViewDidEndDecelerating函数，用户滑动页面停下后调用该函数。


- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView
{
    //更新UIPageControl的当前页
    CGPoint offset = scrollView.contentOffset;
    CGRect bounds = scrollView.frame;
    [pageCtrl setCurrentPage:offset.x / bounds.size.width];
    NSLog(@"%f",offset.x / bounds.size.width);
}

//然后是点击UIPageControl时的响应函数pageTurn


- (void)pageTurn:(UIPageControl*)sender
{
    //令UIScrollView做出相应的滑动显示
    CGSize viewSize = helpScrView.frame.size;
    CGRect rect = CGRectMake(sender.currentPage * viewSize.width, 0, viewSize.width, viewSize.height);
    [helpScrView scrollRectToVisible:rect animated:YES];
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
