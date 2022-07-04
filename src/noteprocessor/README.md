<h1>Problem:</h1>

Where is 2 classes in 4 files (Есть два класса в 4-х файлах):

 1. a.h

```c++
template<class T>
class A {
public:
  void use(const T&);
};
```

2. a.cpp

```c++
template<class T>
void A<T>::use(const T&) {//...}
```
3. b.h

```c++
class B : public A<B> {
void print();
};
```

4. b.cpp

```c++
void B::print() {//...}
```

<p>I understand that the linker should throw an error here, because an instance of class ```A<B>``` has not been created. But I can’t understand how to solve it, I know that the easiest way is to just get rid of .cpp files, but this is not an option (Я понимаю, что линкер должен кидать тут ошибку, потому что экземпляр класса ```A<B>``` не создан. Но как ее решить я не могу понять, знаю что наипростейший способ - это просто избавиться от .cpp файлов, но это не вариант).</p>

<p>And I know about this (Еще знаю о конструкции):</p>

```c++
template class A<b>;
```

<p>But she didn't help either. I don't really know where to place it. (Но и она не помогла. Точнее я не знаю куда ее расположить.)</p>

Error:

```
    Undefined symbols for architecture x86_64:
      "Writable<WritableArray>::copy(WritableArray const&)", referenced from:
          WritableArray::copy() in writablearray.cpp.o
      "Writable<WritableArray>::read(unsigned char*)", referenced from:
          WritableArray::readData(unsigned char*) in writablearray.cpp.o
      "Writable<WritableArray>::write(unsigned char*)", referenced from:
          WritableArray_test() in main.cpp.o
          WritableArray::writeData(unsigned char*) in writablearray.cpp.o
      "Writable<WritableArray>::setName(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >)", referenced from:
          WritableArray_test() in main.cpp.o
      "Writable<WritableArray>::Writable(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >)", referenced from:
          WritableArray::WritableArray(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >) in writablearray.cpp.o
      "Writable<WritableArray>::Writable()", referenced from:
          WritableArray::WritableArray() in writablearray.cpp.o
      "Writable<WritableArray>::~Writable()", referenced from:
          WritableArray::~WritableArray() in writablearray.cpp.o
          WritableArray::copyData(WritableArray const&) in writablearray.cpp.o
          WritableArray::copyData(WritableArray&&) in writablearray.cpp.o
      "Writable<WritableArray>::~Writable()", referenced from:
          WritableArray::~WritableArray() in writablearray.cpp.o
    ld: symbol(s) not found for architecture x86_64
    clang: error: linker command failed with exit code 1 (use -v to see invocation)
    make[2]: *** [test.out] Error 1
    make[1]: *** [CMakeFiles/test.out.dir/all] Error 2
    make: *** [all] Error 2
```