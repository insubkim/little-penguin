#include <stdio.h>
#include <stddef.h>

typedef struct {
    int a;
    char b;
    double c;
    char d;
    char e;
    int f;
} MyStruct;

int main() {
    printf("a 멤버의 오프셋: %zu\n", offsetof(MyStruct, a));
    printf("b 멤버의 오프셋: %zu\n", offsetof(MyStruct, b));
    printf("c 멤버의 오프셋: %zu\n", offsetof(MyStruct, c));
    printf("d 멤버의 오프셋: %zu\n", offsetof(MyStruct, d));
    printf("e 멤버의 오프셋: %zu\n", offsetof(MyStruct, e));
    printf("f 멤버의 오프셋: %zu\n", offsetof(MyStruct, f));
    return 0;
}
