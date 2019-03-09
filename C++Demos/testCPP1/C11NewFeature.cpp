//
//  C11NewFeature.cpp
//  testCPP1
//
//  Created by caichao on 14-9-23.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "C11NewFeature.h"
#include <iomanip>


void Person::setPersonType(Person::PersonType psType)
{
    m_personType = psType;
}

Person::PersonType Person::getPersonType() const
{
    return m_personType;
}

auto Person::getPersonTypeLuma() -> PersonType const
{
    return m_personType;
}

void testAutoKeyWord()
{
    vector<int> vi{1,2,3,4,5,6};
    auto itr = vi.begin();
    cout << "original for loop with auto key word" << endl;
    for (;itr != vi.end(); itr++)
    {
        cout << *itr << ",";
    }
    cout << endl;
    
    cout << "for each loop with lumba expression " << endl;
    for_each (vi.begin(), vi.end(), [](int mb)
    {
        cout<< mb << ",";
    });
    cout<< endl;
 
    cout << "class return type by auto " << endl;
    Person person;
    person.setPersonType(Person::ADULT);
    cout << person.getPersonType() << endl;
    cout << person.getPersonTypeLuma() <<endl;
    
}

void testDecltype()
{
    cout << "get member type by decltype" << endl;
    int x = 3;
    decltype(x) y = x;
    cout<< y <<endl;
}

string& getString()
{
    return *(new string{"china i love u "});
}

void testAutoRefPtr()
{
    cout << "use auto reference and pointer" << endl;
    auto funPtr = testDecltype;
    funPtr();
    auto &str = getString();
    cout << str << endl;
    
    const auto &cStrRef = getString();
    cout << cStrRef << endl;
}

bool testPFunc(string& str)
{
    if (str.length() == 1)
    {
        return true;
    }
    return false;
}

bool funnyFuntion(string)
{
    cout << "u are a funny girl " << endl;
    return true;
}

void testLumbdaExpression()
{
    cout << "test template with funtion pointer type " << endl;
    
    //下面2中template 函数指针定义形式是一样的
    TestClass<bool (*)(string)> tc;
    tc.Test1(funnyFuntion);
    
    TestClass<bool (string)> tc2;
    tc2.Test1(funnyFuntion);
    
    unsigned index = 0;
    cout << "use c98 fun pointer expression" << endl;
    typedef bool (*pFunc)(string &);
    pFunc myFunc = testPFunc;
    AddressBook addressBook;
    auto vi = addressBook.findMatchingAddressC98(myFunc);
    for_each (vi.begin(), vi.end(), [&index](string &str)
    {
        cout << "index:" << index++ << str << ",";
    });
    cout << endl;
    
    cout << "use c11 lumbda expression just more like object-c block " << endl;
    
    []{cout << "lumbda function " << endl;}();
    
    string key = "nhk";
    
    std::function<bool (const string&)> func = [&key](const string &str) -> bool
    {
        if(str == key)
        {
            return true;
        }
        return false;
    };  //使用 function 保存 lumbdda 函数,该function类模板可以还可以保存 函数指针 等任何类型的函数
    
    typedef int (*funcPtr)(const string &); //使用函数指针保存lumbda函数
    funcPtr fp = [](const string &) -> int
    {
        cout << "use function pointer save lumbda function" << endl;
        return 10;
    };
    
    fp(string("abc"));
    
    std::function<bool (string&)> ff = testPFunc;
    
    auto viLumbda = addressBook.findMatchingAddressC98([&key](const string &str) -> bool   //显示指定 返回值， 也可以不指定哦 编译器会自动推导
                                                       {
                                                           if(str == key)
                                                           {
                                                               return true;
                                                           }
                                                           return false;
                                                       });
    
    viLumbda = addressBook.findMatchingAddressC98(func);
    
    for (auto itr = std::begin(viLumbda); itr != std::end(viLumbda); ++itr)
    {
        cout << *itr << ",";
    }
    cout << endl;
}

void testLambdaDelegate()
{
    PhoneBook *pbook = PhoneBook::Instance();
    PhoneBook::Handlerfunc pf1 = [](const string &value)
    {
        cout << "i m first observer value is " << value << endl;
    };
    
    PhoneBook::Handlerfunc pf2 = [](const string &value)
    {
        cout << "i m second observer value is " << value << endl;
    };
    
    PhoneBookAssistant assistant;
    
    pbook->addObserver(pf1);
    pbook->addObserver(pf2);
    
    pbook->addPhoneBook(string("caichao"));
    
    pbook->removeObserver(pf1);
    
    pbook->addPhoneBook(string("chaocai"));
    
    pbook->removeObserver(pf2);
}

void testBoundsIterator()
{
    cout << "vector bounds iterator " << endl;
    vector<int> vi{10,20};
    
    for(int i : vi)
    {
        cout << i << ",";
    }
    cout << endl;
    
    
    cout << "map bounds iterator " << endl;
    
    map<string,string> mp
    {
        {"123","caichao"},
        {"124","chaocai"}
    };
    
    for (auto &itr : mp) //以引用的方式进行遍历，可以对值进行修改
    {
        itr.second = itr.second + "__tag";
    }
    
    for (auto itr : mp)
    {
        cout << "key : " << itr.first << ",value : " << itr.second << ";";
    }
    cout << endl;
    
}

void testIntVector()
{
    cout << "use for(:) with my container " << endl;
    IntVector100 iv;
    
    for(auto &itr : iv)
    {
        itr = itr*10;
    }
    
    for(auto itr : iv)
    {
        cout << itr << ",";
    }
    cout << endl;
    
    
    int data[10] = {0};
    for(auto tm : data)
    {
        
    }
    
    
}

//example for constexpr
int getArraySize(int multiplier)
{
    return 4*multiplier;
}

constexpr int multiply(int x ,int y)
{
    return x * y;
}

constexpr int factorial(int n)  //递归不受影响
{
    return n > 0? n*factorial(n - 1) : 1;
}

class Circle
{
    double radius;
public:
    constexpr explicit Circle(double ra):radius(ra){}
    constexpr double getArea() const
    {
        return 3.14*3.14*radius;
    }
};


void testConstexpr() //感觉 constexpr 只是对 const 在表达式层面的扩展
{
    //这里仅仅测试一下区别，无关程序正确性
    //constexpr int cm = getArraySize(3);
    //constexpr int cm[getArraySize(2)];
    int cm[multiply(1,2)];
    //constexpr 正对表达式，函数，普通常量变量上面，同const没有多大区别, 该函数只能有一个return(存在特例) 只能调用其他constexpr函数，类似class 中的 static 函数，只能使用全局的constexpr变量???，在函数内部递归不受限制
    //如果需要在编译期间就得到值，需要将函数声明为constexpr 对于class 中的成员函数一样；
    //constexpr 支持浮点计算 double float
    
    
    const int *pc = nullptr; //指向常量的指针
    int* const cp = nullptr; // 常量指针
    constexpr int *qc = nullptr; // 常量指针
    //int* constexpr cq = nullptr;
    const constexpr int *qp = nullptr; //指向常量的常量指针
    const int* const qqp = nullptr;  //指向常量的常量指针
    //qqp = (int*)1;
    //*qqp = 1;
    //qp = (int*)1;
    //*qp = 1;
    pc = (int*)1;
    //*pc = 1;
    //cp = (int*)1;
    *cp = 2;
    //qc = (int*)1;
    *qc = 1;
}



//void reference_overload(string &str)
//{
//    cout << setw(15) << str << "==>" << "type & " << endl;
//}

void reference_overload(string &&str)
{
    cout << setw(15) << str << "==>" << "type && " << endl;
}

void reference_overload(string const &str)
{
    cout << setw(15) << str << "==>" << "type const & " << endl;
}

//void reference_overload(string const &&str)
//{
//    cout << setw(15) << str << "==>" << "type const && " << endl;
//}

string const getconststring()
{
    return string("const value");
}



string const getrlstring()
{
    string &&mm("china");
    return mm;
}

CString getCString()
{
    CString &&str("jiaoyonggong");
    return str;
}

void testRValueReference()
{
    //左值右值都是相对于表达式而言的，左值指表达式结束后依然存在的对象，右值则是表达式结束后就不在存在的临时对象
    //区分左值右值的方法是看能不能对表达式取地址，如果能，则为左值，否则为右值
    //左值引用根据修饰符不同，可以分为常量左值和非常量左值
    //非常量左值只能绑定到非常量左值，不能绑定到常量左值、常量右值和非常量右值
    //如果允许绑定到常量左值，常量右值，则非常量引用可以用于修改常量左值和常量右值，这明显违背了常量的定义；如果允许
    //绑定到非常量右值，则会导致危险的情况出现，因为右值是一个临时的对象，非常量左值引用可能会使用一个已经被销毁了的
    //临时对象;常量左值引用可以绑定到所有类型的值，包括非常量左值，常量左值，非常量右值，常量右值
    //可以看出，使用左值引用的时候，我们无法区分处绑定的是否是非常量右值的情况
     
    //但是如果临时对象通过一个接受右值的函数传递给另一个函数时，就会变成左值，因为这个临时对象在传递过程中，变成了命名对象。
    
    //左值／右值和 const/non-const。 精确传递就是在参数传递过程中，所有这些属性和参数值都不能改变。在泛型函数中，这样的需求非常普遍。
    //C++11 中定义的 T&& 的推导规则为：
    // 右值实参为右值引用，左值实参仍然为左值引用。
    //一句话，就是参数的属性不变。这样也就完美的实现了参数的完整传递。
    //右值引用，表面上看只是增加了一个引用符号，但它对 C++ 软件设计和类库的设计有非常大的影响。它既能简化代码，又能提高程序运行效率。每一个 C++ 软件设计师和程序员都应该理解并能够应用它。我们在设计类的时候如果有动态申请的资源，也应该设计转移构造函数和转移拷贝函数。在设计类库时，还应该考虑 std::move 的使用场景并积极使用它。
    
    int &&a = 10; //右值引用
    string lv("lvalue");
    string const clvalue("const lvalue");
    reference_overload(lv);
    reference_overload(clvalue);
    reference_overload(string("rvalue"));
    reference_overload(getconststring());
    
    CString c1("abcdefg");
    CString c2(c1);
    CString c3(std::move(CString("abccccc")));
    CString c4;
    c4 = std::move(c2);
    
    CString &&c5("12345");
    CString c6;
    //c6 = c5;
    
    c6 = getCString();
    CString c7("abc");
    vector<CString> vc;
    vc.push_back(c7);
    vc.push_back(CString("niub"));
    //vc.push_back(c7);
    
}

void testEnum()
{
    enum class color : int; //前置声明,带上class 的enum不再是全局可见的了
    
    enum class color : int
    {
        red,
        blue,
        white
    };
    
    //int ea = red;
    
    //int eb = color::red;
    
    int ec = static_cast<int>(color::red); //正确使用方式
    
    
    
    typedef enum : unsigned { //可以指定enum的类型
        MyEnumValueA,
        MyEnumValueB,
        MyEnumValueC,
    } MyEnum;
    
    enum class MyEnumX : int
    {
        
    };
    
    typedef enum : char // 只限于基本类型
    {
        
    }MyEnumString;
    
    
}

int getMaxGap(int *arr,const int size)
{
    //给定数组B 求得数组中 a - b 的最大差值  其中数组B中 a 在 b 的右边 （这是有顺序的）
    if(arr == nullptr || size <= 0)
    {
        return 0;
    }
    
    int maxBefore = arr[0];
    int maxGap = 0;
    for (int i = 1; i < size ; i++)
    {
        int temp = maxBefore - arr[i];
        if(temp > maxGap)
        {
            maxGap = temp;
        }
        if(arr[i] > maxBefore)
        {
            maxBefore = arr[i];
        }
    }
    return maxGap;
}

void testAQuestion()
{
    int arr[4] = {5,7,6,9};
    cout << "maxGap in arr is " << getMaxGap(arr, 4) << endl;
}

void testBinaryOp()
{
    std::equal_to<int> equality; //相等判断
    std::binary_negate< std::equal_to<int> > nonequality (equality); //取反，相反
    int foo[] = {10,20,30};
    int bar[] = {0,15,30};
    std::pair<int*, int*> firstmatch,firstmismatch;
    firstmismatch = std::mismatch(foo, foo+3, bar, equality); //同时遍历2个数组
    firstmatch = std::mismatch(foo, foo+3, bar, nonequality);
    cout << "first mismatch is " << firstmismatch.second << endl;
    cout << "first match is " << firstmatch.second << endl;
}

void testBindAndFunctional()
{
    //STD::BIND 可以帮到全局函数，类函数，虚函数，静态函数
    //unction模板类和bind模板函数，使用它们可以实现类似函数指针的功能，但却却比函数指针更加灵活，特别是函数指向类 的非静态成员函数时。
    //std::function可以绑定到全局函数/类静态成员函数(类静态成员函数与全局函数没有区别),如果要绑定到类的非静态成员函数，则需要使用std::bind。
    
    
//    typedef std::function<void ()> fp;
//    void g_fun()
//    {
//        cout<<"g_fun()"<<endl;
//    }
//    class A
//    {
//    public:
//        static void A_fun_static()
//        {
//            cout<<"A_fun_static()"<<endl;
//        }
//        void A_fun()
//        {
//            cout<<"A_fun()"<<endl;
//        }
//        void A_fun_int(int i)
//        {
//            cout<<"A_fun_int() "<<i<<endl;
//        }
//        
//        //非静态类成员，因为含有this指针，所以需要使用bind
//        void init()
//        {
//            fp fp1=std::bind(&A::A_fun,this);
//            fp1();
//        }
//        
//        void init2()
//        {
//            typedef std::function<void (int)> fpi;
//            //对于参数要使用占位符 std::placeholders::_1
//            fpi f=std::bind(&A::A_fun_int,this,std::placeholders::_1);
//            f(5);
//        }
//    };
//    int main()
//    {
//        //绑定到全局函数
//        fp f2=fp(&g_fun);
//        f2();
//        
//        //绑定到类静态成员函数
//        fp f1=fp(&A::A_fun_static);
//        f1();
//        
//        A().init();
//        A().init2();
//        return 0;
//    }
    
}

void testNewFeature()
{
    cout<< "new Feature Test Begin!" <<endl;
    
    testAutoKeyWord();
    
    testDecltype();
    
    testAutoRefPtr();
    
    testLumbdaExpression();
    
    testLambdaDelegate();
    
    testBoundsIterator();
    
    testIntVector();
    
    //testConstexpr();
    
    testAQuestion();
    
    testRValueReference();
    
    cout<< "new Feature Test End!" <<endl;
}