#pragma once

namespace Core{
    template<typename T>
    class Singleton
    {
    public:
        static T& Instance(){
            static T Instance;
            return Instance;
        };
    };
}