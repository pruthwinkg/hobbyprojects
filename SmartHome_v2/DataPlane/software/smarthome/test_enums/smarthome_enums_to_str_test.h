#include "../smarthome_enums_to_str.h"

BEGIN_ENUM(TestEnum) {
    ADD_ENUM(Test1)
    ADD_ENUM(Test2)
    ADD_ENUM_STR(Test3, "Test 3 string")
    ADD_ENUM_VAL_STR(Test4, 10, "Test 4 string")
    ADD_ENUM_VAL(Test5, 12)
} END_ENUM (TestEnum);

BEGIN_ENUM(TestEnum2) {
    ADD_ENUM(Test21)
    ADD_ENUM(Test22)
    ADD_ENUM_STR(Test23, "Test 3 string")
    ADD_ENUM_VAL_STR(Test24, 10, "Test 4 string")
} END_ENUM (TestEnum2);

