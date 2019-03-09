//
//  C11NewFeature.h
//  testCPP1
//
//  Created by caichao on 14-9-23.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__C11NewFeature__
#define __testCPP1__C11NewFeature__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

void testNewFeature();


class Person
{
public:
    enum PersonType {ADULT,CHILD,SENIOR};
    void setPersonType (PersonType psType);
    PersonType getPersonType() const;
    auto getPersonTypeLuma() -> PersonType const;
private:
    PersonType m_personType;
};

template <typename type>
class TestClass {
public:
    void Test1(type tt)
    {
        
        tt(string("abc"));
    }
};

class AddressBook
{
public:
    template<typename Func>
    vector<string> findMatchingAddressC98(Func func)  //模板可以储存函数指针，
    {
        vector<string> results;
        for(auto itr = std::begin(_addresses); itr != std::end(_addresses); ++itr)
        {
            if(func(*itr))
            {
                results.push_back(*itr);
            }
        }
        return results;
    }
    
    vector<string> findMatchingAddressC11(std::function<bool (const string&)> func)
    {
        vector<string> results;
        for(auto itr = std::begin(_addresses); itr != std::end(_addresses); ++itr)
        {
            if(func(*itr))
            {
                results.push_back(*itr);
            }
        }
        return results;
    }
    
    AddressBook(string str)
    {
        cout<< "use self construct class and param is " << str << endl;
        _addresses = {"a","b","c","def","nhk","nhk","nhk"};
    }
    
    AddressBook():AddressBook("abc")
    {
        
    }
    
private:
    vector<string> _addresses;
};

class PhoneBook //lambda 观察者测试
{
public:
    //typedef std::function<void (const string&)> Handlerfunc;
    // observer delegate
    typedef void(*Handlerfunc)(const string&);
    static PhoneBook* Instance()
    {
        static PhoneBook* instance = nullptr;
        if(!instance)
        {
            instance = new PhoneBook;
        }
        return instance;
    }
public:
    void addObserver(Handlerfunc hf)
    {
        _bookObservers.push_back(hf);
    }
    void removeObserver(Handlerfunc hf)
    {
        for(auto itr = _bookObservers.begin(); itr != _bookObservers.end(); itr++)
        {
            if(*itr == hf)
            {
                _bookObservers.erase(itr);
                break;
            }
        }
    }
    void addPhoneBook(const string &pb)
    {
        _phoneBooks.push_back(pb);
        notifyObserversDataDidChange(pb);
    }
    void removePhoneBook(const string &pb)
    {
        for(auto itr = _phoneBooks.begin(); itr != _phoneBooks.end(); itr++)
        {
            if(*itr == pb)
            {
                _phoneBooks.erase(itr);
                notifyObserversDataDidChange(pb);
                break;
            }
        }
    }
private:
    vector<Handlerfunc> _bookObservers;
    vector<string> _phoneBooks;
    void notifyObserversDataDidChange(const string &odd)
    {
        for(auto itr = std::begin(_bookObservers); itr != std::end(_bookObservers); itr++)
        {
            (*itr)(odd);
        }
    }
};

class PhoneBookAssistant
{
    PhoneBook::Handlerfunc pf;
public:
    void didPhoneBookDataChanged(const string& pbd)
    {
        cout << "PhoneBookAssistant didPhoneBookDataChanged" << endl;
    }
    PhoneBookAssistant()
    {
        pf = [](const string &value)
        {
            cout << "PhoneBookAssistant didPhoneBookDataChanged value is " << value << endl;
        };
        PhoneBook::Instance()->addObserver(pf);
    }
    virtual ~PhoneBookAssistant()
    {
        PhoneBook::Instance()->removeObserver(pf);
    }
};

//自定义容器，使用系统的迭代器
//使用 for(:)循环，需要容器需要实现begin end 方法，因为对for(:)来说这需要知道循环的起始点，结束点
//迭代器必须支持 ++ * != == 操作,在迭代器循环调用的过程中，需要使用这些操作符进行循环,知道了这些，就可以
//使用 for(:)方法了
template<typename value_type>
class MyIterator : public iterator<bidirectional_iterator_tag, value_type>
{
protected:
    value_type *current;
public:
    explicit MyIterator(value_type *v):current(v){}
    
    MyIterator(const MyIterator& mit):current(mit.current){}
    
    MyIterator &operator++()
    {
        ++current;
        return *this;
    }
    
    MyIterator operator++(int)
    {
        MyIterator tmp(*this);
        operator++();
        return tmp;
    }
    
    value_type &operator*() const
    {
        return *current;
    }
    
    bool operator == (const MyIterator<value_type> &ths) const
    {
        return current == ths.current;
    }
    
    bool operator != (const MyIterator<value_type> &ths) const
    {
        return current != ths.current;
    }
    
    MyIterator<value_type> &operator = (const value_type &value)
    {
        current = value;
        return *this;
    }
};

class IntVector100
{
    
public:
    typedef MyIterator<int> viterator;
    
    int get(int col)const
    {
        return data[col];
    }
    
    viterator begin()
    {
        return viterator(data);
    }
    viterator end()
    {
        return viterator(data+100);
    }
    
    IntVector100():IntVector100(string("abc"))
    {
        
    }
    IntVector100(const string &str)
    {
        for (int i = 0;i < 99 ;i++)
        {
            data[i] = i;
        }
    }
private:
    int data[100];
};


class CString
{
    char *m_pData;
public:
    CString(const char *pszC = nullptr)
    {
        cout << "construct cstring : ";
        if(pszC != nullptr)
        {
            cout << pszC << endl;
        }
        if (pszC == nullptr)
        {
            m_pData = new char[1];
            *m_pData = '\0';
        }
        else
        {
            m_pData = new char[strlen(pszC) + 1];
            strcpy(m_pData, pszC);
        }
    }
    
    CString(const CString &s)
    {
        cout << "copy construct : " << s.m_pData << endl;
        m_pData = new char[strlen(s.m_pData) + 1];
        strcpy(m_pData, s.m_pData);
    }
    
    //move 函数
    CString(CString &&s)
    {
        cout << "rvalue construct : " << s.m_pData << endl;
        m_pData = s.m_pData;
        m_pData = nullptr;
    }
    
    ~CString()
    {
        cout << "destruct cstring " << endl;
        delete[] m_pData;
        m_pData = nullptr;
    }
    
    CString &operator = (const CString &s)
    {
        cout << "lvalue operator = : " << s.m_pData <<endl;
        if (this != &s)
        {
            delete[] m_pData;
            m_pData = new char[strlen(s.m_pData) + 1];
            strcpy(m_pData, s.m_pData);
        }
        return *this;
    }
    
    CString &operator = (CString &&s)
    {
        cout << "rvalue operator = " << s.m_pData << endl;
        if (this != &s)
        {
            delete[] m_pData;
            m_pData = s.m_pData;
            s.m_pData = nullptr;
        }
        return *this;
    }
    
    // 可以看到，上面我们添加了move版本的构造函数和赋值函数。那么，添加了move版本后，对类的自动生成规则有什么影响呢？唯一的影响就是，如果提供了move版本的构造函数，则不会生成默认的构造函数。另外，编译器永远不会自动生成move版本的构造函数和赋值函数，它们需要你手动显式地添加。
    //当添加了move版本的构造函数和赋值函数的重载形式后，某一个函数调用应当使用哪一个重载版本呢？下面是按照判决的优先级列出的3条规则：
    //1、常量值只能绑定到常量引用上，不能绑定到非常量引用上。
    //2、左值优先绑定到左值引用上，右值优先绑定到右值引用上。
    //3、非常量值优先绑定到非常量引用上。
    //当给构造函数或赋值函数传入一个非常量右值时，依据上面给出的判决规则，可以得出会调用move版本的构造函数或赋值函数。而在move版本的构造函数或赋值函数内部，都是直接“移动”了其内部数据的指针（因为它是非常量右值，是一个临时对象，移动了其内部数据的指针不会导致任何问题，它马上就要被销毁了，我们只是重复利用了其内存），这样就省去了拷贝数据的大量开销。
    //一个需要注意的地方是，拷贝构造函数可以通过直接调用*this = s来实现，但move构造函数却不能。这是因为在move构造函数中，s虽然是一个非常量右值引用，但其本身却是一个左值（是持久对象，可以对其取地址），因此调用*this = s时，会使用拷贝赋值函数而不是move赋值函数，而这已与move构造函数的语义不相符。要使语义正确，我们需要将左值绑定到非常量右值引用上，C++ 11提供了move函数来实现这种转换，因此我们可以修改为*this = move(s)，这样move构造函数就会调用move赋值函数。
    //
    
};




void testIntVector();

#endif /* defined(__testCPP1__C11NewFeature__) */
