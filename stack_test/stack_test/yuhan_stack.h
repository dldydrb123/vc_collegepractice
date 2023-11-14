#pragma once
#include <iostream>
using namespace std;
class y_stack {

public:
	y_stack();
	~y_stack();

	void create_stack(int size);
	void push(int vlaue);
	void pop();
	void top();


private:
	int* data; //스택용 메모리 포인터
	int stack_size; //스택 사이즈
	int stack_count; // 저장된 데이터 개수
};

//생성자
y_stack::y_stack() {
	//초기화
	stack_size = 0;
	stack_count = 0;
	data = NULL;
}

//소멸자
y_stack::~y_stack() {
	if (data != NULL) {
		//data 존재 ===> 삭제
		delete[] data;
	}
}

void y_stack::create_stack(int size) {
	if (data != NULL) {
		//data 존재 ===> 삭제
		delete[] data;
		stack_size = size;
		data = new int[stack_size];
	}
}

void y_stack::push(int value) {
	//빈공간 있으면
	if (stack_count < stack_size) {
		//스택 인덱스 값만큼 더해서 value넣기
		*(data + stack_count) = value;
		//count 1 증가
		stack_count++;

	}
	else {
		cout << "stack 가득 참" << endl;
	}
}

void y_stack::pop() {
	//저장된 stack없으면
	if (stack_count == 0) {
		cout << "stack에 저장된 값 없음" << endl;
	}
	else {
		cout << "pop됨" << endl;
		//마지막 값 0으로 만들고 stack_count 감소
		data[stack_count--] = 0;

	}
}

void y_stack::top() {
	if (stack_count == 0) {
		cout << "stack에 저장된 값 없음" << endl;
	}
	else {
		cout << "top의 값 " << endl;
		for (int i = 0; i < stack_count; i++) {
			cout << " = " << data[i - 1] << endl;
		}
	}

}