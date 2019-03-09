//
//  main.m
//  testNSProxy
//
//  Created by Caichao on 15/4/28.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyProxy :NSProxy {
    NSObject *object;
}

- (id)transformToObject:(NSObject *)anObject;

@end

@implementation MyProxy

- (void)dealloc
{
    [object release];
    object = nil;
    [super dealloc];
}

- (void)fun
{
    // Do someting virtual
    //先做一些代理工作，然后创建一个后台线程，在后台线程中再调用真正的[object fun];
    [object performSelector:@selector(fun) withObject:nil withObject:nil];
}

// Stupid transform implementation just by assigning a passed in object as transformation target. You can write your factory here and use passed in object as id for object that need ot be created.
- (id)transformToObject:(NSObject *)anObject
{
    if(object != anObject) {
        [object release];
    }
    object = [anObject retain];
    return object;
}

- (void)forwardInvocation:(NSInvocation *)invocation
{
    if (object != nil) {
        [invocation setTarget:object];
        
        [invocation invoke];
    }
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)sel
{
    NSMethodSignature *result;
    if (object != nil) {
        result = [object methodSignatureForSelector:sel];
    } else {
        // Will throw an exception as default implementation
        result = [super methodSignatureForSelector:sel];
    }
    return result;
}

@end


@interface RealSubject : NSObject

- (void)fun;

@end


@implementation RealSubject

- (void)fun
{
    //这个方法需要代理进行惰性调用
    // Do something real
    NSLog(@"fun");
}

- (void)otherFun
{
    //这个方法不需要代理做任何处理，可直接被调用
    // Do something real
    NSLog(@"otherFun");
}

@end

// main.m
int main(int argc,char *argv[])
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    MyProxy *myProxy = [MyProxy alloc];
    RealSubject *realSub = [[RealSubject alloc] init];
    [myProxy transformToObject:realSub];
    [myProxy fun]; // 直接调用myProxy的fun，执行代理工作
    [myProxy otherFun]; // 依次调用myProxy的methodSignatureForSelector和forwardInvocation转发给realSub，realSub调用otherFun
    [myProxy testss];
    
    [RealSubject release];
    [myProxy release];
    
    [pool release];
    return 0;
}

