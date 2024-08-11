#include "Singleton.hpp"

#include <mutex>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

namespace Core{
    template<typename T, size_t PoolSize>
    class DataFrame;

    namespace Internal{
        //create a class to manage memory for heavy processing
        template<typename T, size_t PoolSize>
        class MemoryPool
        {
        private:
            friend class DataFrame<T, PoolSize>;

            const size_t m_NumberOfElements{PoolSize};
            std::vector<DataFrame<T, PoolSize>> m_ProcessMemory{};
            std::vector<DataFrame<T, PoolSize>> m_InUse{};
            std::vector<DataFrame<T, PoolSize>> m_Available{};
            std::mutex m_PoolLock{};
            //Internal and only accessible from the pointers in the pool
            void Release(DataFrame<T, PoolSize>& frame){
                std::scoped_lock lock{m_PoolLock};
                //std::erase_if(m_InUse, [&](const DataFrame<T, PoolSize>& f){return f==frame;});
                std::remove_if(m_InUse.begin(), m_InUse.end(), [&](const DataFrame<T, PoolSize>& f){return f==frame;});
                //m_Available.emplace_back(frame);
            }
        public:
            //we'll allocate total memory here
            MemoryPool() {
                m_ProcessMemory = {m_NumberOfElements, {T(), *this}};
            };

            DataFrame<T, PoolSize> Alloc(){
                std::scoped_lock lock{m_PoolLock};
                if(m_Available.empty()){
                    throw std::runtime_error("Memory pool out of resources");
                }
                DataFrame<T, PoolSize> AvailableResource{m_Available.back()};
                m_Available.pop_back();
                return AvailableResource;
            };

        };
    };

    //block access to std::shared_ptr functions
    template<typename T, size_t PoolSize>
    class DataFrame{
        public:
            DataFrame(std::shared_ptr<T> dataFrame, Internal::MemoryPool<T, PoolSize>& poolRef): 
            m_DataFrameCopy{dataFrame}, 
            m_PoolRef{poolRef}{
            }
            DataFrame(const DataFrame& frame): 
            m_DataFrameCopy{frame.m_DataFrameCopy}, 
            m_PoolRef{frame.m_PoolRef.get()}{
            }

            DataFrame& operator = (const DataFrame& rhs){
                m_DataFrameCopy = rhs.m_DataFrameCopy;
                m_PoolRef = rhs.m_PoolRef.get();
                return *this;
            }

            bool operator == (const DataFrame& rhs) const {
                return (m_DataFrameCopy == rhs.m_DataFrameCopy);
            }

            T& operator *(){
                return *m_DataFrameCopy;
            }

            T& operator ->(){
                return *m_DataFrameCopy;
            }

            ~DataFrame(){
                m_PoolRef.get().Release(*this);
            }

        private:
        friend class Internal::MemoryPool<T, PoolSize>;
        
        std::shared_ptr<T> m_DataFrameCopy{};
        std::reference_wrapper<Internal::MemoryPool<T, PoolSize>> m_PoolRef;
    };

//    we're going to be creating project specific pools 
//    template<typename T>
//    using MemoryPool = Core::Singleton<Internal::MemoryPool<T>>;
};