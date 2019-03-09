//
//  MyProxy.h
//  testNSProxyForTimerAndAnimation
//
//  Created by Caichao on 15/4/28.
//  Copyright (c) 2015年 Caichao. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyWeakProxy : NSProxy

+ (instancetype)weakProxyForObject:(id)targetObject;

@end
