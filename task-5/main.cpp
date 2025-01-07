#include <iostream>
#include <vector>
//#include <thread>


class QuerySolver {
private:

    constexpr static long long m_SIZE {5000};

    int m_data_base_size;
    std::vector<std::string> m_data_base;

    int m_query_count;
    std::vector<std::string> m_queries;

    std::vector<int> m_action_count;
    std::vector<std::string> m_thread_current_query;

    int m_query_read_count {};

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
//    QuerySolver() {
//        std::cin >> m_data_base_size;
//        m_data_base = std::vector<std::string> (m_data_base_size);
//        for (int i {}; i < m_data_base_size; ++i) {
//            std::cin >> m_data_base[i];
//        }
//    }

    QuerySolver() {
        m_data_base = std::vector<std::string> (m_SIZE, "asdasd");
        m_query_count = m_SIZE;
        m_queries = std::vector<std::string> (m_SIZE, "asdb");

        m_queries[m_SIZE - 1] = "asdasd";
    }

    int foo2() {
        long long operations_sum {};
        for (int i {}; i < m_SIZE; ++i) {
            std::string query = m_queries[i];

            for (int j {}; j < m_SIZE; ++j) {
                operations_sum += find_max_prefix_size(query, m_data_base[j]);
            }
        }

        return operations_sum;
    }

    void count_actions() {
        std::cin >> m_query_count;
        m_action_count = std::vector<int>(m_query_count);


        auto foo = [this]() {
            for (int query_index {}; query_index < m_query_count; ++query_index) {
                std::string query;
                std::cin >> query;

                int local_action_count {};
                for (int i {}; i < m_data_base_size; ++i) {
                    int max_prefix_size = find_max_prefix_size(query, m_data_base[i]);
                    local_action_count += max_prefix_size + 1;

                    if (query.size() == max_prefix_size) {
                        break;
                    }
                }

                m_action_count[query_index] = local_action_count;
            }
        };

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
    std::cout << query_solver.foo2();
//    query_solver.count_actions();
//    query_solver.print_actions_count();


    return 0;
}
