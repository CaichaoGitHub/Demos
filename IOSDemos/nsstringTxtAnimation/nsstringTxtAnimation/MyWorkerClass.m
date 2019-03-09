//
//  MyWorkerClass.m
//  nsstringTxtAnimation
//
//  Created by Caichao on 16/3/10.
//  Copyright © 2016年 Caichao. All rights reserved.
//

#import "MyWorkerClass.h"

CFRunLoopSourceRef customSourceRef;
CFRunLoopRef customLoopRef;

@interface MyWorkerClass()<NSPortDelegate>

@property (nonatomic , assign) BOOL shouldExit;
@property (nonatomic , retain) NSPort *distantPort;
@property (nonatomic , retain) NSPort *remotePort;

@property (nonatomic , retain) NSMachPort *thread1Port;
@property (nonatomic , retain) NSMachPort *thread2Port;
@property (nonatomic , assign) BOOL isThread1TaskFinished;
@property (nonatomic , assign) BOOL isThread3Finished;

@end

@implementation MyWorkerClass

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        static dispatch_once_t onceToken;
        dispatch_once(&onceToken, ^{
            //[self testThread];
            [self test1];
        });
        
    }
    return self;
}

- (void)test1
{
    NSThread *thread = [[NSThread alloc] initWithTarget:self selector:@selector(thread3) object:nil];
    [thread start];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        
        self.isThread3Finished = YES;
        
        [self performSelector:@selector(runTask) onThread:thread withObject:nil waitUntilDone:NO modes:@[(NSString*)kCFRunLoopCommonModes]];
        
        [thread cancel];
        
    });
    
    
    //[NSThread detachNewThreadSelector:@selector(thread1) toTarget:self withObject:nil];
    //[NSThread detachNewThreadSelector:@selector(thread2) toTarget:self withObject:nil];
    //[NSThread detachNewThreadSelector:@selector(threadPort1) toTarget:self withObject:nil];
}

- (void)runTask
{
    NSLog(@"runTask");
}

- (void)thread3
{
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    
    CFMachPortRef portRef = CFMachPortCreate(NULL, NULL, NULL, NULL);
    
    CFRunLoopSourceRef sourceRef = CFMachPortCreateRunLoopSource(NULL, portRef, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), sourceRef, kCFRunLoopDefaultMode);
    
    do {
        NSLog(@"run");
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, CFDateGetAbsoluteTime((__bridge CFDateRef)[NSDate distantFuture]), YES);
    } while (!self.isThread3Finished);
    NSLog(@"finish");
    CFRunLoopRemoveSource(CFRunLoopGetCurrent(), sourceRef, kCFRunLoopDefaultMode);
    
    CFRelease(sourceRef);
    CFRelease(portRef);
    
    [pool drain];
}

- (void)thread1
{
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    
    CFRunLoopRef runLoopRef  = CFRunLoopGetCurrent();
    
    //add a observer for current runloop,CFRunLoopActivity is what you care about
    CFRunLoopObserverContext context = {0,self,NULL,NULL,NULL};
    CFRunLoopObserverRef observerRef = CFRunLoopObserverCreate(NULL, kCFRunLoopAllActivities, true, 0, observerCallBack, &context);
    CFRunLoopAddObserver(runLoopRef, observerRef, kCFRunLoopDefaultMode);
    
    //[NSTimer scheduledTimerWithTimeInterval:4 target:self selector:@selector(doFireTimer) userInfo:nil repeats:YES];
    
    //sub thead's timer
    //theory:the timer is actived by the timer hardware.when we start a timer , one of computer's timer hardwares begin to time
    //after time out,the timer hardware will break CPU and make CPU run your program right now
    CFRunLoopTimerContext timercontext = {0, NULL, NULL, NULL, NULL};
    CFRunLoopTimerRef timer = CFRunLoopTimerCreate(kCFAllocatorDefault, 0.1, 0, 0, 0,
                                                   &timerCallBack, &timercontext);
    
    CFRunLoopAddTimer(runLoopRef, timer, kCFRunLoopCommonModes);
    
    do {
        
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1000/*CFDateGetAbsoluteTime((__bridge CFDateRef)[NSDate dateWithTimeIntervalSinceNow:3])*/, false);
        
    } while (!self.isThread1TaskFinished);
    
    CFRunLoopRemoveObserver(runLoopRef, observerRef, kCFRunLoopDefaultMode);
    CFRelease(observerRef);
    [pool release];
}

void observerCallBack(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info)
{
    NSLog(@"%zd",activity);
}

- (void)thread2
{
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    
    [self useCustomInputSource];
    
    do {
        
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 15, false);
    } while (false);
    
    //[self removeCustomInputSource];
    
    [pool release];
}

- (void)useCustomInputSource
{
    //using "CFRunLoopSourceContext" to custom my input source
    CFRunLoopSourceContext context = {0,self,NULL,NULL,NULL,NULL,NULL,RunLoopSourceScheduleRoutine,RunLoopSourceCancelRoutine,RunLoopSourcePerformRoutine};
    customSourceRef = CFRunLoopSourceCreate(NULL, 0, &context);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), customSourceRef, kCFRunLoopDefaultMode);
    customLoopRef = CFRunLoopGetCurrent();
}

- (void)removeCustomInputSource
{
    CFRunLoopRemoveSource(CFRunLoopGetCurrent(), customSourceRef, kCFRunLoopDefaultMode);
}

- (void)signalCustomSource
{
    CFRunLoopSourceSignal(customSourceRef);
    CFRunLoopWakeUp(customLoopRef);
}

void RunLoopSourceScheduleRoutine (void *info, CFRunLoopRef rl, CFStringRef mode)
{
    NSLog(@"RunLoopSourceScheduleRoutine");
//    RunLoopSource* obj = (RunLoopSource*)info;
//    AppDelegate*   del = [AppDelegate sharedAppDelegate];
//    RunLoopContext* theContext = [[RunLoopContext alloc] initWithSource:obj andLoop:rl];
//    
//    [del performSelectorOnMainThread:@selector(registerSource:)
//                          withObject:theContext waitUntilDone:NO];
}

void RunLoopSourcePerformRoutine (void *info)
{
    NSLog(@"RunLoopSourcePerformRoutine");
}

void RunLoopSourceCancelRoutine (void *info, CFRunLoopRef rl, CFStringRef mode)
{
    NSLog(@"RunLoopSourceCancelRoutine");
}

void timerCallBack(CFRunLoopTimerRef timer, void *info)
{
    NSLog(@"timerCallBack");
}

- (void)doFireTimer
{
    NSLog(@"doFireTimer");
    //self.isThread1TaskFinished = YES;
    CFRunLoopStop(CFRunLoopGetCurrent()); // we can stop current thread's runloop to make current thread exit
    
    [self signalCustomSource]; // signal my working thread to work from another thread
}

- (void)threadPort1
{
    // Create a local port for receiving responses.
    CFStringRef myPortName;
    CFMessagePortRef myPort;
    CFRunLoopSourceRef rlSource;
    CFMessagePortContext context = {0, NULL, NULL, NULL, NULL};
    Boolean shouldFreeInfo;
    
    myPortName = CFStringCreateWithFormat(NULL, NULL, CFSTR("threadPort1"));
    
    //give thread1 a input source
    myPort = CFMessagePortCreateLocal(NULL, myPortName, threadPort1CallBack, &context, &shouldFreeInfo);
    
    rlSource = CFMessagePortCreateRunLoopSource(NULL, myPort, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), rlSource, kCFRunLoopDefaultMode);
    
    [NSThread detachNewThreadSelector:@selector(threadPort2:) toTarget:self withObject:(__bridge NSObject*)myPortName];
    
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, CFDateGetAbsoluteTime((__bridge CFDateRef)[NSDate distantFuture]), false);
    
    //these can be released
    CFRelease(myPort);
    CFRelease(rlSource);
    CFRelease(myPortName);
}

- (void)threadPort2:(CFStringRef)portName
{
    CFMessagePortRef threadPort1 = CFMessagePortCreateRemote(NULL, portName);
    
    CFStringRef myPortName = CFStringCreateWithFormat(NULL, NULL, CFSTR("threadPort2"));
    CFMessagePortContext context = {0,threadPort1,NULL,NULL,NULL};
    Boolean shouldFreeInfo;
    Boolean shouldAbort = true;
    
    //in order to block current thread ,let's create a local port for current thread
    CFMessagePortRef myPort = CFMessagePortCreateLocal(NULL, myPortName, threadPort2CallBack, &context, &shouldFreeInfo);
    
    if (shouldFreeInfo)
    {
        exit(0);
    }
    
    CFRunLoopSourceRef rlSource = CFMessagePortCreateRunLoopSource(NULL, myPort, 0);
    
    if (!rlSource)
    {
        exit(0);
    }
    
    CFRunLoopAddSource(CFRunLoopGetCurrent(), rlSource, kCFRunLoopDefaultMode);
    
    CFDataRef returnData = nil;
    CFDataRef outData;
    CFIndex strLength = CFStringGetLength(myPortName);
    UInt8 *buffer = CFAllocatorAllocate(NULL, strLength, 0);
    CFStringGetBytes(myPortName, CFRangeMake(0, strLength), kCFStringEncodingASCII, 0, false, buffer, strLength, NULL);
    outData = CFDataCreate(NULL, buffer, strLength);
    //send data to target port
    //here,i target the sendtimeout and replytimeout to make current thread to waiting another thread's reply
    //after we get the reply , contiune processing
    SInt32 result = CFMessagePortSendRequest(threadPort1, 123, outData, 10, 10, kCFRunLoopDefaultMode , &returnData);
    
    CFIndex bufferLen = CFDataGetLength(returnData);
    UInt8 *reBuffer = CFAllocatorAllocate(NULL, bufferLen, 0);
    
    CFDataGetBytes(returnData, CFRangeMake(0, bufferLen), reBuffer);
    
    // Clean up thread data structures.
    CFRelease(outData);
    CFAllocatorDeallocate(NULL, buffer);
    
    // keep current thread running
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, CFDateGetAbsoluteTime((__bridge CFDateRef)[NSDate distantFuture]), false);
}

CFDataRef threadPort2CallBack(CFMessagePortRef local, SInt32 msgid, CFDataRef data, void *info)
{
    return nil;
}

CFDataRef threadPort1CallBack(CFMessagePortRef local, SInt32 msgid, CFDataRef data, void *info)
{
    if (msgid == 123)
    {
        //analyse the data sended by thread2
        CFMessagePortRef msgPort;
        CFStringRef threadPortName;
        CFIndex bufferLen = CFDataGetLength(data);
        UInt8 *buffer = CFAllocatorAllocate(NULL, bufferLen, 0);
        CFDataGetBytes(data, CFRangeMake(0, bufferLen), buffer);
        threadPortName = CFStringCreateWithBytes(NULL, buffer, bufferLen, kCFStringEncodingASCII, false);
        
        msgPort = CFMessagePortCreateRemote(NULL, threadPortName);
        
        //here after receiving the thread2's data, we can alos send thread1's data to thread2
        
        CFRelease(msgPort);
        // Clean up.
        CFRelease(threadPortName);
        CFAllocatorDeallocate(NULL, buffer);
        
        CFStringRef reStrRef = CFStringCreateWithFormat(NULL, NULL, CFSTR("yes , i get ur the data"));
        CFIndex strLen = CFStringGetLength(reStrRef);
        UInt8 *reBuffer = CFAllocatorAllocate(NULL, strLen, 0);
        CFStringGetBytes(reStrRef, CFRangeMake(0, strLen), kCFStringEncodingASCII, 0, false, reBuffer, strLen, NULL);
        
        //prepare the returndata and reply thread 2
        return CFDataCreate(NULL, reBuffer, strLen);
        
    }
    return nil;
}

@end
