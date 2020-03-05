#include <iostream>
#include <thread>
#include <future>
#include <string>

void print_string(std::future<std::string> f) {
    std::cout << "Text:     " <<  f.get() << "  thread:     "<< std::this_thread::get_id() << std::endl;
}

void fill_string(std::promise <std::string> p) {
    std::string text;
    std::cout << "thread:      " << std::this_thread::get_id()<< "      Insert string:    ";
    std::cin >> text;
    p.set_value(std::move(text));
    std::cout << std::endl;
}

std::string fill_string2() {
    std::string text;
    std::cout << "thread:      " << std::this_thread::get_id()<< "      Insert string:    ";
    std::cin >> text;
    std::cout << std::endl;
    return text;
}

int main() {
    std::promise <std::string> p;
    std::future <std::string> f = p.get_future();

    std::thread t1(fill_string, std::move(p));
    std::thread t2(print_string,std::move(f));
    t1.join();
    t2.join();

    std::packaged_task<std::string(void)> task(fill_string2);
    f = task.get_future();
    std::thread t3(std::move(task));
    t3.detach();
    std::cout << f.get() << std::endl;
    return 0;
}