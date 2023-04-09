// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

enum OperatorPriority {
    OPEN_PARENTHESIS = 0,
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
    TStack<char, 100> operatorStack;
    for (auto& op : inf) {
        int priority = getPriority(op);
        if (priority == -1) {
            postfix += op;
        }
        else {
            if (operatorStack.getTop() < priority || priority == OPEN_PARENTHESIS || operatorStack.isEmpty()) {
                operatorStack.push(op);
            }
            else if (op == ')') {
                char topOperator = operatorStack.getTop();
                while (getPriority(topOperator) >= priority) {
                    postfix += topOperator;
                    operatorStack.pop();
                    topOperator = operatorStack.getTop();
                }
                operatorStack.pop();
            }
            else {
                char topOperator = operatorStack.getTop();
                while (getPriority(topOperator) >= priority) {
                    postfix += topOperator;
                    operatorStack.pop();
                    topOperator = operatorStack.getTop();
                }
                operatorStack.push(op);
            }
        }
    }
    while (!operatorStack.isEmpty()) {
        postfix += operatorStack.getTop();
        operatorStack.pop();
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
