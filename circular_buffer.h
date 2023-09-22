#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER



template <class ValueType> class CircularBuffer {
  ValueType *buffer_;
  int capacity_;
  int size_;
  int firstIndex_;

public:
  CircularBuffer();
  ~CircularBuffer();
  CircularBuffer(const CircularBuffer &cb);

  // Конструирует буфер заданной ёмкости.
  explicit CircularBuffer(int capacity);
  // Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.
  CircularBuffer(int capacity, const ValueType &elem);

  // Доступ по индексу. Не проверяют правильность индекса.
  ValueType &operator[](int i);
  const ValueType &operator[](int i) const;

  // Доступ по индексу. Методы бросают исключение в случае неверного индекса.
  ValueType &at(int i);
  const ValueType &at(int i) const;

  ValueType &front(); // Ссылка на первый элемент.
  ValueType &back();  // Ссылка на последний элемент.
  const ValueType &front() const;
  const ValueType &back() const;

  // Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
  // переместится в начало аллоцированной памяти. Возвращает указатель
  // на первый элемент.
  ValueType *linearize();
  // Проверяет, является ли буфер линеаризованным.
  bool is_linearized() const;
  // Сдвигает буфер так, что по нулевому индексу окажется элемент
  // с индексом new_begin.
  void rotate(int new_begin);
  // Количество элементов, хранящихся в буфере.
  int size() const;
  bool empty() const;
  // true, если size() == capacity().
  bool full() const;
  int reserve() const;
  // ёмкость буфера
  int capacity() const;

  void set_capacity(int new_capacity);
  // Изменяет размер буфера.
  // В случае расширения, новые элементы заполняются элементом item.
  void resize(int new_size, const ValueType &item = ValueType());
  // Оператор присваивания.
  CircularBuffer &operator=(const CircularBuffer &cb);
  // Обменивает содержимое буфера с буфером cb.
  void swap(CircularBuffer &cb);

  // Добавляет элемент в конец буфера.
  // Если текущий размер буфера равен его ёмкости, то переписывается
  // первый элемент буфера (т.е., буфер закольцован).
  void push_back(const ValueType &item = ValueType());
  // Добавляет новый элемент перед первым элементом буфера.
  // Аналогично push_back, может переписать последний элемент буфера.
  void push_front(const ValueType &item = ValueType());
  // удаляет последний элемент буфера.
  void pop_back();
  // удаляет первый элемент буфера.
  void pop_front();

  // Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
  void insert(int pos, const ValueType &item = ValueType());
  // Удаляет элементы из буфера в интервале [first, last).
  void erase(int first, int last);
  // Очищает буфер.
  void clear();
};

template <class X>
bool operator==(const CircularBuffer<X> &a, const CircularBuffer<X> &b);

template <class X>
bool operator!=(const CircularBuffer<X> &a, const CircularBuffer<X> &b);

#endif