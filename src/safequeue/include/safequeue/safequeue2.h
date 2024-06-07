// https://stackoverflow.com/questions/15278343/c11-thread-safe-queue

#ifndef SAFE_QUEUE
#define SAFE_QUEUE

#include <queue>
#include <mutex>
#include <condition_variable>

// A threadsafe-queue.
template <class T>
class SafeQueue {
    public:
        SafeQueue(void): queue(), q_guard(), q_condition() {
        }

        ~SafeQueue(void) {
        }

        void enqueue(T value) {
            // Add an element to the queue.
            std::lock_guard<std::mutex> lock(q_guard);

            queue.push(value);
            q_condition.notify_one();
        }

        T dequeue(void) {
            // Get the "front"-element.
            // If the queue is empty, wait till a element is avaiable.
            std::unique_lock<std::mutex> lock(q_guard);

            while(queue.empty()) {
                // release lock as long as the wait and reaquire it afterwards.
                q_condition.wait(lock);
            }

            T value = queue.front();
            queue.pop();
            return value;
        }

    private:
        std::queue<T> queue;
        mutable std::mutex q_guard;
        std::condition_variable q_condition;
};

#endif