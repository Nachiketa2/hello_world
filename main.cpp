#include <iostream>

int main() {
    double first{};
    double second{};
    char operation{};

    std::cout << "Enter an expression (number operator number): ";
    if (!(std::cin >> first >> operation >> second)) {
        std::cerr << "Invalid expression.\n";
        return 1;
    }

    switch (operation) {
    case '+':
        std::cout << first + second << '\n';
        break;
    case '-':
        std::cout << first - second << '\n';
        break;
    case '*':
        std::cout << first * second << '\n';
        break;
    case '/':
        if (second == 0) {
            std::cerr << "Cannot divide by zero.\n";
            return 1;
        }
        std::cout << first / second << '\n';
        break;
    default:
        std::cerr << "Unsupported operator. Use +, -, *, or /.\n";
        return 1;
    }

    return 0;
}
