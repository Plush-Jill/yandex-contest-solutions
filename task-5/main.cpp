#include <iostream>
#include <vector>
//#include <thread>



class QuerySolver {
private:
    int m_data_base_size;
    std::vector<std::string> m_data_base;

    int m_query_count;
    int m_remain_query_count;
    std::vector<int> m_action_count;

//    std::vector<std::thread> m_thread_pool;
//    std::mutex m_query_read_mutex;
    std::vector<std::string> m_thread_current_query;

    int m_query_read_count {};
//    constexpr static int m_thread_count = 1;

    int find_max_prefix_size(const std::string& str1, const std::string& str2) {
        if (str1[0] != str2[0]) {
            return 0;
        }

        int size = str1.size() > str2.size() ? str1.size() : str2.size();
        for (int i {}; i < size; ++i) {
            if (str1[i] != str2[i]) {
                return i - 1;
            }
        }

        return size;
    }

public:
    QuerySolver() {
        std::cin >> m_data_base_size;
        m_data_base = std::vector<std::string> (m_data_base_size);
        for (int i {}; i < m_data_base_size; ++i) {
            std::cin >> m_data_base[i];
        }
    }

    void count_actions() {
        std::cin >> m_query_count;
        m_action_count = std::vector<int>(m_query_count);
        m_remain_query_count = m_query_count;
//        m_thread_current_query = std::vector<std::string>(m_thread_count);


        auto foo = [this]() {
            while (m_remain_query_count > 0) {
                std::string query;
                int query_index;
//                m_query_read_mutex.lock();
                std::cin >> query;
//                query_index = m_query_read_count;
                ++m_query_read_count;
//                m_query_read_mutex.unlock();

                int local_action_count {};
                for (int i {}; i < m_data_base_size; ++i) {
                    int max_prefix_size = find_max_prefix_size(query, m_data_base[i]);
                    local_action_count += max_prefix_size + 1;

                    if (query.size() == max_prefix_size) {
                        break;
                    }
                }

                m_action_count[query_index] = local_action_count;
//                m_query_read_mutex.lock();
                --m_remain_query_count;
//                m_query_read_mutex.unlock();

            }
        };

//        for (int i {}; i < m_thread_count; ++i) {
//            m_thread_pool.emplace_back(foo);
//        }
//
//        for (int i {}; i < m_thread_count; ++i) {
//            m_thread_pool[i].join();
//        }
        foo();
    }

    void print_actions_count() {
        for (int i {}; i < m_action_count.size(); ++i) {
            std::cout << m_action_count[i] << "\n";
        }
    }

};


int main() {


    QuerySolver query_solver;
    query_solver.count_actions();
    query_solver.print_actions_count();


    return 0;
}
