// List.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

struct Node
{
    std::string data = "";
    Node* ptr = nullptr;
};

void AssignNewNode(Node*& ptr)
{
    ptr = new Node;
    if (!ptr) // То же самое, что if ( ptr == nullptr )
    {
        std::cout << "Извините, недостаточно оперативной памяти";
        exit(1);
    }
}


void AssignList(Node*& list)
{
    Node* currentNode = nullptr;
    Node*  lastNode = nullptr;
    AssignNewNode(list);
    std::cout << "Введите первое слово";
    std::cout << "(или '.' для завершения списка): ";
    std::cin >> list->data;
    if (list->data == ".")
    {
        delete list;
        list = nullptr;
    }
    currentNode = list; /* СТРОКА 13 */
    while (currentNode != nullptr)
    {
        AssignNewNode(lastNode);
        std::cout << "Введите следующее слово";
        std::cout << "(или '.' для завершения списка): ";
        std::cin >> lastNode->data;
        if (lastNode->data == ".")
        {
            delete lastNode;
            lastNode = nullptr;
        }
        currentNode->ptr = lastNode;
        currentNode = lastNode;
    }
}

void add_after(Node*& list, char a_word[], char word_after[])
{
    // преобразование массива char к строкам
    std::string word(a_word);
    std::string word2(word_after);
    
    //создаём новую переменную для list иначе список исчезнет
    Node* a_list = list;
    // пока не закончился список или 
    //пока не нашли элемент после которого нужно добавить элемент
    while (a_list && a_list->data != word)
    {
        // идем по списку сворачивая его
        a_list = a_list->ptr;
    }
    // если элемент найден
    if (a_list)
    {
        // запоминаем значение следуещего элемента
        Node* buf = a_list->ptr;
        // вставляем пустой элемент
        a_list->ptr = new Node;
        // заполняем его
        a_list->ptr->data = word2;
        // делаем связь с последующим элементом
        a_list->ptr->ptr = buf;
    }
    
}

void delete_after(Node*& list, char a_word[])
{
    
    std::string word(a_word);
    Node* a_list = list;
    while (a_list->ptr && a_list->ptr->data != word)
    {
        a_list = a_list->ptr;
    }
    if (a_list->ptr)
    {

        Node* del = a_list->ptr;
        a_list->ptr = a_list->ptr->ptr;
        delete del;
    }

}

void print_list(Node* list) 
{
    while (list) 
    {
        std::cout << list->data << " ";
        list = list->ptr;
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    Node* list = nullptr;
    
    AssignList(list);
    std::cout << "\nТЕКУЩЕЕ СОДЕРЖИМОЕ СПИСКА:\n";
//    print_list(list);
    std::cout << '\n';
    char a_word[]{'h', 'e', 'c', '\0'};
    char word_after[]{'t', 'e', 'r', '\0'};
    add_after(list, a_word, word_after);
    print_list(list);
    std::cout << '\n';
    delete_after(list, word_after);
    print_list(list);
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
