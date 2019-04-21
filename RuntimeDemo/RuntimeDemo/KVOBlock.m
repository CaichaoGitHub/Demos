//
//  KVOBlock.m
//  RuntimeDemo
//
//  Created by caichao on 2019/4/20.
//  Copyright © 2019 caichao. All rights reserved.
//

#import "KVOBlock.h"
#import <objc/runtime.h>
#import <objc/message.h>

static void *const sw_KVOObserverAssociatedKey = (void *)&sw_KVOObserverAssociatedKey;
static NSString *sw_KVOClassPrefix = @"sw_KVONotifing_";

@implementation SWKVOObserverItem

@end

@implementation NSObject(KVOBlock)

- (void)sw_addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath callback:(sw_KVOObserverBlock)callback
{
    NSString *setterString = sw_setterByGetter(keyPath);
    SEL setterSel = NSSelectorFromString(setterString);
    Method method = class_getInstanceMethod(object_getClass(self), setterSel); //找到原始类的setter方法
    if (method)
    {
        Class objectClass = object_getClass(self);
        NSString *objectClassName = NSStringFromClass(objectClass);
        if (![objectClassName hasPrefix:sw_KVOClassPrefix]) {
            Class kvoClass = [self makeKvoClassWithOriginalClassName:objectClassName];
            object_setClass(self, kvoClass);
        }
        
        if (![self hasMethodWithMethodName:setterString]) {
            class_addMethod(object_getClass(self), NSSelectorFromString(setterString), (IMP)sw_kvoSetter,method_getTypeEncoding(method));
        }
        
        // 4. 注册Observer
        NSMutableArray<SWKVOObserverItem *> *observerArray = objc_getAssociatedObject(self, sw_KVOObserverAssociatedKey);
        if (observerArray == nil) {
            observerArray = [NSMutableArray new];
            objc_setAssociatedObject(self, sw_KVOObserverAssociatedKey, observerArray, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        }
        SWKVOObserverItem *item = [SWKVOObserverItem new];
        item.keyPath = keyPath;
        item.observer = observer;
        item.callback = callback;
        [observerArray addObject:item];
    }
}

- (void)sw_removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath
{
    NSMutableArray<SWKVOObserverItem *> *observerArray = objc_getAssociatedObject(self, sw_KVOObserverAssociatedKey);
    [observerArray enumerateObjectsUsingBlock:^(SWKVOObserverItem * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        if (obj.observer == observer && [obj.keyPath isEqualToString:keyPath]) {
            [observerArray removeObject:obj];
        }
    }];
    
    if (observerArray.count == 0) {
        Class originalClass = [self class];
        Class kvoClass = object_getClass(self);
        object_setClass(self, originalClass);
        objc_disposeClassPair(kvoClass);
    }
}

- (Class)makeKvoClassWithOriginalClassName:(NSString*)originalClassName
{
    NSString *kvoClassName = [NSString stringWithFormat:@"%@%@",sw_KVOClassPrefix,originalClassName];
    Class kvoClass = objc_getClass(kvoClassName.UTF8String);
    if (kvoClass) {
        return kvoClass;
    }
    kvoClass = objc_allocateClassPair(object_getClass(self), kvoClassName.UTF8String, 0);
    objc_registerClassPair(kvoClass);
    Method classMe = class_getInstanceMethod(object_getClass(self), @selector(class));
    const char *types = method_getTypeEncoding(classMe);
    class_addMethod(kvoClass, @selector(class), (IMP)sw_class, types);
    return kvoClass;
}

- (BOOL)hasMethodWithMethodName:(NSString*)selname
{
    unsigned int methodCount = 0;
    Method *methodList = class_copyMethodList(object_getClass(self), &methodCount);
    for (int i = 0; i < methodCount; i ++) {
        Method method = methodList[i];
        SEL sel = method_getName(method);
        NSString *name = NSStringFromSelector(sel);
        if ([selname isEqualToString:name]) {
            return YES;
        }
    }
    return NO;
}

#pragma mark - helper method

static void sw_kvoSetter(id self,SEL selector, id value)
{
    NSString *getterString = sw_getterBySetter(selector);
    if (getterString) {
        id(*getterMsgSend)(id,SEL) = (void *)objc_msgSend;
        id oldValue = getterMsgSend(self,NSSelectorFromString(getterString));
        id(*supperSetterMsgSend)(void *,SEL,id newValue) = (void*)objc_msgSendSuper;
        struct objc_super objcSuper = {
            .receiver = self,
            .super_class = class_getSuperclass(object_getClass(self)),
        };
        supperSetterMsgSend(&objcSuper,selector,value);
        NSMutableArray<SWKVOObserverItem*> *observerArray = objc_getAssociatedObject(self, sw_KVOObserverAssociatedKey);
        if (observerArray == nil) {
            observerArray = [NSMutableArray new];
            objc_setAssociatedObject(self, sw_KVOObserverAssociatedKey, observerArray, OBJC_ASSOCIATION_RETAIN);
        }
       
        [observerArray enumerateObjectsUsingBlock:^(SWKVOObserverItem * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            
            if ([obj.keyPath isEqualToString:getterString]) {
                dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                    obj.callback(self, getterString, oldValue, value);
                });
            }
        }];
    }
}

static Class sw_class(id self,SEL selector)
{
    return class_getSuperclass(object_getClass(self)); //super 类是真正的类，直接返回
}

static NSString *sw_getterBySetter(SEL setter) {
    NSString *setterString = NSStringFromSelector(setter);
    if (![setterString hasPrefix:@"set"]) {
        return nil;
    }
    
    // 下面根据setAge 方法生成 age NSString
    NSString *firstString = [setterString substringWithRange:NSMakeRange(3, 1)];
    firstString = [firstString lowercaseString];
    if (setterString.length < 5) {
        return firstString;
    }
    NSString *getterString = [setterString substringWithRange:NSMakeRange(4, setterString.length - 5)];
    getterString = [NSString stringWithFormat:@"%@%@", firstString, getterString];
    return getterString;
}

static NSString * sw_setterByGetter(NSString* getterString) {
    NSString *firstString = [getterString substringToIndex:1];
    firstString = [firstString uppercaseString];
    NSString *lastString = [getterString substringFromIndex:1];
    NSString *setterString = [NSString stringWithFormat:@"set%@%@:", firstString, lastString];
    return setterString;
}

@end
