// List.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>

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

void AddAfter(Node* list, std::string word, std::string wordAfter)
{
 

    // пока не закончился список или 
    //пока не нашли элемент после которого нужно добавить элемент
    while (list && list->data != word)
    {
        // идем по списку сворачивая его
        list = list->ptr;
    }
    // если элемент найден
    if (list)
    {
        // запоминаем значение следуещего элемента
        Node* buf = list->ptr;
        // вставляем пустой элемент
        list->ptr = new Node;
        // заполняем его
        list->ptr->data = wordAfter;
        // делаем связь с последующим элементом
        list->ptr->ptr = buf;
    }

}


void DeleteAfter(Node*& a_list, std::string word)
{
    Node* list = a_list;
    if (list)
    {
        if (list->data == word)
        {
            a_list = list->ptr;
            delete list;
            list = nullptr;
        }
        else
        {
            while (list->ptr && list->ptr->data != word)
            {
                list = list->ptr;
            }
            if (list->ptr)
            {

                Node* del = list->ptr;
                list->ptr = list->ptr->ptr;
                delete del;
                del = nullptr;
            }
        }
        
    }
        
}

// функция не безопасно можно использоввать только, если известно, что указатель не NULL
void MinBegin(Node* list)
{
        Node* a_list = list;
        std::string min = list->data;
        Node* minIndex = list;
            while (a_list)
            {
                if (a_list->data < min)
                {
                    min = a_list->data;
                    minIndex = a_list;
                }
                a_list = a_list->ptr;
            }
            minIndex->data = list->data;
            list->data = min;
}

void Sort(Node* list)
{
    while (list)
    {
        MinBegin(list);
        list = list->ptr;
    }
}


void Swap(Node* a, Node* b)
{
    Node* f = new Node;
    f->data = a->data;
    a->data = b->data;
    b->data = f->data;
    delete f;
    f = nullptr;
}


void PrintList(Node* list) 
{
    std::cout << "\nТЕКУЩЕЕ СОДЕРЖИМОЕ СПИСКА:\n";
    while (list) 
    {
        std::cout << list->data << " ";
        list = list->ptr;
    }
    std::cout << '\n';
}

void PrintListForwards(Node* list)
{
    if (list)
    {
        std::cout << list->data << ' ';
        PrintListForwards(list->ptr);
    }
    else
    {
        std::cout << '\n';
    }
}


void PrintListBackwards(Node* list)
{
    if (list)
    {
        PrintListBackwards(list->ptr);
        std::cout << list->data << ' ';
    }
}


void PrintListBackwardsIteration(Node* list)
{

    std::vector<std::string> temporaryData;
    while (list)
    {
        temporaryData.push_back(list->data);
        list = list->ptr;
    }
    for (int i = temporaryData.size() - 1; i >= 0; i--)
    {
        std::cout << temporaryData[i] << ' ';
    }
}

void DeleteList(Node*& a_list)
{
    
    while (a_list)
    {
        Node* list = a_list;
        a_list = a_list->ptr;
        delete list;
        list = nullptr;
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    
    Node* list = nullptr;
    std::string word;
    std::string wordAfter;
    std::string deleteWord;
    AssignList(list);
    
    PrintList(list);
    
    /*
    std::cout << "ПОСЛЕ КАКОГО СЛОВА ВЫ ХОТИТЕ ВСТАВИТЬ НОВОЕ СЛОВО ? ";
    std::cin >> word;
    std::cout << "КАКОЕ СЛОВО ВЫ ХОТИТЕ ВСТАВИТЬ? ";
    std::cin >> wordAfter;
    AddAfter(list, word, wordAfter);
    PrintList(list);
    std::cout << "КАКОЕ СЛОВО ВЫ ХОТИТЕ УДАЛИТЬ ?";
    std::cin >> deleteWord;
    DeleteAfter(list, deleteWord);
    PrintList(list);
    Sort(list);
    std::cout << "СОДЕРЖИМОЕ СПИСКА ПОСЛЕ СОРТИРОВКИ : \n";
    PrintList(list);
    */

    
    std::cout << "Вывод прямой порядок рекурсия\n";
    PrintListForwards(list);
    std::cout << "Вывод обратный порядок рекурсия\n";
    PrintListBackwards(list);
    std::cout << '\n';
    std::cout << "Вывод обратный порядок цикл\n";
    PrintListBackwardsIteration(list);
    DeleteList(list);
    PrintList(list);
    


    /*
    Node* a;
    Node* b;
    AssignList(a);
    AssignList(b);
    Swap(a, b);
    DeleteList(a);
    DeleteList(b);
    */
    return 0;
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
