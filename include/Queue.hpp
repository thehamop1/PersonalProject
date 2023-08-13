#include <queue>
#include <mutex>

template<typename T>
class Queue{
    private:
        std::queue<T> m_queue;
        std::mutex    m_lock;

    public:  
    bool empty(){
        std::scoped_lock<std::mutex> localLock{m_lock};
        return m_queue.empty();
    };
    
    void push(const T& data){
        std::scoped_lock<std::mutex> localLock{m_lock};
        m_queue.emplace(data);
    };

    void push(T& data){
        std::scoped_lock<std::mutex> localLock{m_lock};
        m_queue.emplace(data);
    };

    void push(T&& data){
        std::scoped_lock<std::mutex> localLock{m_lock};
        m_queue.emplace(data);
    };

    bool pop(T& element){
        std::scoped_lock<std::mutex> localLock{m_lock};

        if(m_queue.empty()) return false;

        element = m_queue.front();
        m_queue.pop();
        return true;
    };
};