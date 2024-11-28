#include <iostream>
#include <string>
#include <vector>
#include <format>




class BraceTaskSolver {
private:
    int m_size;
    std::string m_sequence;
    std::vector<std::vector<int>> m_count_map;

    constexpr static int m_module = 1e+9 + 7;
public:
    BraceTaskSolver() {
        std::cin >> m_size;
        std::cin >> m_sequence;
    }


    int count_sequences() {
        m_count_map = std::vector<std::vector<int>> (m_size + 1, std::vector<int>(m_size + 1, 0));
        m_count_map[0][0] = 1;


        for (int i {1}; i <= m_sequence.size(); ++i) {
            for (int open {}; open <= i; ++open) {
                char current_symbol = m_sequence[i - 1];



                if (current_symbol == '(' || current_symbol == '[' || current_symbol == '{') {
                    // если открывающаяся и при этом правее, то добавляем то что слева сверху
                    if (open > 0) {
                        m_count_map[i][open] = (m_count_map[i][open] + m_count_map[i - 1][open - 1]) % m_module;
                    }

                } else if (current_symbol == ')' || current_symbol == ']' || current_symbol == '}') {
                    // в таком случае просто закрыть, сдвинув влево
                    if (open < m_sequence.size()) {
                        m_count_map[i][open] = (m_count_map[i][open] + m_count_map[i - 1][open + 1]) % m_module;
                    }

                } else if (current_symbol == '?') {
                    // тут собрать по диагонали сверху слева и справа.
                    if (open == 0) {
                        m_count_map[i][open] = (m_count_map[i][open] + m_count_map[i - 1][open + 1]) % m_module;
                    }
                    if (open == m_sequence.size()) {
                        m_count_map[i][open] = (m_count_map[i][open] + m_count_map[i - 1][open - 1]) % m_module;
                    }
                    if (open > 0 && open < m_sequence.size()) {
                        m_count_map[i][open] = (m_count_map[i][open] + m_count_map[i - 1][open - 1]) % m_module;
                        m_count_map[i][open] = (m_count_map[i][open] + m_count_map[i - 1][open + 1]) % m_module;
                    }
                }
            }
        }

        return m_count_map[m_size][0];
    }
};


int main() {

    BraceTaskSolver brace_task_solver;
    std::cout << brace_task_solver.count_sequences();

    return 0;
}
