#include "Singleton.hpp"

#include <mutex>
#include <memory>
#include <vector>
#include <algorithm>

namespace Core{
    template<typename T>
    class DataFrame;

    namespace Internal{
        //create a class to manage memory for heavy processing
        template<typename T>
        class MemoryPool
        {
        private:
            size_t m_NumberOfElements{};
            std::vector<DataFrame<T>> m_ProcessMemory{};
            std::vector<DataFrame<T>> m_InUse{};
            std::vector<DataFrame<T>> m_Available{};
            std::mutex m_PoolLock{};
            //Internal and only accessible from the pointers in the pool
            void Release(DataFrame<T> frame){
                std::scoped_lock lock{m_PoolLock};
                auto PointerIt{std::find(m_InUse.begin(), m_InUse.end(), frame)};
                std::remove(m_InUse.begin(), m_InUse.end(), PointerIt);
                m_Available.emplace_back(frame);
            }
        public:
            //we'll allocate total memory here
            MemoryPool(const size_t& NumDataFrames) {
                m_NumberOfElements = NumDataFrames;
                m_ProcessMemory = {NumDataFrames, {DataFrame<T>(), *this}};
            };

            DataFrame<T> Alloc(){
                std::scoped_lock lock{m_PoolLock};
                if(m_Available.empty()){
                    throw std::runtime_error("Memory pool out of resources");
                }
                DataFrame<T> AvailableResource{m_Available.back()};
                m_Available.pop_back();
                return AvailableResource;
            };

        };
    };

    //block access to std::shared_ptr functions
    template<typename T>
    class DataFrame{
        private:
        std::shared_ptr<T> m_DataFrameCopy{};
        Internal::MemoryPool<T>& m_PoolRef{};

        public:
            DataFrame(std::shared_ptr<T> dataFrame, Internal::MemoryPool<T>& poolRef): m_DataFrameCopy{dataFrame}, m_PoolRef{poolRef}{}
            T& operator *(){
                return *m_DataFrameCopy;
            }

            T& operator ->(){
                return *m_DataFrameCopy;
            }

            ~DataFrame(){
                m_PoolRef.Release(*this);
            }
    };

    template<typename T>
    using MemoryPool = Core::Singleton<Internal::MemoryPool<T>>;
};