//
//  ViewController.m
//  testNSOperationQueue
//
//  Created by Caichao on 15/5/26.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "ViewController.h"

static int m = 0;

@interface ViewController ()

@property (strong) NSOperationQueue *operationQueue;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.operationQueue = [[NSOperationQueue alloc] init];
    self.operationQueue.maxConcurrentOperationCount  = 1;
    
    NSBlockOperation *blockO = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"thread sleep 2s");
        [NSThread sleepForTimeInterval:2];
    }];
    
    NSBlockOperation *blockOperation = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"index = %d",m++);
    }];
    
    [blockOperation addExecutionBlock:^{
        NSLog(@"index = %d",m++);
    }];
    
    [blockOperation addExecutionBlock:^{
        NSLog(@"index = %d",m++);
    }];
    
    [blockOperation addExecutionBlock:^{
        NSLog(@"index = %d",m++);
    }];
    
    
    [blockOperation addDependency:blockO];
    
    NSBlockOperation *block1 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"hello bb");
        [blockO waitUntilFinished];
        NSLog(@"hello aa");
    }];
    
   // [self.operationQueue addOperation:blockOperation];
    //[self.operationQueue addOperation:blockO];
    //[self.operationQueue addOperation:block1];
    
    NSBlockOperation *block3 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"index = %d",m++);
    }];
    
    //[[NSOperationQueue currentQueue] addOperation:block3];
    
    NSBlockOperation *block4 = [[NSBlockOperation alloc]init];
    [block4 addExecutionBlock:^{
        NSLog(@"block4 = %d",m++);
        [NSThread sleepForTimeInterval:15];
    }];
    
    block4.completionBlock = ^(void){NSLog(@" block4 the thread completed");};
    
    NSBlockOperation *block5 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"block5 = %d",m++);
        [NSThread sleepForTimeInterval:15];
    }];
    
    __weak NSBlockOperation *b5 = block5;
    
    block5.completionBlock = ^(void){
        
        if (!b5.isCancelled)
        {
            NSLog(@"task has been finished");
        }
        NSLog(@"block5 the thread completed");
    };
    
    [self.operationQueue addOperation:block4];
    [self.operationQueue addOperation:block5];
    
    //[self performSelector:@selector(cancel) withObject:nil afterDelay:2];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [block4 cancel];
        //[self.operationQueue cancelAllOperations];
    });
    
    
}

- (void)testNSOperationQueue
{
    
}

@end
