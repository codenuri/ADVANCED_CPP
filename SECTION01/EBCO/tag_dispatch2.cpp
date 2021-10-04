#include <iostream>
#include <mutex>

struct adopt_lock_t
{
    explicit adopt_lock_t() = default;
};

constexpr adopt_lock_t adopt_lock;


template <class Mutex> class lock_guard 
{ 
public:
    using mutex_type = Mutex;

    explicit lock_guard(Mutex& mtx ) : mtx(mtx) { mtx.lock();}    
    explicit lock_guard(Mutex& mtx, adopt_lock_t ) : mtx(mtx) { }    

    ~lock_guard() noexcept { mtx.unlock(); }

    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;
private:
    Mutex& mtx;
};

std::mutex m1, m2;

int main()
{
    m2.lock();
    lock_guard g1(m1);   
    lock_guard g2(m2, adopt_lock); 
//    lock_guard g2(m2, {} );  // adopt_lock_t = {}
}


