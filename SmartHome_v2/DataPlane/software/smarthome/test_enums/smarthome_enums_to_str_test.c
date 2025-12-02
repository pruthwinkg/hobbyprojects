#include "../smarthome_essentials.h"
#include "smarthome_enums_to_str_test.h"

int main() {
    TestEnum test = Test2;
    printf("%d - %s\n", test, GetStringTestEnum(test));

    test = Test3;
    printf("%d - %s\n", test, GetStringTestEnum(test));

    test = Test4;
    printf("%d - %s\n", test, GetStringTestEnum(test));

    return 0;
}
