
#import "ViewController.h"


@interface TestObj : NSObject<NSCopying>

@property (nonatomic , strong) NSString *userName;

@property (nonatomic , strong) NSString *userID;

@end

@implementation TestObj

- (id)copyWithZone:(NSZone *)zone
{
    TestObj *obj = [[[self class] allocWithZone:zone] init];
    
    obj.userName = [_userName copyWithZone:zone];
    obj.userID = [_userID copyWithZone:zone];
    
    return obj;
}

- (NSString*)description
{
    return [NSString stringWithFormat:@"uid=%@&uname=%@",_userID,_userName];
}

@end

@interface TestKey : NSObject<NSCopying>

@property (nonatomic , retain) NSString *key;

@end

@implementation TestKey

- (id)copyWithZone:(NSZone *)zone
{
    TestKey *obj = [[[self class] allocWithZone:zone] init];
    
    obj.key = [_key copyWithZone:zone];
    
    return obj;
}

- (NSString*)description
{
    return [NSString stringWithFormat:@"key=%@",_key];
}

@end


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //[self testNSMapTableDefaultFunctionPointer];
    //[self testNSMapTableMyFunctionPointer];
    [self testWeakHashTable];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)testNSMapTableDefaultFunctionPointer
{
    
    /**
     *  测试，NSPointerFunctionsStrongMemory 引用+1 浅拷贝 NSPointerFunctionsCopyIn 深拷贝
     *  配合使用 = 深拷贝
     *  NSPointerFunctionsWeakMemory,弱引用，类似智能指针
     
     *  NSPointerFunctionsOpaqueMemory  大概是使用原始的指针地址，比如你通过C++ new 了一块内存，放在table里面，那么就保存这个指针，不要非法的使用retain
     
     * 这几个和内存联系紧密的应该是为了处理C指针，或者C与OC对象的一些内存问题，其实可以直接考虑使用C++的map了 如果处理C指针
     *  NSPointerFunctionsMallocMemory 没明白，英文解释是 当对象被remove会调用free 当对象copy in 的时候，会调用calloc 猜测应该是对于一些C临时对象，如堆栈上的字符串，如果要用来保存的话，应该会分配内存，拷贝对象到堆上面，
     *  NSPointerFunctionsMachVirtualMemory 没懂，字面上应该是使用机器的虚拟内存，和上面估计有类似的配合使用，
     
     *
     * 以下的几个Personalities 都是互斥的，不能同时在一起使用？
     * default is object.  As a special case, 'strong' memory used for Objects will do retain/release under non-GC
     
     NSPointerFunctionsObjectPersonality : 使用 hash and isEqual 函数 进行hash和等比比较, use the description method for a description. 默认的personality值，特殊情况下，如果你没使用使用ARC但是将这个value配合NSPointerFunctionsStrongMemory使用那么对象将被retain 和 release
     
     NSPointerFunctionsOpaquePersonality : 使用偏移的指针地址来做hash值，直接比较指针来判断对象是否相等
     
     NSPointerFunctionsObjectPointerPersonality : 使用偏移的指针地址来做hash值，直接比较指针来判断对象是否相等
     特殊情况下，如果你没使用使用ARC但是将这个value配合NSPointerFunctionsStrongMemory使用那么对象将被retain 和 release，感觉有点像上面2个对象的合成
     
     NSPointerFunctionsCStringPersonality 使用c string来做hash和比较，对于utf-8或者ascii编码的字符比较适合
     
     NSPointerFunctionsStructPersonality 使用一块内存进行hash和比较，必须配合size function哦
     
     NSPointerFunctionsIntegerPersonality 直接使用整数进行hash和比较，不做任何偏移

     总结：如果你只是用oc的对象，那么你只会用的最上面的3各属性，strong copy weak ；如果你有C的一些对象或者指针，涉及到内存管理的时候，会用到下面的一些属性，这个时候是不是可以直接考虑使用C++ containers 了 哈哈哈
     
     */
    NSMapTable *mapTable = [NSMapTable mapTableWithKeyOptions: NSPointerFunctionsObjectPersonality
                                                 valueOptions: NSPointerFunctionsStrongMemory | NSPointerFunctionsCopyIn |NSPointerFunctionsObjectPointerPersonality];
    
    
    char* key1 = "abc";
    char* key2 = "abd";
    TestObj *obj1 = [TestObj new];
    
    obj1.userID = @"ID";
    obj1.userName = @"name";
    NSString *nsKey1 = [NSString stringWithCString:key1 encoding:NSASCIIStringEncoding];
    NSString *nsKey2 = [NSString stringWithCString:key2 encoding:NSASCIIStringEncoding];
    [mapTable setObject:obj1 forKey:nsKey1];
    [mapTable setObject:obj1 forKey:nsKey2];
    obj1.userID = @"SSSSSSS";
    obj1.userName = @"!!!!!";
    NSLog(@"%@",[mapTable objectForKey:nsKey1]);
    NSLog(@"%@",[mapTable objectForKey:nsKey2]);
    NSLog(@"%@",[mapTable objectForKey:@"abc"]);
    NSLog(@"%@",[mapTable objectForKey:@"abd"]);
    
    
    //测试 NSPointerFunctionsOpaqueMemory
    NSPointerArray *array = [NSPointerArray pointerArrayWithOptions: NSPointerFunctionsMallocMemory |
                             NSPointerFunctionsStructPersonality |
                             NSPointerFunctionsCopyIn];
    //创建一个二维数组
    char* strPtr = malloc(sizeof(char) * 10);
    strcpy(strPtr, "abcd");
    [array addPointer:strPtr];
   // free(strPtr);
    char *ptr = [array pointerAtIndex:0];
    free(ptr);

}

static BOOL key_isEqual(const void *item1, const void *item2, NSUInteger (*size)(const void *item))
{
    return (unsigned)item1 == (unsigned)item2; //简单地比较指针得了
}

static NSUInteger key_hashFunction(const void *item, NSUInteger (*size)(const void *item))
{
    return (unsigned)item; //直接返回指针地址
}

static NSUInteger key_sizeFunction(const void *item)
{
    TestKey *obj =  (__bridge TestKey*)item;
    return sizeof(obj); //简单的sizeof
}

static NSString* key_descriptionFunction(const void *item)
{
    return @"description JUST FOR TEST!"; //test 文本
}

static void key_relinquishFunction(const void *item, NSUInteger (*size)(const void *item))
{
    free((void*)item); //内存释放
}

static void* key_acquireFunction(const void *src, NSUInteger (*size)(const void *item), BOOL shouldCopy)
{
    int *newPtr = NULL;
    if (!shouldCopy)
    {
        newPtr = malloc(sizeof(int)); //指针必须在堆上
        *newPtr = *(const int *)src;
    }
    else
    {
        newPtr = malloc(size(src));
        memcpy(newPtr, src, size(src)); //copy 内存
    }
    
    return newPtr;
}

- (void)testNSMapTableMyFunctionPointer
{
    NSPointerFunctions *key_pointerFun = [[NSPointerFunctions alloc] initWithOptions:NSPointerFunctionsCopyIn];
    key_pointerFun.isEqualFunction = key_isEqual;
    key_pointerFun.hashFunction = key_hashFunction;
    key_pointerFun.sizeFunction = key_sizeFunction;
    key_pointerFun.descriptionFunction = key_descriptionFunction;
    key_pointerFun.relinquishFunction = key_relinquishFunction;
    key_pointerFun.acquireFunction = key_acquireFunction;
    
    
    NSPointerFunctions *value_pointerFun = [NSPointerFunctions pointerFunctionsWithOptions:NSPointerFunctionsStrongMemory];
    
    NSMapTable *mapTable = [[NSMapTable alloc] initWithKeyPointerFunctions:key_pointerFun valuePointerFunctions:value_pointerFun capacity:2];
    
    TestKey *key1 = [[TestKey alloc] init];
    key1.key = @"abc";
    
    TestKey *key2 = [[TestKey alloc] init];
    key2.key = @"abcD";
    [mapTable setObject:@"1234" forKey:key1];
    [mapTable setObject:@"qwerty4" forKey:key2];
    
    NSLog(@"%@",[mapTable objectForKey:key1]);
    
}

- (void)testWeakHashTable
{
    //lets test the weakhashtable in mrc environment
//    NSPointerFunctionsStrongMemory
//    NSPointerFunctionsWeakMemory
    NSHashTable *table = [NSHashTable hashTableWithOptions:NSPointerFunctionsWeakMemory];
    for (int i = 0; i < 100 ; i++)
    {
        //NSString *str = [[NSString alloc] initWithFormat:@"%zd",i];
        NSObject *myobj = [[NSObject alloc] init];
        [table addObject:myobj];
        //[myobj release];
    }
    
    for (NSObject *obj in table.allObjects) {
        [obj release];
    }
    
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        //for (NSObject *obj in table.allObjects)
        {
            //[obj release];
        }
        
        //[table removeAllObjects];
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, NSEC_PER_SEC*1), dispatch_get_main_queue(), ^{
            
            dispatch_async(dispatch_get_main_queue(), ^{     //主线程，当对象释放的适合，会从容器中移除，子线程则没有发生
                
//                NSObject *myobj = [[NSObject alloc] init];
//                [table addObject:myobj];
//                [myobj release];
                
                NSLog(@"xx %@ %zd",[table allObjects],[table count]);
                
            });
            
        });
    });
    
    NSPointerArray *pointerArray = [NSPointerArray weakObjectsPointerArray];
    
    for (int i = 0; i < 100; i ++)
    {
        NSObject *obj = [[NSObject alloc] init];
        [pointerArray addPointer:obj];
        [obj release];
    }
    
//    for (int i = 0; i < 100; i ++)
//    {
//       NSObject *point = [pointerArray pointerAtIndex:i];
//        [point release];
//    }
    
    NSLog(@"xxxxxx %zd",[pointerArray count]);
    
    /**
     *  add 新observer 将已经释放的对象移除，就不用每次强行remove了
     */
    
}



@end
