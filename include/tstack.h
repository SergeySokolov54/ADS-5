// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  private:
    T arr[size];  
    int top_index;  
public:
    TStack() :top_index(-1) {}  
    void push(T value) {
        if (isFull()) {
            throw std::string("Stack is full");  
        }
        else {
            arr[++top_index] = value;
        }
    }
    const T& pop() {
        if (isEmpty()) {
            throw std::string("Stack is empty");  
        }
        else {
            return arr[top_index--];
        }
    }
    bool isEmpty() const {  
        return top_index == -1;
    }
    bool isFull() const {
        return top_index == size - 1;
    }
    const T& getTop() const {  
        return arr[top_index];
    }
};

#endif  // INCLUDE_TSTACK_H_
