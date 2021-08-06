#include <iostream>
using namespace std;
int main() {

    int x;
    std::cin >> x;
    while(std::cin.fail()) {
        std::cout << "Error" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> x;
    }
    std::cout << x << std::endl;
    return 0;
}