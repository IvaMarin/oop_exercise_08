#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#include <fstream>

template <class MESSAGE_T>
class server {
public:
    using subscriber_t = std::function<void(const MESSAGE_T&)>;

    // Singleton
    static server& Get() {
        static server instance; // Guaranteed to be destroyed
                                // Instantiated on first use
        return instance;
    }

    // Subscriber - function to handle buffer
    void RegisterSubscriber(const subscriber_t& sub) {
        subscribers.push_back(sub);
    }

    // Publisher - element of a buffer (figure)
    void Publish(const MESSAGE_T& msg) {
        std::lock_guard<std::mutex> lck(mtx);
        message_queue.push(msg);
    }

    // Starting handler
    void Run(size_t max_size) {
        while (active) {
            if (message_queue.size() == max_size) {
                // handling
                std::string file_name = GenerateFileName();
                fd.open(file_name);
                while (!message_queue.empty()) {
                    std::lock_guard<std::mutex> lck(mtx);
                    MESSAGE_T val = message_queue.front();
                    message_queue.pop();
                    for (auto sub : subscribers) {
                        sub(val);
                    }
                }
                fd.flush();
                fd.close();
            }
            else {
                // Provides a hint to the implementation to reschedule  
                // the execution of threads, allowing other threads to run
                std::this_thread::yield; 
            }
        }
    }

    void Stop() {
        active = false;
    }

    // Gets file descriptor
    std::ofstream& GetFD() {
        return fd;
    }

private:
    std::vector<subscriber_t> subscribers;
    std::queue<MESSAGE_T> message_queue;
    std::mutex mtx;
    std::string file_name;
    std::ofstream fd;
    server() {};
    bool active = true;

    std::string GenerateFileName() {
        std::string file_name = "file_";
        srand(time(NULL));
        for (int i = 0; i < 3; ++i) {
            file_name.push_back(rand() % 10 + '0');
        }
        return file_name;
    }
};

#endif //SERVER_HPP