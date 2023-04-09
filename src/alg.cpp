// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

enum OperatorPriority {
    OP = 0,
    CLOSE_PARENTHESIS = 1,
    ADDITION = 2,
    SUBTRACTION = 2,
    MULTIPLICATION = 3,
    DIVISION = 3
};

int getPriority(char oper) {
    std::pair<char, int> priority[6];
    switch (oper) {
    case'(':
        priority[0].first = '(';
        priority[0].second = 0;
    case')':
        priority[1].first = ')';
        priority[1].second = 1;
    case'+':
        priority[2].first = '+';
        priority[2].second = 2;
    case'-':
        priority[3].first = '-';
        priority[3].second = 2;
    case'*':
        priority[4].first = '*';
        priority[4].second = 3;
    case'/':
        priority[5].first = '/';
        priority[5].second = 3;
    }
    int prior = -1;
    for (int i = 0; i < 6; ++i) {
        if (oper == priority[i].first) {
            prior = priority[i].second;
            break;
        }
    }
    return prior;
}

std::string addSpaces(const std::string& s) {
    const int MIN_LENGTH = 2;
    if (s.length() <= MIN_LENGTH) {
        return s;
    }
    int n = MIN_LENGTH - s.length() % MIN_LENGTH;
    std::string result(s, 0, n);
    for (auto it = s.begin() + n; it != s.end();) {
        result += ' '; result += *it++;
    }
    return result;
}

std::string infx2pstfx(std::string inf) {
  std::string postfix;
    TStack<char, 100> operStack;
    for (auto& op : inf) {
        int pr = getPriority(op);
        if (pr == -1) {
            postfix += op;
        } else {
            if (operStack.getTop() < pr || pr == OP || operStack.isEmpty()) {
                operStack.push(op);
            } else if (op == ')') {
                char topOperator = operStack.getTop();
                while (getPriority(topOperator) >= pr) {
                    postfix += topOperator;
                    operStack.pop();
                    topOperator = operStack.getTop();
                }
                operStack.pop();
            } else {
                char topOperator = operStack.getTop();
                while (getPriority(topOperator) >= pr) {
                    postfix += topOperator;
                    operStack.pop();
                    topOperator = operStack.getTop();
                }
                operStack.push(op);
            }
        }
    }
    while (!operStack.isEmpty()) {
        postfix += operStack.getTop();
        operStack.pop();
    }
    postfix = addSpaces(postfix);
    return postfix;
}

int calculate(const int& a, const int& b, const char& oper) {
    switch (oper) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: break;
    }
    return 0;
}

int eval(std::string pref) {
  TStack<int, 100> operandStack;
    std::string num = "";
    for (size_t i = 0; i < pref.size(); i++) {
        if (getPriority(pref[i]) == -1) {
            if (pref[i] == ' ') {
                continue;
            } else if (isdigit(pref[i + 1])) {
                num += pref[i];
                continue;
            } else {
                num += pref[i];
                operandStack.push(atoi(num.c_str()));
                num = "";
            }
        } else {
            int b = operandStack.getTop();
            operandStack.pop();
            int a = operandStack.getTop();
            operandStack.pop();
            operandStack.push(calculate(a, b, pref[i]));
        }
    }
    return operandStack.getTop();
}
