#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <string>
#include <thread>
#include <queue>
#include <semaphore>

namespace safequeue {

	//https://stackoverflow.com/questions/15278343/c11-thread-safe-queue
	class queue {
		private:
			std::mutex guard {};
			std::queue<std::unique_ptr<std::string>> queue {};
			std::counting_semaphore<100> q_count {0};

		public:
			void push(const std::string &message) {
				push(std::make_unique<std::string>(message));
			}

			void push(std::unique_ptr<std::string> message) {
				std::lock_guard<std::mutex> lock(guard);
				queue.push(std::move(message));
				q_count.release();
			}

			bool empty() {
				std::lock_guard<std::mutex> lock(guard);
				return queue.empty();
			}

			std::unique_ptr<std::string> pop() {
				while (true) {
					q_count.acquire();

					std::lock_guard<std::mutex> lock(guard);
					if (!queue.empty()) {
						auto message = std::move(queue.front());
						queue.pop();
						return message;
					}
				}
			}
	};

}

#endif