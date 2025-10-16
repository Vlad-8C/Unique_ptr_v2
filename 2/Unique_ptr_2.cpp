#include <iostream>

class EndMemory : public std::exception
{
public:
    const char* what() const override { return "End memory\n"; }
};

class smart_array
{
private:
    int* arr{};
    int pos{ 0 };
    int size{};
public:
    smart_array(int size_) : size{ size_ } { arr = new int[size]; }

    void add_element(int var)
    {
        if (pos < size) { arr[pos] = var; ++pos; }
        else throw EndMemory();
    }

    int get_element(int pos_)
    {
        if (pos_ < size) return arr[pos_];
        else throw EndMemory();
    }

    smart_array& operator =(const smart_array& obj) 
    {
        delete[] arr;
        pos = obj.pos;
        size = obj.size;
        arr = new int(size);
        for (int i = 0; i < obj.size; ++i)
        {
            arr[i] = obj.arr[i];
        }
        return *this;
    }
    ~smart_array() { std::cout << "Delete \n"; };
};

int main()
{
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;

        std::cout << "0: " << arr.get_element(0) << std::endl;
        std::cout << "1: " << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
