//
//  main.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/11.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include <iostream>
#include <string>
#include "test1.hpp"
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>
#include <mm_malloc.h>
#include <list>
#include <map>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "SalesItem.hpp"
#include "SalesPocket.hpp"
#include "Operator.hpp"
#include "Item_base.hpp"
#include <map>
#include "Template.hpp"
#include "ExceptionX.hpp"
#include "Memory.hpp"
#include "Advance.hpp"

using namespace std;



void testCommon()
{
    // insert code here...
    std::cout << "Hello, World!\n" << std::\
    endl;
    
    cerr << "Error world" << endl;
    
    string originalString = "originalString";
    
    /**
     *  全局extern string
     */
    extern const string str;
    
    cout << "" <<str << endl;
    
    /**
     *  绑定到 const 引用
     */
    const string &referString = originalString;
    
//    int m1 = 5; //不同类型const引用
//    double d1 = 9.0;
//    const double &referInt = &m1;
//    const int &referDouble = &d1;
    
    const int m2 = 5;
    const double &referM2 = m2; //const 类型不同的const对象绑定相关类型const
    
    //int &referM2NotConst = m2; //const 到notConst 引用
    
    cout << "referString = " << referString << endl;
    
    //cin >> m;
}

void testString()
{
    const string str("test");
    
    cout << str << endl;
    
    string mm;
    string nn;
    //cin >> mm >> nn;
   // cout << mm+nn << mm[1] << endl;
//
//    while (cin >> mm)
//    {
//        cout << mm << endl;
//    }
    
//    string line;
//    while (getline(cin, line)) //一次读取一行
//    {
//        cout << line << endl;
//    }
}

void testVector()
{
    vector<int> m;
    m.push_back(1);
    m.push_back(3);
    
    for (vector<int>::iterator beg = m.begin(); beg != m.end(); beg++)
    {
//        if (*beg == 1)
//        {
//            m.push_back(4); //遍历过程改变容器error
//        }
        cout << "vector : " << *beg << endl;
    }
    
    m[0] = 2;
    
    cout << m[0] << endl;
    
    bitset<32>(3);
    
    int array[] = {1,2,3};
    
    cout << array[0] << array[1] << endl;
    
    int *mp1 = &array[0],*mp2 = &array[1];
    cout << *mp1 << *mp2 << endl;
    int **mpp1 = &mp1;
    cout << *mpp1 << "   " << sizeof(mpp1) << "  " << **mpp1 << endl;
    ptrdiff_t ptrDiff = &array[0] - &array[1];
    cout << ptrDiff << endl;
}

void testConstPonter()
{
    //const指针和指向const的指针
    int const variable = 1;
    int const var = 2;
    int vari = 3;
    const int *m = &variable; //指向const的指针 ,指针的值可以修改，所指向的变量不能被修改
    int const *nn = &variable;
    //*m = 4; error
    m = &var;
    m= &vari;
   // *m = 5;
    
    const int *p = new const int(12); //const int 必须立马初始化
    delete p;
    
    int *const n = &vari; //const指针 指针不能被修改 但是值可以修改,指向的对象为非const得对象
    *n = 10;
    
    const int *const mx = &variable; //指针指向的类型为 const int ,指针也是const类型
    
    string str;
    
    typedef string* pString;
    
    const pString cstr = &str; // == string* const cstr
    
    typedef const string* pcString;
    
    const string str1 = "";
    
    const pcString ccstr = &str; // == const string* const ccstr ??
    
    const int *pArr = new const int[12](); //没什么卵用的数组,函数参数传递
    //pArr[1] = 1;
    
    const string *pStrings = new const string[12];
    
    delete[] pArr;
    
    //多维数组,数组在内存里面依然是个连续的区域，所以依然可以连续访问
    int mxx[2][2] = {{1,8},{1,6}};
    
    int (*pmu)[2] = mxx; //多维数组指针
    
    typedef int int_array[2]; //指针的类型 int[2]
    int_array *ppmu = mxx; //指向数组int[2] 的数组的指针
    
    int * ip[3]; // 指针数组，内部存放指针 int*
    
    cout << "xx" << (*(pmu + 1))[1] << endl;
    
    for (int i = 0; i < 4; i++)
    {
        //((*pmu)[i]) 相当于 mxx[0][i]
        cout << ((*pmu)[i]) << "  " << *(*pmu + i) << endl; // *pmu 相当于取得 mxx[0]的地址
    }
    
    int *pmmu = mxx[0]; //这里直接将mxx[0]地址获取到
    
    for (int i = 0; i < 4; i++)
    {
        cout << pmmu[i] << endl; // 数组访问的方式
    }
    
    const char *pstr = "test abc"; //C++ 的字符串 默认为 const char
    printf("%s \n",pstr);
    
    /**
     *  迷糊，多维字符串数组
     */
    char a[2][10] = {"hello", "hi"}; //2个字符串 hello\0 hi\0
    printf( "a[0] = %s\n", a[0] ); //打印字符串
    printf( "a[0][0] = %c\n", a[0][0] ); //打印字符
    printf( "*a = %s\n", *a ); //相当于 *a = a[0](hello)
    printf( "*a + 1 = %s\n", *a + 1 ); // a[0](hello) + 1 打印h 地址后的字符串
    printf( "*(a + 1) = %s\n", *(a + 1) ); // a == &a[0]
    printf( "a,&a[0] = %s %s \n",a,&a[0]);
    
    cout << sizeof(a) << "  " << sizeof(pmu) << "  " << sizeof(&mxx[0])  <<  "  " << sizeof(mxx) << endl;
    
    //sizeof 方法计算依赖本身对象的类型 例如 pmu 是 int[2] mxx 是 int[2][2] mxx[0] 是 int[2]
    //sizeof 返回数组的真实长度
    
    cout << &mxx[0] << "  " << mxx[0] << "  " << mxx << endl;
    
}

void testCast()
{
    int *ip = new int(2);
    char *pc = reinterpret_cast<char*>(ip);
    
    string ss(pc);
    
    cout << ss << endl;
    
    try {
        
    } catch (exception ex) {
        cout << ex.what() << endl;
    }
    
    cout<< __FILE__ << "\n" << __LINE__ << "\n" << __TIME__ << "\n" << __DATE__ << endl;
    
    
}

//数组传递是传递数组指针，*p 和 m[] 不知道数组长度 需要另外传入，动态性好，n[10]固定长度，只能传递固定长度进入
//数组引用，传递的数组，会做数组长度检查 int(&nRef)[10]
//多维数组传递int (*mx)[10]
//多维数组引用传递 int (* (&nx))[10] ？？
void testArrayParams(int *p,int n[10],int m[], int (&nRef)[10] ,int (*mx)[10])
{
    return;
}

//普通引用，const引用，const int* 指针的应用 对象数据不能修改 指针可以修改 int * const 指针 指针不可以该 值可以改
void testParams(int &m ,const string &n,const int* &pRef,int * const &pcRef,const int * const &cpcRef)
{
    m = 0;
    //n = "s";
    pRef = nullptr;
    //*pRef = 2;
    //pcRef = nullptr;
    *pcRef = 2;
    
    int nx[10] = {1,2,3,4};
    
    int nm[2][10]={{1,2},{3,4}};
    
    testArrayParams(nx, nx, nx,nx,nm);
}


inline int &testReturn(int m = 2) //默认形参 内敛函数
{
    //return 2; //不能返回局部对象的指针和引用
    return m;
}

inline int &testRF(double);

typedef int& (*pf1)(int); //函数指针
int * pf2(); //函数返回指针

//传递3个函数指针参数 前2种比较方便访问
void tt(pf1*pfn,bool(*m)(int n),bool(int m))
{
    m = nullptr;
}

pf1 ttt() //返回函数指针
{
    return nullptr;
}

void teststream() //stream 不可以复制
{
    wcout << L"ss" << endl;
    cout << L"SSSS"<<endl; //不能处理宽字符

    //cout.clear();
    
    //iostream iost;
    //ostream ostr(stdout);
    
//    ios_base::iostate
    //ios::goodbit
    fstream fs("");
    cout << fs.good() << endl;
    cout << fs.eof() << endl;
    //cout << fs.clear() << endl;
    cout << fs.rdstate() << endl;
    fs.setstate(ios::goodbit);
    cout << fs.rdstate() << endl;
    //cout << fs.rdbuf() << endl;
    
    int iVal;
//    while (cin >> iVal , !cin.eof())
//    {
//        if (cin.bad())
//        {
//            //throw runtime_error("io error");
//            cin.clear(ios::badbit);
//            continue;
//        }
//        
//        if (cin.fail())
//        {
//            cerr << "bad data try again" << endl;
//            cin.clear(ios::failbit);
//            break;
//        }
//    }
    
    
    cout << "first" << flush << "mbd" << ends; //不换行 加空格 ， flush 刷新缓冲区
    
    cout << unitbuf << "china" << nounitbuf << endl; //全量刷新
    
    cin.tie(&cout); //捆绑 每次输入都会刷新输出
    
    cout << "xfghkll";
    
    //cin >> iVal;
    
    fstream fstream("/Users/caichao/IProject/Demo/ReviewCPlusplus/test");
    if (fstream.is_open())
    {
        
        char bufff[100];
        
        fstream.read(bufff, 100); // the method of reading binary data,it also support string;
        
        fstream.seekg(0,ios::end); //in this way , i can get the file's length
        
        cout << "length of file " <<fstream.tellg() << endl;
        
        // ok let's recover the file input sequence pointer position
        
        fstream.seekg(0, ios::beg);
        
        string fString;
        
        while (!fstream.eof()) //
        {
            fstream >> fString; //the way of reading string which can read string word by word only
            cout << fString << "\t" << ends;
        }
        cout << endl << endl;
        
        
        //let's do the same recovery
        fstream.clear();
        fstream.seekg(0,ios::beg);
        
        char buff[100];
        
        while (!fstream.eof()) // brandnew way of reading string which returns string line by line,however if ur buff is not enough to contain the longest line of string ,which will result in error of stream!
        {
            fstream.getline(buff, 10);
            cout << buff << "\t" << ends;
            memset(buff, 0, 100);
            
            if (!fstream.eof() && fstream.fail()) //while the stream is in bad state, we can still use clear method make the stream works again,if we update the stream state ,the stream will be in non eof state ,so we check the stream is in eof state while updating the stream state
            {
                fstream.clear(ios::goodbit);
            }
        }
        cout << endl << endl;
        
        fstream.clear();
        fstream.seekg(0,ios::beg);
        while (getline(fstream, fString))
        {
            cout << fString << "\t";
        }
        cout << endl << endl;
        
        fstream.close();
        fstream.clear();
        fstream.open("");
        fstream.close();
    }
    
    string fstr;
    
    stringstream sst;
    
    sst << "test" << endl << "mm" << "nn"; //let's cache the string into stringstream's buff
    
    fstr = sst.str();
    
    getline(sst, fstr);
    
    sst >> fstr; //convert string caching in stringstream's buff to any type,for example int double or string and so on
    
    fstr = std::to_string(1); //insteading of taking advantage of simpler stringstream ,we can still make good use of original C methods
    
    sst.clear();
    
    const char *pBuf = "standford university";
    
    char *pnB = new char[20];
    
    int tLen = sizeof(pnB);
    
    /*(0)sizeof是运算符，不是函数；
    
    (1)sizeof不能求得void类型的长度；
    
    (2)sizeof能求得void类型的指针的长度；
    
    (3)sizeof能求得静态分配内存的数组的长度!
    
    (4)sizeof不能求得动态分配的内存的大小!
    
    (5)sizeof不能对不完整的数组求长度；
    
    (6)当表达式作为sizeof的操作数时，它返回表达式的计算结果的类型大小，但是它不对表达式求值！
    
    (7)sizeof可以对函数调用求大小，并且求得的大小等于返回类型的大小，但是不执行函数体！
    
     1、 结构体的大小等于结构体内最大成员大小的整数倍
     
     2、 结构体内的成员的首地址相对于结构体首地址的偏移量是其类型大小的整数倍，比如说double型成员相对于结构体的首地址的地址偏移量应该是8的倍数。
     
     3、 为了满足规则1和2编译器会在结构体成员之后进行字节填充！
     
    (8)sizeof求得的结构体(及其对象)的大小并不等于各个数据成员对象的大小之和！
    
    (9)sizeof不能用于求结构体的位域成员的大小，但是可以求得包含位域成员的结构体的大小*/
    
    struct tesstruct {
        bool m:1; // set bit length obviously , the bool only need one bit to make judgment!
    };
    
    delete[] pnB;
    
    int len = sizeof(pBuf); // error , we can only get the lenght of the char* pointer is 8 at 64bit mac ox
    
    int lenS = strlen(pBuf); // except sizeof method ,choosing strlen method alternately!
    
    //int memL =
    
    sst.write(pBuf, lenS);
    
    //sst << "new bie";
    
    sst >> fstr;
    
    sst.str(""); // we had better clear the cache of stringstream after we reuse the same object in case of out of memory
    
    fstr = sst.str();
    
    
    
    return;
}

void testContainer()
{
    char *words[] = {"sta","china","buck","mulligan","d"};
    size_t word_length = sizeof(words)/sizeof(char*);
    cout << "word length\t" << word_length << endl;
    
    list<string> wordslist(words,words+word_length); // what elemets could be putted in standard container have the most important two property,one is supporting copy,another is supporting assignment
    
    vector<int> m;
    m.reserve(2);
    
    map<int,int> map;
    
    pair<int , int> pari = make_pair(2, 2);
    
    map.insert(pari);
    
    list<int> mList = {1,2,3,2,3,2,4,2,3,1,2};
    vector<int> mVector;
    replace_copy(mList.begin(), mList.end(), back_inserter(mVector), 2, 100);
    
    vector<string> mInputVector;
    
    //its a convenient way to redirect our input to a container using stream_iterator
    //while u interrupt the input queue use command + d ,the input request will be invalid!
    copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(mInputVector));
    copy(mInputVector.begin(), mInputVector.end(), ostream_iterator<string>(cout,"\t"));
    
    cout << "\n\n";
    
    fstream fstream("/Users/caichao/IProject/Demo/ReviewCPlusplus/test");
    
    //another way of writing data to container just treating the istream_iterator as
    //the datasource of vector directly which is as same as above way
    vector<string> ftoContainer((istream_iterator<string>(fstream)),istream_iterator<string>());
    copy(ftoContainer.begin(), ftoContainer.end(), ostream_iterator<string>(cout,"\t"));
    
    cout << "\n\n";
    
    ostream_iterator<int> oi(cout,",");
    *oi = 5;
    *oi = 6;
    
    cin.clear();
    cin.sync();
    
    cout << "state = " << cin.good() << cin.bad() << cin.fail() << endl;
    
    istream_iterator<int> ii(cin);
    istream_iterator<int> eof;
    
    while (ii != eof)
    {
        cout << *ii++ << endl;
    }
    
    typedef bool (*com)(int,int);
    
    multimap<int, int, com> x; // custom compare func
    
    return;
}

void testClass()
{
    SalesItem sales("s");
    sales.testSameObj(string("")); // the string will result in the implicative conversion from string to Salesitem
    // in orider to deal with the wrong conversion , we should require the constructor called explicitly using explict mark
    
    const SalesPocket sp;
    sp.showItemsPrice();
}

void testTemplate()
{
    template1(2, 4);
    
    const string cstr("const string");
    string nstr("normal string");
    template1(cstr, nstr); // const is ignored , because the param will cp the original data
    template0(cstr, nstr); // the normal string will convert to const string
    
    int a[10],b[20];
    //template0(a, b); // the type of ref a is int[10] and another is int[20] so different type
    template1(a, b); // the array will convert to int*
    
    //template1(2, 2.0);
    
    
    template2(string());
    template4<int, 2>(4);
    
    int (*pfun)(int &m,int &n) = compareTemplate; // using a template method initialize a fun pointer
    // which has the same type of param
    
    //void (*pfun1)(int &m,int &n) = compareTemplate; // error
    
    sumtemplate<int>(1,2); //
    
    sumtemplate2<int,double,int>(1.2,2);
    
    char ca;char cb;
    compareN(ca,cb); // call the specified version of template
    //
    
    compareN(1, 2);
}

int main(int argc, const char * argv[]) {
//    
//    testString();
//    testCommon();
//    testVector();
//    testConstPonter();
//    testCast();
//    teststream();
//    testContainer();
//    int i =0;
//    string m;
//    const int n = 0;
//    const int * const p = new const int(2);
//    int * const pp = new int(1);
//    const int *ppp = new const int(3);
//    testParams(i, m, ppp, pp,p);
//    
//    pf1 pff = testReturn; //函数指针指向具体函数
//    //pf1 pfn = testRF; 参数必须精确匹配到
//    
//
    
   // testClass();
    
    //testFunctionObject();
    //testFunctionAdapter();
    //testConversionOperator();
    
   // testVirtualProperty();
    
   // testInheritedProperty();
    
    //testTemplate();
    
    //templateFriendFun();
    
    //testException();
    
    //testMemory();
    
    testAdvance();
    
    return 0;
}


