#include<iostream>
//#define DEBUG

using namespace std;
class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		this->pPrev = pPrev;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{

#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class List;
};
class List
{
	Element* Head;
	Element* Tail;
	int size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~List()
	{
		while (Head)pop_front();
		while (Tail)pop_back();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG
	}
	// Add element

	void push_front(int Data)
	{
		size++;
		if (Head == nullptr)
		{
			Head = Tail = new Element(Data);
			return;
		}
		//New->pNext = Head;
		//New->pPrev= New;
		//Head = New;
		Head = Head->pPrev = new Element(Data, Head);
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index > size)return;
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Index == size - 1)
		{
			push_back(Data);
			return;
		}
		Element* it;
		if (Index < size / 2)
		{
			it = Head;
			for (int i = 0; i < Index; i++)it = it->pNext;
		}
		else
		{
			it = Tail;
			for (int i = 0; i < size - Index - 1; i++)it = it->pPrev;
		}
		//Element* New = new Element(Data);
		//New->pPrev = it->pPrev;
		//New->pNext = it;
		//it->pPrev->pNext = New;
		//it->pPrev = New;
		it->pPrev = it->pPrev->pNext = new Element(Data, it, it->pPrev);
		size++;
	}
	//deleting elements:
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Element* it = Head->pNext;
		delete Head;
		Head = it;
		size--;

	}
	void pop_back()
	{
		if (Tail == Head)
		{
			pop_front();
			return;
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index == size - 1)
		{
			pop_back();
			return;
		}
		Element* it;
		if (Index < size / 2)
		{
			it = Head;
			for (int i = 0; i < Index; i++)it = it->pNext;

		}
		else
		{
			it = Tail;
			for (int i = 0; i < size - Index - 1; i++)it = it->pPrev;
		}
		Element* Del = it;
		it->pPrev->pNext = it->pNext;
		it->pNext->pPrev = it->pPrev;
		delete Del;
		size--;
	}
	//methods:
	void print()
	{
		Element* it = Head;
		while (it != nullptr)
		{
			cout << it->pPrev << "\t" << it << "\t" << it->Data << "\t" << it->pNext << endl;
			it = it->pNext;
		}
		cout << "Number of elements: " << size << endl;
	}
	void print_reverse()
	{
		Element* it = Tail;
		while (it != nullptr)
		{
			cout << it->pPrev << "\t" << it << "\t" << it->Data << "\t" << it->pNext << endl;
			it = it->pNext;
		}
		cout << "Number of elements: " << size << endl;
	}

};

void main() {
	setlocale(LC_ALL, "");
	int n;
	cout << "Input lsit size: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	/*list.push_front(3);
	list.push_back(3);*/
	list.print();
	//int Data;  // значение доб еллемента
	//int Index;
	//cout << "Input list Data: "; cin >> Data;
	//cout << "Input list Value: "; cin >> Index;
	//list.insert(Index,Data);
	//list.print();
	//list.pop_front();
	//list.print();
	/*list.pop_back();
	list.print();*/
	int Index;
	cout << "Input list Index: "; cin >> Index;
	list.erase(Index);
	list.print();
}