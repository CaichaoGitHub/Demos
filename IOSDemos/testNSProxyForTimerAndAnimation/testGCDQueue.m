//
//  testGCDQueue.m
//  testNSProxyForTimerAndAnimation
//
//  Created by Caichao on 15/4/28.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "testGCDQueue.h"
#import "MyWeakProxy.h"

@interface testGCDQueue()

@property (nonatomic , assign)dispatch_queue_t myQueue;

@property (nonatomic , retain)UIView *myView;

@end

@implementation testGCDQueue

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        
        self.myView = [[[UIView alloc] initWithFrame:self.bounds] autorelease];
        [self addSubview:self.myView];
        
        _myQueue = dispatch_queue_create("test", DISPATCH_QUEUE_SERIAL);
        
        //MyWeakProxy *proxy = [MyWeakProxy weakProxyForObject:self];
        
        testGCDQueue * __weak ttt = self;
        
        dispatch_async(_myQueue, ^{
            while (1)
            {
                [NSThread sleepForTimeInterval:2];
                ttt.myView.hidden = !ttt.myView.hidden;
                //[proxy myView];
                dispatch_async(dispatch_get_main_queue(), ^{
                    NSLog(@"show dispatch log %@",ttt.myView);
                });
            }
        });
    }
    return self;
}

- (void)dealloc
{
    if (_myQueue)
    {
        dispatch_release(_myQueue);
    }
    NSLog(@"testGCDQueue dealloc");
    [super dealloc];
}

@end
