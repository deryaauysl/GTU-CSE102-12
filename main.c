#include "customDict.h"

int main()
{
    CustomDict *dict = create_dict();

    Value value1;
    value1.i = 10;
    add_item(dict, "key1", &value1, "int");

    Value value2;
    value2.f = 10.5;
    add_item(dict, "key2", &value2, "float");

    print_dict(dict);

    Value newValue;
    newValue.d = 100.5;
    set_value(dict, "key1", &newValue, "double");

    print_dict(dict);

    delete_item(dict, "key1");

    print_dict(dict);

    read_csv(dict, "data.csv");

    print_dict(dict);

    free_dict(dict);

    return 0;
}