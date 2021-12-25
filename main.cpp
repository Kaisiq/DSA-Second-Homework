#include <iostream>
#include "implementation/implementation.h"

int main() {
    Hierarchy poe("fiki");
    poe.hire("toni", "fiki");
    std::cout << poe.print() << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
