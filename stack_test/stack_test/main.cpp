#include <iostream>

// ��ũ�� ����Ʈ�� ��带 ��Ÿ���� Ŭ����
class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// ������ ��Ÿ���� Ŭ����
class Stack {
private:
    Node* top; // ������ �� ���� ����Ű�� ������

public:
    Stack() : top(nullptr) {}

    // ���ÿ� ��� �߰�
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // ���ÿ��� ��� ����
    void pop() {
        if (isEmpty()) {
            std::cout << "������ ����ֽ��ϴ�." << std::endl;
            return;
        }

        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // ������ �� �� ��� ��ȯ
    int peek() {
        if (isEmpty()) {
            std::cout << "������ ����ֽ��ϴ�." << std::endl;
            return -1; // Ȥ�� �ٸ� ���� �����ϰų� ���ܸ� ���� �� �ֽ��ϴ�.
        }

        return top->data;
    }

    // ������ ����ִ��� Ȯ��
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