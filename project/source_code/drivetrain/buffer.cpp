//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include "user_input.hpp"

class CanBuffer
{
    public:
        static CanBuffer& getInstance()
        {
            static CanBuffer    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
        void add(user_input input) {
            received_can_data = input;
        }
        user_input pull () {
            return received_can_data;
        }
    private:
        CanBuffer() {}                    // Constructor? (the {} brackets) are needed here.

        // C++ 03
        // ========
        // Don't forget to declare these two. You want to make sure they
        // are inaccessible(especially from outside), otherwise, you may accidentally get copies of
        // your singleton appearing.
        CanBuffer(CanBuffer const&);              // Don't Implement
        void operator=(CanBuffer const&); // Don't implement

        user_input received_can_data; //this will be replaced by ringbuffer

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
    public:
        CanBuffer(CanBuffer const&)               = delete;
        void operator=(CanBuffer const&)  = delete;
        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
};