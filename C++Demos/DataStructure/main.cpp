#include <iostream>
#include "OrderList/OrderList.h"
#include "LinkList/LinkList.h"
#include "LinkList/StaticList.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    OrderList::Test();
    LinkList::Test();
    StaticList::Test();

    return 0;
}