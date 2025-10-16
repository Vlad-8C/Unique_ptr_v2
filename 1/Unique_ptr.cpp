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
    int pos{0};
    int size{};
public:
    smart_array(int size_) : size{ size_ } { arr = new int(size); }

    void add_element(int var) 
    { 
        if (pos>=0 && pos < size) { arr[pos] = var; ++pos; }
        else throw EndMemory();
    }
    int get_element(int pos_) 
    {
        if (pos_>=0 && pos_ < size) return arr[pos_];
        else throw EndMemory();
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
        arr.add_element(14);
        arr.add_element(15);
        std::cout << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}