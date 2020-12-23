#pragma once
template<class T>
class List
{
private:
	// Вспомогательный класс
	class Node
	{
	public:
		Node(T val, Node* next = nullptr, Node* prev = nullptr) : val(val), next(next), prev(prev) {}
		Node(Node* next, Node* prev) : next(next), prev(prev) {}
		Node() : next(nullptr), prev(nullptr) {}
		~Node() {}

		T val;
		Node* next;
		Node* prev;
	};
private:
	Node* head; // Указатель на начало списка
	Node* tail; // Указатель на конец списка
	int _size; // Размер списка
public:
	List() : head(new Node), tail(head), _size(0) {}
	List(const List& list) : head(new Node), tail(head), _size(0)
	{
		for (Node* it = list.head; it != list.tail; it = it->next)
		{
			push(it->val);
		}
	}
	~List()
	{
		if (!empty())
		{
			Node* it = tail;
			do
			{
				it = it->prev;
				delete it->next;
			} while (it != head);
		}
		delete head;
		tail = head = nullptr;
		_size = 0;
	}

	// Проверка на пустоту списка
	bool empty() const
	{
		return head == tail;
	}
	
	// Возвращает размер
	int size() const
	{
		return _size;
	}

	// Очищает список
	void clear()
	{
		if (!empty())
		{
			Node* it = tail;
			do
			{
				it = it->prev;
				delete it->next;
			} while (it != head);
		}
		tail = head;
		_size = 0;
	}
	
	// Добавляет элемент в конце списка
	void push(const T& val)
	{
		tail->val = val;
		tail->next = new Node(nullptr, tail);
		tail = tail->next;
		++_size;
	}
	
	// Удаляет элемент из конца списка
	T pop()
	{
		tail = tail->prev;
		T val = tail->val;
		delete tail->next;
		tail->next = nullptr;
		--_size;
		return val;
	}
	
	// Добавляет элемент в место, заданное индексом
	void append(const T& val, int index)
	{
		if (index < 0 || index > _size)
			throw "Illegal index";
		if (index == _size)
		{
			push(val);
			--_size;
		}
		else if (index == 0)
		{
			Node* tmp = new Node(val, head, nullptr);
			head->prev = tmp;
			head = tmp;
		}
		else
		{
			int i;
			Node* it;
			for (it = head->next, i = 1; i < _size; ++i, it = it->next)
			{
				if (i == index)
				{
					Node* tmp = new Node(val);
					tmp->prev = it->prev;
					it->prev = tmp;
					tmp->prev->next = tmp;
					tmp->next = it;
					break;
				}
			}
		}
		++_size;
	}
	
	// Заменяет элемент в месте, заданном индексом
	void emplace(const T& val, int index)
	{
		if (index < 0 || index >= _size)
			throw "Illegal index";
		int i;
		Node* it;
		for (it = head, i = 0; i < _size; ++i, it = it->next)
		{
			if (i == index)
			{
				it->val = val;
				break;
			}
		}
	}
	
	// Удаляет элемент по заданному индексу
	T erase(int index)
	{
		if (index < 0 || index >= _size)
			throw "Illegal index";
		int i;
		Node* it;
		T val;
		if (index == 0)
		{
			val = head->val;
			Node* tmp = head;
			head = head->next;
			head->prev = nullptr;
			delete tmp;
		}
		else
		{
			for (it = head, i = 0; i < _size; ++i, it = it->next)
			{
				if (i == index)
				{
					val = it->val;
					it->prev->next = it->next;
					it->next->prev = it->prev;
					delete it;
					break;

				}
			}
		}
		--_size;
		return val;
	}
	
	List& operator=(const List& list)
	{
		if (this != &list)
		{
			if (!empty())
			{
				Node* it = tail;
				do
				{
					it = it->prev;
					delete it->next;
				} while (it != head);
			}
			delete head;
			tail = head = new Node;
			_size = 0;
			for (Node* it = list.head; it != list.tail; it = it->next)
			{
				push(it->val);
			}
		}
		return *this;
	}
	
	// Операторы сравнения
	bool operator==(const List& list) const
	{
		if (this != &list)
		{
			if (_size != list._size)
				return false;
			int i;
			Node* f;
			Node* s;
			for (f = head, s = list.head, i = 0; i < _size; ++i, f = f->next, s = s->next)
			{
				if (f->val != s->val)
					return false;
			}
		}
		return true;
	}

	bool operator!=(const List& list) const
	{
		return !(*this == list);
	}

	// Операторы доступа к элементам списка
	T& operator[](int index)
	{
		if (index < 0 || index >= _size)
			throw "Illegal index";
		int i;
		Node* it;
		for (it = head, i = 0; i < _size; ++i, it = it->next)
		{
			if (i == index)
				return it->val;
		}
	}

	const T& operator[](int index) const
	{
		if (index < 0 || index >= _size)
			throw "Illegal index";
		int i;
		Node* it;
		for (it = head, i = 0; i < _size; ++i, it = it->next)
		{
			if (i == index)
				return it->val;
		}
	}
};