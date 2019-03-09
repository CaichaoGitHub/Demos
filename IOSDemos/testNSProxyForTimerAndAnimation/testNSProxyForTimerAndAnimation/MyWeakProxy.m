//
//  MyProxy.m
//  testNSProxyForTimerAndAnimation
//
//  Created by Caichao on 15/4/28.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import "MyWeakProxy.h"

#pragma mark - FLWeakProxy

@interface MyWeakProxy ()

@property (nonatomic, weak) id target;

@end


@implementation MyWeakProxy

#pragma mark Life Cycle

// This is the designated creation method of an `FLWeakProxy` and
// as a subclass of `NSProxy` it doesn't respond to or need `-init`.
+ (instancetype)weakProxyForObject:(id)targetObject
{
    MyWeakProxy *weakProxy = [MyWeakProxy alloc];
    weakProxy.target = targetObject;
    return weakProxy;
}


#pragma mark Forwarding Messages

- (id)forwardingTargetForSelector:(SEL)selector
{
    return _target;
}

- (void)forwardInvocation:(NSInvocation *)invocation
{
    void *nullPointer = NULL;
    [invocation setReturnValue:&nullPointer];
}


- (NSMethodSignature *)methodSignatureForSelector:(SEL)selector
{
    return [NSObject instanceMethodSignatureForSelector:@selector(init)];
}

@end




