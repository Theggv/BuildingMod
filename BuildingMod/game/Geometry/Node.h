#ifndef _UTILITY_GEOMETRY_NODE_H_
#define _UTILITY_GEOMETRY_NODE_H_

#include <pch.h>

class Node {  //  Узел кольцевого двойного списка
protected:
	Node* _next;	// связь к последующему узлу
	Node* _prev;	// связь к предшествующему узлу
public:
	Node(void);
	virtual ~Node(void);
	Node* next(void);
	Node* prev(void);
	Node* insert(Node*);  // вставить узел после текущего
	Node* remove(void);// удалить узел из списка, возвратить его указатель
	void splice(Node*); // слияние/разделение кольцевых списков
};

#endif // !_UTILITY_GEOMETRY_NODE_H_
