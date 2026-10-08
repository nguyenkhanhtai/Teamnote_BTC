#include <bits/stdc++.h>
  // Use: auto value = evaluate_expression("2*(3+4)");

// + - * / ^, parentheses, unary signs; ^ is right-associative.
// Throws invalid_argument on syntax errors, domain_error on undefined arithmetic.
struct ExpressionParser {
    std::vector<long double> values; std::vector<char> ops;
    int precedence(char op) {
        if (op == '^') return 4;
        if (op == 'n' || op == 'p') return 3;
        if (op == '*' || op == '/') return 2;
        if (op == '+' || op == '-') return 1;
        return 0;
    }
    void syntax() { throw std::invalid_argument("expression syntax"); };
    void apply() {
        char op = ops.back(); ops.pop_back();
        if (values.empty()) syntax();
        long double b = values.back(); values.pop_back();
        if (op == 'n' || op == 'p') {
            values.push_back(op == 'n' ? -b : b); return;
        }
        if (values.empty()) syntax();
        long double a = values.back(); values.pop_back();
        if (op == '/' && b == 0) throw std::domain_error("division by zero");
        long double result = op == '+' ? a + b : op == '-' ? a - b :
            op == '*' ? a * b : op == '/' ? a / b : std::pow(a, b);
        if (!std::isfinite(result)) throw std::domain_error("nonfinite result");
        values.push_back(result);
    }
    long double evaluate(const std::string& text) {
    bool operand = true;
    for (size_t i = 0; i < text.size();) {
        char c = text[i];
        if (std::isspace(static_cast<unsigned char>(c))) { ++i; continue; }
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            if (!operand) syntax();
            char* end;
            long double value = std::strtold(text.c_str() + i, &end);
            if (end == text.c_str() + i || !std::isfinite(value)) syntax();
            i = static_cast<size_t>(end - text.c_str());
            values.push_back(value); operand = false; continue;
        }
        ++i;
        if (c == '(') {
            if (!operand) syntax();
            ops.push_back(c); continue;
        }
        if (c == ')') {
            if (operand) syntax();
            while (!ops.empty() && ops.back() != '(') apply();
            if (ops.empty()) syntax();
            ops.pop_back(); operand = false; continue;
        }
        if (c != '+' && c != '-' && c != '*' && c != '/' && c != '^') syntax();
        if (operand) {
            if (c != '+' && c != '-') syntax();
            ops.push_back(c == '-' ? 'n' : 'p'); continue;
        }
        while (!ops.empty() && ops.back() != '(' &&
               (precedence(ops.back()) > precedence(c) ||
                (precedence(ops.back()) == precedence(c) && c != '^'))) apply();
        ops.push_back(c); operand = true;
    }
    if (operand) syntax();
    while (!ops.empty()) {
        if (ops.back() == '(') syntax();
        apply();
    }
    if (values.size() != 1) syntax();
    return values.back();
    }
};
long double evaluate_expression(const std::string& text) {
    ExpressionParser parser; return parser.evaluate(text);
}
