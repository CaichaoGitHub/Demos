//
//  UMLDiagram.hpp
//  testCPP1
//
//  Created by Caichao on 15/10/20.
//  Copyright © 2015年 caichao. All rights reserved.
//

#ifndef UMLDiagram_hpp
#define UMLDiagram_hpp

#include <stdio.h>


//http://www.open-open.com/lib/view/open1328059700311.html

/**
 
 泛化 = 继承： 表示一般与特殊的关系，它指定了子类如何特化父类的所有特征和行为。
 例如老虎是动物的一种
 带三角箭头实线，箭头指向父类
 
 实现：抽象接口有不同的实现 表示类是接口所有特征和行为的实现.
 带三角箭头的虚线，箭头指向接口
 
 关联 = 成员变量：拥有关系，即一个类知道另一个类的接口，可以是双向或者单向，例如老师和学生，丈夫和妻子
 双向的关联可以有两个箭头或者没有箭头，单向的关联有一个箭头
 自身关联箭头指向自己
 带普通箭头的实线，箭头指向被拥有者
 
 依赖 = 局部变量、方法的参数或者对静态方法的调用：是一种使用的关系，即一个类的实现需要另一个类的协助，所以要尽量不使用双向的互相依赖.
 例如现代人依赖计算机
 带普通箭头的虚线，指向被使用者
 
 聚合 = 成员变量：是整体与部分的关系，且部分可以离开整体而单独存在。如车和轮胎是整体和部分的关系，轮胎离开车仍然可以存在。
 一头空心菱形，一头普通箭头，菱形指向整体
 
 组合 = 成员变量：是整体与部分的关系，但部分不能离开整体而单独存在。如公司和部门是整体和部分的关系，没有公司就不存在部门。
 一头实心菱形，一头普通箭头，菱形指向整体

 强弱顺序 ：泛化 = 实现 > 组合 > 聚合 > 关联 > 依赖
 
 */

#endif /* UMLDiagram_hpp */








