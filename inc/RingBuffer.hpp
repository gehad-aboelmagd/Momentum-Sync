#ifndef RING_BUFFER_HPP_
#define RING_BUFFER_HPP_

#include <vector>
#include <optional>

template <typename T>
class RingBuffer 
{
private:
    std::vector<std::optional<T>> buffer;
    int capacity; // overall
    int counter; // current
public:
    RingBuffer(int size): capacity(size), counter{0}
    {
        buffer.resize(size);
    }

    RingBuffer(RingBuffer &other) = delete;
        
    RingBuffer(RingBuffer && other)
    : buffer{std::move(other.buffer)}, capacity{other.capacity}, counter{other.counter}
    {
        other.capacity = other.counter = 0;
    }
    
    RingBuffer & operator=(RingBuffer &other) = delete;

    RingBuffer & operator=(RingBuffer &&other)
    {
        buffer = std::move(other.buffer);
        capacity = other.capacity;
        counter = other.counter;

        other.capacity = other.counter = 0;

        return *this;
    }

    std::optional<T> & operator[](int index)
    {
        return buffer[index];
    }

    int getSize()
    {
        return capacity;
    }
    
    void tryPush(T value)
    {
        buffer[counter] = std::move(value);
        counter = (counter + 1) % capacity;
    }

    std::optional<T> tryPop()
    {
        counter = (counter-1+capacity) % capacity;
        return buffer[counter];
    }
};

#endif // RING_BUFFER_HPP_