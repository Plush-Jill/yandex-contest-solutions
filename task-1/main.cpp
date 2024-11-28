#include <iostream>
#include <vector>
#include <format>
#include <thread>


class Crossword {
private:
    int m_row_count;
    int m_column_count;
    std::vector<std::vector<char>> m_grid;
    std::string m_min_word {"zzzzzzzzz"};
    enum class SearchDirection {
        Right,
        Down
    };

    bool can_start_search_from_this_point(int row, int column, SearchDirection direction) {
        bool is_zero_row = row == 0;
        bool is_zero_column = column == 0;
        bool is_white_cell = m_grid[row][column] != '#';

        if (is_zero_row && is_zero_column && is_white_cell) {
            return true;
        }
        if (is_zero_row && direction == SearchDirection::Down && is_white_cell) {
            return true;
        }
        if (is_zero_column && direction == SearchDirection::Right && is_white_cell) {
            return true;
        }
        if (!is_zero_row && direction == SearchDirection::Down) {
            if (m_grid[row - 1][column] == '#') {
                return true;
            }
        }
        if (!is_zero_column && direction == SearchDirection::Right) {
            if (m_grid[row][column - 1] == '#') {
                return true;
            }
        }

        return false;
    }

    void dfs(int row, int column, SearchDirection direction, std::string accumulated_word, bool is_first) {
        if (row >= m_row_count || column >= m_column_count) {
            return;
        }

        char current_symbol = m_grid[row][column];

        if (current_symbol == '#') {
            if (accumulated_word < m_min_word && accumulated_word.size() >= 2) {
                m_min_word = accumulated_word;
                return;
            }
        } else if (row == m_row_count - 1 && direction == SearchDirection::Down) {
            accumulated_word += current_symbol;
            if (accumulated_word < m_min_word && accumulated_word.size() >= 2) {
                m_min_word = accumulated_word;
                return;
            }
        } else if (column == m_column_count - 1 && direction == SearchDirection::Right) {
            accumulated_word += current_symbol;
            if (accumulated_word < m_min_word && accumulated_word.size() >= 2) {
                m_min_word = accumulated_word;
                return;
            }
        } else {
            accumulated_word += current_symbol;

            if (direction == SearchDirection::Right) {
                dfs(row, column + 1, direction, accumulated_word, false);
            } else if (direction == SearchDirection::Down){
                dfs(row + 1, column, direction, accumulated_word, false);
            }
        }


    }

public:

    void print_crossword() {
        for (int i{}; i < m_row_count; ++i) {
            for (int j{}; j < m_column_count; ++j) {
                char c = m_grid[i][j];
                std::cout << c;
            }
            std::cout << "\n";
        }
    }

    Crossword(int row_count, int column_count){
        m_row_count = row_count;
        m_column_count = column_count;
        m_grid = std::vector<std::vector<char>>(m_row_count, std::vector<char>(m_column_count));



        for (int i {}; i < m_row_count; ++i) {
            for (int j {}; j < m_column_count; ++j) {
                std::cin >> m_grid[i][j];
            }
        }
    }

    std::string find_min_word() {
        for (int i {}; i < m_row_count; ++i) {
            for (int j{}; j < m_column_count; ++j) {

                if (can_start_search_from_this_point(i, j, SearchDirection::Right)) {
                    dfs(i, j, SearchDirection::Right, "", true);
                }
                if (can_start_search_from_this_point(i, j, SearchDirection::Down)) {
                    dfs(i, j, SearchDirection::Down, "", true);
                }

            }
        }

        return m_min_word;
    }
};

int main() {
    int row_count;
    int column_count;
    std::cin >> row_count >> column_count;

    Crossword crossword {row_count, column_count};
    std::cout << crossword.find_min_word();
    return 0;
}
