#include <deque>
#include <iostream>
#include <memory>

template <typename T>
struct counting_allocator {
    using value_type = T;

    static std::size_t allocated_bytes;   // 累计字节数

    counting_allocator() noexcept = default;
    template <typename U>
    counting_allocator(const counting_allocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        std::size_t bytes = n * sizeof(T);
        allocated_bytes += bytes;
        return static_cast<T*>(::operator new(bytes));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::size_t bytes = n * sizeof(T);
        allocated_bytes -= bytes;
        ::operator delete(p);
    }

    // 为了让不同实例被视为同一类型
    template <typename U>
    friend bool operator==(const counting_allocator&, const counting_allocator<U>&) {
        return true;
    }
    template <typename U>
    friend bool operator!=(const counting_allocator&, const counting_allocator<U>&) {
        return false;
    }
};

// 静态成员定义
template <typename T>
std::size_t counting_allocator<T>::allocated_bytes = 0;

int main() {
    using Alloc = counting_allocator<int>;
    using Deque = std::deque<int, Alloc>;
    using Vector = std::vector<int, Alloc>;

    std::cout << "初始已分配: " << Alloc::allocated_bytes << " 字节\n";

    Alloc alloc;             // 实例化一个分配器
    Deque dq(alloc);         // 把分配器传进去

    std::cout << "初始已分配: " << Alloc::allocated_bytes << " 字节\n";

    // 按阶段插入元素，观察内存变化
    for (int i = 0; i < 1000; ++i) {
        dq.push_back(i);
    }
    std::cout << "插入1000个int后已分配: " << Alloc::allocated_bytes << " 字节\n";

    dq.shrink_to_fit();
    std::cout << "shrink_to_fit() 后已分配: " << Alloc::allocated_bytes << " 字节\n";

    // 清理
    dq.clear();
    dq.shrink_to_fit();
    std::cout << "clear + shrink_to_fit 后已分配: " << Alloc::allocated_bytes << " 字节\n";

    return 0;
}