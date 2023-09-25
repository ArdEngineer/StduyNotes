# C\C++ 学习笔记--C指针的使用

这份笔记用于记录C\C++学习时的心得体会，以便后期快速回顾温习基础知识，加深对于C\C++高级使用方式的理解与运用

## 为什么说指针是C\C++最强大的一个特性？我是如何理解的？

正如“指针”二字所表明，在C语言中这一种变量犹如一个指针(pointer)一般，是可以随意“拨动”去“指向”在计算机存储单元中的某一个地址，这也是链表CRUD操作实现的一种最基本的思想，把指针这种可以“拨动”的特性理解和运用起来，实现和C指针相关的操作就会简单不少

## 我学到的指针有用的地方

指针最强大的地方在于，它可以用于对实体做出实际的修改。在其他语言中，向函数传递一个实体（传值），实际上传递的是该实体的副本，函数只对副本进行了修改而没办法对实体进行修改，但在C语言中，向函数传递实体的指针（即该实体在内存中的地址），函数就可以通过传入的地址对在该地址内的值进行实际修改大大节省了内存开销

基于上述特性，指针在以下方面可以大展身手：

1、实现链表的相关操作，包括创建、删除、插入、修改

2、在C语言中实现对字符串（相当于其它语言的string类型）的处理

3、在C语言中实现对数组、结构体等集合数据类型的简便操作

4、高效地实现函数对实体的实际修改（有时候可以不用返回值到函数体外）

## 以下是一些指针大显神通的用处示例（实现字符串复制、拼接，交换变量）

``` C++
//实现字符串的复制，要包含头文件assert.h
char* str_copy(char* tar_str, char* src_str){
    assert(tar_str != NULL && src_str != NULL);
    char *head_p = tar_str;

    while(*src_str != '\0'){
        *tar_str = *src_str;
        src_str++;
        tar_str++;
    }
    *tar_str = *src_str;

    return head_p;
}
```

``` C++
//实现字符串的拼接，要包含头文件assert.h
char* str_connect(char* str1, char* str2){
    assert(str1 != NULL && str2 != NULL);
    char* head_p = str1;
    while(*str1 != '\0'){
        str1++;
    }

    while(*str2 != '\0'){
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';

    return head_p;
}
```

``` C++
//实现两个变量的交换（经典问题），要包含头文件assert.h
int* change_seq(int* seq1, int* seq2, int seq_size){
    assert(seq1 && seq2 != NULL);
    int* head_p = seq2;

    int i = 0;
    for(; i < seq_size; i++){
        *(seq2 + i) = *(seq1 + seq_size - 1 - i);
    }
    return head_p;
}

//在主函数main中调用
int num1[4] = {1, 2, 3, 4}, num2[4];
change_seq(num1, num2, sizeof(num1) / sizeof(num1[0]));
int i = 0;
printf("Change result : ");
for(; i < sizeof(num1) / sizeof(num1[0]); i++){
    printf(" %d  ", *(num2 + i));
}
```

在上述例子中有几个重要的的知识点，务必牢记：

在向上述处理字符串的相关函数中传入数组时

``` C++
char *str1 = "Hello World!";
char str2[30];
printf("Copy result is : str2 = %s\n\n", str_copy(str2, str1));

char str_1[] = "Hello ";
char *str_2 = "World!";//实际上这里用可变的字符常量数组更加好 char str_2[]="World!"
printf("Connect result : %s\n", str_connect(str_1, str_2));
```

1、第一行和第六行的 str1 和 str_2实际上代表的是字符串常量，现行的C编译器为ANSI C编译器，该编译器不允许修改字符串常量。而在对字符串的操作中，一般使用char[]字符常量数组，这种数组的长度是可变的，因此日后使用时尽量少用char *object而使用char object[]的方式存储可变的字符串变量

2、但是使用之前要声明数组大小或者初始化数组，如上面代码的第2、4行所示

3、同时，只要传递数组的名称就行，在C语言中数组名称向函数传递时，实际上传递了该数组的首地址，这种传址是可以对传入的对象进行实际修改的，而非传值的方法只对传入对象的副本进行修改（参见代码第3，第7行）

## 共用体和结构体有什么区别？何时候用共用体？

使用共用体的几种常见情况：

1、需要在相同的内存空间中使用不同类型的数据时

2、共用体的所有字段共享同一块内存，但只能同时使用其中一个字段

3、共用体适合在某个特定时刻只需要存储一种类型的数据的情况

例如，共用体可以用于表示一个变量可以是整型、浮点型或字符型等不同类型数据

ex : 如果用户输入的数据有可能时整型、字符串、浮点型或者其他类型，并且每次都不同，那么这个时候就可以用共用体保存用户输入的数据.

explain : 如果用户输入的数据可能是不同类型的，而且每次输入的数据类型不同，可以使用共用体来保存用户输入的数据。

共用体的特点是它的字段共享同一块内存空间。因此，在每次用户输入数据时，您可以将不同类型的数据存储在共用体的不同字段中，然后根据需要访问适当的字段来解释和使用数据.

## C语言结构体数据类型以及链表的CRUD操作

1、什么是数据？ 数据是信息的载体，是描述客观事物属性的数、字符以及所有能输入到计算机中并被计算机程序识别和处理的集合

2、什么是数据结构？ 数据结构是指数据对象以及其中的相互关系和构造方法

3、什么是链表？ 链表是数据结构中的一种链式存储结构，简称为链表（link-list）

``` C++
//以下例子所用到的结构体的定义
struct Test{
    int num;
    struct Test *pNext;
};
```

### 动态创建一个链表

动态创建一个链表的函数如下：

``` C++
struct Test *createLinkList(){
    struct Test *pHead = NULL;
    struct Test *pTrail = NULL;

    while(1){
        struct Test *pNew = (struct Test*)malloc(sizeof(struct Test));
        printf("Enter the number(Enter 0 to exit): ");
        scanf("%d", &(pNew->num));
        pNew->pNext = NULL;
        
        if(pNew->num == 0){
            printf("Exit, data save successfully!\n");
            free(pNew);
            break;
        }
        
        if(pHead == NULL){
            pHead = pNew;
        }else{
            pTrail->pNext = pNew;
        }
        pTrail = pNew;
    }
    return pHead;
}
```

1、该函数最后向外返回该链表的启示指针，以便外部可以访问得到这个链表，这同时也决定了该函数的返回类型为struct Test*结构体指针类型

2、pTrail是用来追踪新插入的元素的地址

### 在链表的指定位置进行插入

### 删除链表中的指定元素
