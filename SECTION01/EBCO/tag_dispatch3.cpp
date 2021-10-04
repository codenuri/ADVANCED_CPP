#include <mutex>
#include <new>

std::mutex m;

int main()
{
    std::unique_lock u1(m, std::adopt_lock);
    std::unique_lock u2(m, std::defer_lock);
    std::unique_lock u3(m, std::try_to_lock);

    // C++98
    int* p1 = new int[10];  // 실패시 std::bad_alloc 예외 발생
    delete[] p1;

    int* p2 = new(std::nothrow) int[10]; // 실패시 0 반환
    delete[] p2;
}
