#ifndef _UTILITY_GEOMETRY_NODE_H_
#define _UTILITY_GEOMETRY_NODE_H_

#include <pch.h>

class Node {  //  ���� ���������� �������� ������
protected:
	Node* _next;	// ����� � ������������ ����
	Node* _prev;	// ����� � ��������������� ����
public:
	Node(void);
	virtual ~Node(void);
	Node* next(void);
	Node* prev(void);
	Node* insert(Node*);  // �������� ���� ����� ��������
	Node* remove(void);// ������� ���� �� ������, ���������� ��� ���������
	void splice(Node*); // �������/���������� ��������� �������
};

#endif // !_UTILITY_GEOMETRY_NODE_H_
