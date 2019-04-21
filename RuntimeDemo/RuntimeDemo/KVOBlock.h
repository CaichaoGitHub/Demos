//
//  KVOBlock.h
//  RuntimeDemo
//
//  Created by caichao on 2019/4/20.
//  Copyright © 2019 caichao. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^sw_KVOObserverBlock)(id observerdObject,NSString *keyPath,id oldValue,id newValue);

@interface SWKVOObserverItem : NSObject
@property(nonatomic, weak) NSObject *observer;  // 注意这里是weak，不会对observer做强引用，这样可以消除 观察者和被观察者间潜在的循环引用
@property(nonatomic, copy) NSString *keyPath;
@property(nonatomic, copy) sw_KVOObserverBlock callback;
@end

@interface NSObject(KVOBlock)

- (void)sw_addObserver:(NSObject *)observer
            forKeyPath:(NSString *)keyPath
              callback:(sw_KVOObserverBlock)callback;

- (void)sw_removeObserver:(NSObject *)observer
               forKeyPath:(NSString *)keyPath;

@end


