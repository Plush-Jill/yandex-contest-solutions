#include <iostream>
#include <vector>
//#include <thread>


class QuerySolver {
private:
    static constexpr long long long_long_binary[] = {
            0b00000001'00000000'00000000'00000000'00000000'00000000'00000000'00000000LL,
            0b00000000'00000001'00000000'00000000'00000000'00000000'00000000'00000000LL,
            0b00000000'00000000'00000001'00000000'00000000'00000000'00000000'00000000LL,
            0b00000000'00000000'00000000'00000001'00000000'00000000'00000000'00000000LL,
            0b00000000'00000000'00000000'00000000'00000001'00000000'00000000'00000000LL,
            0b00000000'00000000'00000000'00000000'00000000'00000001'00000000'00000000LL,
            0b00000000'00000000'00000000'00000000'00000000'00000000'00000001'00000000LL,
            0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000001LL
    };

    struct LongLongFour {
        long long num1;
        long long num2;
        long long num3;
        long long num4;
    };

    union StringAsLongLongPair {
        struct LongLongFour ll_pair;
        char* string;
    };

    constexpr static long long m_SIZE {5000};

    int m_data_base_size;
    std::vector<StringAsLongLongPair> m_data_base;

    int m_query_count;



    int find_max_prefix_size(const StringAsLongLongPair& str1, const StringAsLongLongPair& str2) {
        StringAsLongLongPair tmp;
        tmp.ll_pair.num1 = str1.ll_pair.num1 ^ str2.ll_pair.num1;
        tmp.ll_pair.num2 = str1.ll_pair.num2 ^ str2.ll_pair.num2;
        tmp.ll_pair.num3 = str1.ll_pair.num3 ^ str2.ll_pair.num3;
        tmp.ll_pair.num4 = str1.ll_pair.num4 ^ str2.ll_pair.num4;

        for (int i {}; i < 8; ++i) {
            if (tmp.ll_pair.num1 >= long_long_binary[i]) {
                return i;
            }
        }

        for (int i {0}; i < 8; ++i) {
            if (tmp.ll_pair.num2 >= long_long_binary[i]) {
                return i + 8;
            }
        }

        for (int i {0}; i < 8; ++i) {
            if (tmp.ll_pair.num3 >= long_long_binary[i]) {
                return i + 16;
            }
        }

        for (int i {0}; i < 8; ++i) {
            if (tmp.ll_pair.num4 >= long_long_binary[i]) {
                return i + 24;
            }
        }

        return 8;

    }


public:

    QuerySolver() {
        StringAsLongLongPair tmp {};
        tmp.ll_pair.num1 = 0b01100001'01110011'01100100'01100001'01110011'01100100'00000000'00000000;
        for (int i {}; i < m_SIZE; ++i) {
            m_data_base.push_back(tmp);
        }
        m_query_count = m_SIZE;

//        m_queries[m_SIZE - 1] = "asdasd";
    }

    long long foo() {
        long long operations_sum {};

        for (int i {}; i < m_SIZE; ++i) {
            StringAsLongLongPair query {};

//            query.ll_pair.num1 = "asdasd";
            query.ll_pair.num1 = 0b01100001'01110011'01100100'01100001'01110011'01100100'00000000'00000000;
            for (int j {}; j < m_SIZE; ++j) {
                operations_sum += find_max_prefix_size(query, m_data_base[j]);
            }
        }

        return operations_sum;
    }

};


int main() {

    QuerySolver query_solver;
    std::cout << query_solver.foo();
//    query_solver.count_actions();
//    query_solver.print_actions_count();


    return 0;
}
