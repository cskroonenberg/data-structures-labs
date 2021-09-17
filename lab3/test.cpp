#include<iostream>
#include<stdexcept>

int return_2() {
    int size = 1;
    if(size < 2) {
        throw std::runtime_error("EXCEPTION");
    }
    return 2;
}

int main() {
    /*try {
        int num = return_2();
    }
    catch (std::runtime_error e) {
        std::cerr << "ERROR: " << e.what();
    }*/
    int* m_arr = new int[5];
    int* m_arr2 = new int[5];
    std::cout << "m_arr[0]: " << m_arr[0] << '\n';
    for(int i = 0; i < 5; i++) {
        std::cout << "m_arr[" << i << "]: " << m_arr[i] << '\n';
        m_arr2[i] = m_arr[i];
    }
    for(int i = 0; i < 5; i++) {
        std::cout << "m_arr2[" << i << "]: " << m_arr2[i] << '\n';
    }
    return 0;
}