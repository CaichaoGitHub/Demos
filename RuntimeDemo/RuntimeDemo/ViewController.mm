//
//  ViewController.m
//  RuntimeDemo
//
//  Created by caichao on 2019/4/16.
//  Copyright © 2019 caichao. All rights reserved.
//

#import "ViewController.h"
#import "KVOBlock.h"

#import <objc/runtime.h>
#import <objc/message.h>

@interface Computer : NSObject

@property (nonatomic , strong) NSString *name;

@end

@implementation Computer

- (void)reloadData
{
    NSLog(@"reload data computer");
}

@end

@interface Person : NSObject
{
    NSString *_age;
}

@end

@implementation Person


- (instancetype)init
{
    self = [super init];
    
    _age = @"18";
    
    return self;
}

- (void)printAge
{
    Ivar ivar = class_getInstanceVariable([self class], "_age");
    object_setIvar(self, ivar, @"100");
    NSLog(@"age %@",_age);
}

static void testIMP(id self,SEL _cmd)
{
    NSLog(@"reload data");
}

+ (BOOL)resolveInstanceMethod:(SEL)sel
{
    //ask1
//    if ([NSStringFromSelector(sel) isEqualToString:@"reloadData"]) {
//
//        char *pNmae = @encode(id);
//        class_addMethod([self class], sel, (IMP)testIMP, "v@:");
//        return YES;
//
//    }
    return NO;
}

- (id)forwardingTargetForSelector:(SEL)aSelector
{
    //ask2
//    if ([NSStringFromSelector(aSelector) isEqualToString:@"reloadData"]) {
//
//        return [Computer new];
//
//    }
    return nil;
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector
{
    //ask3
    return [NSMethodSignature signatureWithObjCTypes:"v@:"];
}

- (void)forwardInvocation:(NSInvocation *)anInvocation
{
    //ask4
    Computer *t = [Computer new];
    [anInvocation setTarget:t];
    [anInvocation invoke];
}

@end


@interface MyNavi : NSObject

@end

@implementation MyNavi

+ (void)load
{
    [super load];
    
    [self tellMePush];
}

- (void)pushView:(NSObject*)view ani:(BOOL)ani
{
    NSLog(@"original push");
}

typedef void (*voidImp)(id,SEL,...);

static voidImp sOriginPushImp = NULL;

static void tellmePush(id self,SEL _cmd,id view,BOOL ani)
{
    NSLog(@"new push");
    
    if (sOriginPushImp) {
        sOriginPushImp(self,_cmd,view,ani);
    }
}

+ (void)tellMePush
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        
        Class classss = [self class];
        SEL sele = @selector(pushView:ani:);
        Method originMeth = class_getInstanceMethod(classss, sele);
        sOriginPushImp = (voidImp)(void*)method_getImplementation(originMeth);
        method_setImplementation(originMeth, (IMP)tellmePush);
    });
}

@end

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    Person *per = [[Person alloc] init];
    [per printAge];
    [per performSelector:@selector(reloadData) withObject:nil];
    
    [[MyNavi new] pushView:nil ani:YES];
    
    __block NSString *str = @"abc";
    void(^blk)() = ^{
        str = @"cde";
    };
    
    int bc = 1;
    int &bcref = bc;
    __block int b = 1;
    int &bref = b;
    NSLog(@"address1 %p",&b);
    void(^blk1)() = ^{
        b = 3;
        NSLog(@"address2 %p",&b);
    };
    blk1();
    NSLog(@"address3 %p",&b);
    NSLog(@"address3 %p",&bref);
    
    Computer *computer = [Computer new];
    [computer sw_addObserver:self forKeyPath:@"name" callback:^(id observerdObject, NSString *keyPath, id oldValue, id newValue) {
        
        NSLog(@"%@ - %@",oldValue,newValue);
        
    }];
    [computer setName:@"abc"];
    
//    do {
//        wait_message(); -> darwin msg port
//        int msg = get_msg();
    //        process_msg(msg);{update time , callback selector ..}
//    } while (msg != quit_msg);
    
}


@end
