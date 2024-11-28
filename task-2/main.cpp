#include <iostream>
#include <vector>
#include <unordered_map>
#include <format>



bool is_debug_enabled = false;


class Segment {
private:
    std::vector<int> m_numbers;
    int m_target_median;
    int m_median_pos;

public:
    Segment(int size, int target_median) {
        m_numbers = std::vector<int>(size);
        m_target_median = target_median;

        for (int i {}; i < size; ++i) {
            std::cin >> m_numbers[i];

            if (m_numbers[i] == m_target_median) {
                m_median_pos = i;
            }
        }
    }
    [[nodiscard]] int get_median_pos() const {
        return m_median_pos;
    }
    [[nodiscard]] int get_median() const {
        return m_target_median;
    }

    int count_median_sub_arrays() {
        std::unordered_map<int, int> map;
        int result {0};

        map[0] = 1;


        int left_sum {};
        for (int i {m_median_pos - 1}; i >= 0; --i) {
            left_sum += (m_numbers[i] < m_target_median ? -1 : 1);
            if (is_debug_enabled) std::cout << std::format("array[{}] = {}, balance = {}\n", i, m_numbers[i], left_sum);


            ++map[left_sum];

            if (left_sum == 0) {
                ++result;
            }
        }


        int right_sum {};
        for (int i {m_median_pos}; i < m_numbers.size(); ++i) {
            if (m_numbers[i] == m_target_median) {
                ++result;
                continue;
            }
            right_sum += (m_numbers[i] < m_target_median ? -1 : 1);

            result += map[-right_sum];

            if (is_debug_enabled) std::cout << std::format("array[{}] = {}, balance = {}, result = {}\n", i, m_numbers[i], right_sum, result);
        }



        return result;
    }

};


int main() {
    int size;
    int median;
//    is_debug_enabled = true;


    std::cin >> size >> median;

    Segment segment {size, median};
    if (is_debug_enabled) std::cout << std::format("median: array[{}] = {}",segment.get_median_pos(), segment.get_median()) << std::endl << std::endl;
    std::cout << segment.count_median_sub_arrays() << std::endl;

    return 0;
}
