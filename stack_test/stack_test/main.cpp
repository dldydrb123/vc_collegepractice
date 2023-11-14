#include <iostream>

// 링크드 리스트의 노드를 나타내는 클래스
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// 스택을 나타내는 클래스
class Stack {
private:
    Node* top; // 스택의 맨 위를 가리키는 포인터

public:
    Stack() : top(nullptr) {}

    // 스택에 요소 추가
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // 스택에서 요소 제거
    void pop() {
        if (isEmpty()) {
            std::cout << "스택이 비어있습니다." << std::endl;
            return;
        }

        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // 스택의 맨 위 요소 반환
    int peek() {
        if (isEmpty()) {
            std::cout << "스택이 비어있습니다." << std::endl;
            return -1; // 혹은 다른 값을 리턴하거나 예외를 던질 수 있습니다.
        }

        return top->data;
    }

    // 스택이 비어있는지 확인
    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {
    Stack myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    std::cout << "Top of the stack: " << myStack.peek() << std::endl;

    myStack.pop();
    std::cout << "Top of the stack after pop: " << myStack.peek() << std::endl;

    myStack.pop();


    std::cout << myStack.peek();

    return 0;
}