#include "circular_buffer.h"
#include <iostream>


template <class ValueType>
CircularBuffer<ValueType>::CircularBuffer() {
  const int stdCapacity = 2;
  buffer_ = new ValueType[stdCapacity];
  for (int i = 0; i < stdCapacity; i++) {
    buffer_[i] = ValueType();
  }
  capacity_ = stdCapacity;
  size_ = 0;
  firstIndex_ = 0;
}

template <class ValueType>
CircularBuffer<ValueType>::~CircularBuffer() {
  delete[] buffer_;
}


template <class ValueType>
CircularBuffer<ValueType>::CircularBuffer(
    const CircularBuffer<ValueType> &cb) {
  buffer_ = new ValueType[cb.capacity_];
  capacity_ = cb.capacity_;
  firstIndex_ = cb.firstIndex_;
  size_ = cb.size_;
  for (int i = 0; i < cb.size_; i++) {
    buffer_[(firstIndex_ + i) % capacity_] =
        cb.buffer_[(cb.firstIndex_ + i) % cb.capacity_];
  }
}

// explicit
// Конструирует буфер заданной ёмкости.
template <class ValueType>
CircularBuffer<ValueType>::CircularBuffer(int capacity) {
  buffer_ = new ValueType[capacity];
  this->capacity_ = capacity;
  size_ = 0;
  firstIndex_ = 0;
}

 // Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.
template <class ValueType>
CircularBuffer<ValueType>::CircularBuffer(int capacity, const ValueType &elem) {
buffer_ = new ValueType[capacity];
this->capacity_ = capacity;
size_ = capacity;
firstIndex_ = 0;
for (int i = 0; i < this->capacity_; i++) {
buffer_[(firstIndex_ + i) % this->capacity_] = elem;
}
}

// Доступ по индексу. Не проверяют правильность индекса.
template <class ValueType>
ValueType &CircularBuffer<ValueType>::operator[](int i) {
ValueType &element = buffer_[(firstIndex_ + i)%capacity_];
return element;
}

template <class ValueType>
const ValueType &CircularBuffer<ValueType>::operator[](int i) const {
    const ValueType &element = buffer_[(firstIndex_ + i)%capacity_];
    return element;
}

// Доступ по индексу. Методы бросают исключение в случае неверного индекса.
template <class ValueType>
ValueType &CircularBuffer<ValueType>::at(int i) {
    try {
        ValueType &element = buffer_[(firstIndex_ + i)%capacity_];
        return element;
    } catch (const std::out_of_range &other) {
        throw other;
    }
}

template <class ValueType>
const ValueType &CircularBuffer<ValueType>::at(int i) const {
    try {
        const ValueType &element = buffer_[firstIndex_ + i];
        return element;
    } catch (const std::out_of_range &other) {
        throw other;
    }
}

// Ссылка на первый элемент.
template <class ValueType>
ValueType &CircularBuffer<ValueType>::front() { 
    ValueType &firstElement = buffer_[firstIndex_];
    return firstElement;
}

template <class ValueType>
const ValueType &CircularBuffer<ValueType>::front() const {
    const ValueType &firstElement = buffer_[firstIndex_];
    return firstElement;
}

// Ссылка на последний элемент.
template <class ValueType>
ValueType &CircularBuffer<ValueType>::back() { 
    ValueType &lastElement = buffer_[(firstIndex_ + size_-1) % capacity_];
    return lastElement;
}

template <class ValueType>
const ValueType &CircularBuffer<ValueType>::back() const {
    const ValueType &lastElement = buffer_[(firstIndex_ + size_ - 1) % capacity_];
    return lastElement;
}

// Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
// переместится в начало аллоцированной памяти. Возвращает указатель
// на первый элемент.
template <class ValueType>
ValueType *CircularBuffer<ValueType>::linearize() {
    if (firstIndex_ != 0) {
        ValueType *temporaryBuffer = new ValueType[size_];
        for (int i = 0; i < size_; i++) {
          temporaryBuffer[i] = buffer_[(firstIndex_ + i) % capacity_];
        }
        for (int i = 0; i < size_; i++) {
          buffer_[i] = temporaryBuffer[i];
        }
        firstIndex_ = 0;
        delete [] temporaryBuffer;
    }
    return buffer_;
}

// Проверяет, является ли буфер линеаризованным.
template <class ValueType>
bool CircularBuffer<ValueType>::is_linearized() const {
    return firstIndex_ == 0;
}

// Сдвигает буфер так, что по нулевому индексу окажется элемент
// с индексом new_begin.
template <class ValueType>
void CircularBuffer<ValueType>::rotate(int new_begin) {
    if (new_begin == 0)
        return;
    ValueType *temporaryBuffer = new ValueType[size_];
    for (int i = 0; i < size_; i++) {
        temporaryBuffer[i] = buffer_[(firstIndex_ + i) % capacity_];
    }
    for (int i = 0; i < size_; i++) {
        buffer_[(capacity_ +firstIndex_ + i) % capacity_] = temporaryBuffer[(new_begin + i)%size_];
    }
    delete [] temporaryBuffer;
}

// Количество элементов, хранящихся в буфере.
template <class ValueType>
int CircularBuffer<ValueType>::size() const {
    return size_;
}
template <class ValueType>
bool CircularBuffer<ValueType>::empty() const {
    return size_ == 0;
}
// true, если size() == capacity().
template <class ValueType>
bool CircularBuffer<ValueType>::full() const {
    return size() == capacity();
}
// Количество свободных ячеек в буфере.
template <class ValueType>
int CircularBuffer<ValueType>::reserve() const {
    return capacity_ - size_;
}
// ёмкость буфера
template <class ValueType>
int CircularBuffer<ValueType>::capacity() const {
    return capacity_;
}

// установить ёмкость буффера
template <class ValueType>
void CircularBuffer<ValueType>::set_capacity(int new_capacity) {
    if (capacity_ == new_capacity)
        return;
    capacity_ = new_capacity;
    if (capacity_ <= size_){
        size_ = capacity_;
    }
    ValueType *newBuffer = new ValueType[new_capacity];

    for (int i = 0; i < size_; i++) {
        newBuffer[i] = buffer_[(firstIndex_ + i) % capacity_];
    }
    delete[] buffer_;
    buffer_ = newBuffer;
    firstIndex_ = 0;
}

// Изменяет размер буфера.
// В случае расширения, новые элементы заполняются элементом item.
template <class ValueType>
void CircularBuffer<ValueType>::resize(int new_size, const ValueType &item) {
    if (size_ < new_size) {
        if (capacity_ <= new_size)
          set_capacity(new_size);
        for (int i = size_ + 1; i < new_size; i++) {
          buffer_[(firstIndex_ + i) % capacity_] = item;
        }
    }
    size_ = new_size;
}

// Оператор присваивания.
template <class ValueType>
CircularBuffer<ValueType> &CircularBuffer<ValueType>::operator=(const CircularBuffer<ValueType> &cb) {
    //delete[] this->buffer_;
    buffer_ = new ValueType[cb.capacity_];
    capacity_ = cb.capacity_;
    firstIndex_ = cb.firstIndex_;
    size_ = cb.size_;
    for (int i = 0; i < cb.size_; i++) {
        buffer_[(firstIndex_ + i) % capacity_] =
            cb.buffer_[(cb.firstIndex_ + i) % cb.capacity_];
    }
    return *this;
}

// Обменивает содержимое буфера с буфером cb.
template <class ValueType>
void CircularBuffer<ValueType>::swap(CircularBuffer &cb) {
    ValueType *temporaryBuffer = buffer_;
    buffer_ = cb.buffer_;
    cb.buffer_ = temporaryBuffer;
    int temporaryCapacity = capacity_;
    capacity_ = cb.capacity_;
    cb.capacity_ = capacity_;
    int temporarySize = size_;
    size_ = cb.size_;
    cb.size_ = temporarySize;
}

// Добавляет элемент в конец буфера.
// Если текущий размер буфера равен его ёмкости, то переписывается
// первый элемент буфера (т.е., буфер закольцован).
template <class ValueType>
void CircularBuffer<ValueType>::push_back(const ValueType &item) {
    if (full()) {
        buffer_[firstIndex_] = item;
        firstIndex_ = (firstIndex_ + 1) % capacity_;
    } else {
        buffer_[firstIndex_ + size_] = item;
        size_++;
    }
}

// Добавляет новый элемент перед первым элементом буфера.
// Аналогично push_back, может переписать последний элемент буфера.
template <class ValueType>
void CircularBuffer<ValueType>::push_front(const ValueType &item) {
    if (!full())
        size_++;
    firstIndex_ = (capacity_ + firstIndex_ - 1) % capacity_;
    buffer_[firstIndex_] = item;
}

// удаляет последний элемент буфера.
template <class ValueType>
void CircularBuffer<ValueType>::pop_back() {
    if (!empty())
        size_--;
}

// удаляет первый элемент буфера.
template <class ValueType>
void CircularBuffer<ValueType>::pop_front() {
    if (!empty()) {
        size_--;
        firstIndex_ = (firstIndex_ + 1) % capacity_;
    }
}

// Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
template <class ValueType>
void CircularBuffer<ValueType>::insert(int pos, const ValueType &item) {
    try {
        at(pos) = item;
    } catch (const std::out_of_range &other) {
        throw other;
    }
}

// Удаляет элементы из буфера в интервале [first, last).
template <class ValueType>
void CircularBuffer<ValueType>::erase(int first, int last) {
    if (last > capacity_+1){
        last = capacity_ + 1;
    }
    for (int i = 0; i < capacity_ - last; i++) {
        buffer_[(firstIndex_ + first + i) % capacity_] =
            buffer_[(firstIndex_ + last + i) % capacity_];
    }
    size_ -= last - first;
}
// Очищает буфер.
template <class ValueType>
void CircularBuffer<ValueType>::clear() {
    size_ = 0;
    firstIndex_ = 0;
}

template <class X>
bool operator==(const CircularBuffer<X> &a, const CircularBuffer<X> &b) {
    if (a.capacity() != b.capacity())
        return false;
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size(); i++) {
        if (a.at(i) != b.at(i))
          return false;
    }
    return true;
}

template <class X>
bool operator!=(const CircularBuffer<X> &a, const CircularBuffer<X> &b) {
    if (a == b)
        return false;
    return true;
}


// block of instances
// This code instance templates for it's usable 
template class CircularBuffer<int>;
template class CircularBuffer<char>;
template class CircularBuffer<float>;
template class CircularBuffer<double>;
template class CircularBuffer<bool>;
template class CircularBuffer<long>;
template class CircularBuffer<long long>;
template class CircularBuffer<long double>;

template bool operator==
    <int>(const CircularBuffer<int> &a, const CircularBuffer<int> &b);
template bool operator!=
    <int>(const CircularBuffer<int> &a, const CircularBuffer<int> &b);

template bool operator==
    <double>(const CircularBuffer<double> &a, const CircularBuffer<double> &b);
template bool operator!=
    <double>(const CircularBuffer<double> &a, const CircularBuffer<double> &b);