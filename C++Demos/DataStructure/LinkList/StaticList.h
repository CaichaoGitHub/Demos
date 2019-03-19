//
// Created by caichao on 2019-03-18.
//

#ifndef DATASTRUCTURE_STATICLIST_H
#define DATASTRUCTURE_STATICLIST_H

class StaticList {

public:

    static void Test();

    StaticList();
    void Insert(int e,int index);
    void Delete(int index);

    void Traverse();

private:

    struct Node{
        int elem;
        int cur = 0;
    };

    int GetLength();
    int GetEmptyNode();
    void SaveEmptyNode(int &index);

    Node list_[100];
};

#endif //DATASTRUCTURE_STATICLIST_H
