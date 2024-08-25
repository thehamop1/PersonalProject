//todo: remove this line
#include <iostream>

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
            std::vector<DataFrame<T, PoolSize>> m_InUse{};
            std::vector<DataFrame<T, PoolSize>> m_Available{};
            std::mutex m_PoolLock{};

            //Internal and only accessible from the pointers in the pool
            void Release(DataFrame<T, PoolSize> frame){
                std::cout << "Right before release" << std::endl;
                PrintDebugInfo();

                std::scoped_lock lock{m_PoolLock};
                for(auto it{m_Available.begin()}; it!=m_Available.end();++it){
                  if(frame==*it){
                    return;
                  }
                }
                
                for(auto it{m_InUse.begin()}; it!=m_InUse.end();++it){
                  if(frame==*it){
                    m_InUse.erase(it);
                    std::cout << "Erasing Frame" << std::endl;
                    break;
                  }
                }

                m_Available.emplace_back(frame);

                std::cout << "After release" << std::endl;
                PrintDebugInfo();
            }

        public:
            //we'll allocate total memory here
            MemoryPool() {
                std::scoped_lock lock{m_PoolLock};
                m_Available = {m_NumberOfElements, {T(), *this}};
                for(auto& resource: m_Available){
                    resource.m_DataFrameCopy = std::make_shared<T>();
                }

                PrintDebugInfo();
            };

            void PrintDebugInfo(){
              std::cout << std::endl;
              std::cout << "m_Available: " << m_Available.size() << std::endl;
              for(const auto& d: m_Available){
                d.PrintHash();
              }

              std::cout << "m_InUse: " << m_InUse.size() << std::endl;
              for(const auto& d: m_InUse){
                d.PrintHash();
              }
              std::cout << std::endl;
            }

            DataFrame<T, PoolSize> Alloc(){
                std::scoped_lock lock{m_PoolLock};
                if(m_Available.empty()){
                    throw std::runtime_error("Memory pool out of resources");
                }
                DataFrame<T, PoolSize> AvailableResource{m_Available.back()};
                m_Available.pop_back();
                m_InUse.push_back(AvailableResource);
                PrintDebugInfo();
                return AvailableResource;
            };
        };
    };

    //block acmess to std::shared_ptr functions
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

            void PrintHash() const {
              std::cout << std::hex << m_DataFrameCopy.get() << std::endl;
            }

            DataFrame& operator = (const T rhs){
                *m_DataFrameCopy = rhs;
                return *this;
            }

            DataFrame& operator = (const DataFrame& rhs){
                if(m_DataFrameCopy.use_count()<=2){
                  std::cout << "release mem" << std::endl;
                  m_PoolRef.get().Release(*this);
                }

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
                if(m_DataFrameCopy.use_count()==1){
                    std::cout << "Releasing memory" << std::endl;
                    m_PoolRef.get().Release(*this);
                }
            }

        private:

        friend class Internal::MemoryPool<T, PoolSize>;
        
        std::shared_ptr<T> m_DataFrameCopy{};
        std::reference_wrapper<Internal::MemoryPool<T, PoolSize>> m_PoolRef;
    };
};
