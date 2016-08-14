#include <stdio.h>

//__attribute__((aligned(n))) : 该声明将强制编译器确保（尽其所能）
//将其变量在分配空间时采用n字节对齐方式
typedef struct p {
    int  a;     //4
    char b;     //1
    short c;    //2
}__attribute__((aligned(8))) p; //sz: 8

//__attribute__((__packed__)): 使用该属性对struct/union类型定义
//使其变量中的值会紧紧的靠在一起
struct packed_struct {
    char c;     //1
    int i;      //4
}__attribute__((__packed__)); //sz: 5

int main() {
    printf("int'sz:%ld  void*'sz:%ld  char'sz:%ld  "
        "short'sz:%ld  "
        "long'sz:%ld  double'sz:%ld\n", 
        sizeof(int), sizeof(void*),
        sizeof(char), sizeof(short), sizeof(long),
        sizeof(double));
    
    printf("p'sz:%ld\n", sizeof(p));
    printf("packed_struct:%ld\n", sizeof(struct packed_struct));
    return 0;
}
