#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;


void Write_Matrix(string str, size_t rows, size_t cols)
{
    vector<vector<int>> m(rows);
    for(auto& i : m)
        i.resize(cols);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            m[i][j] = rand() % 1000;
        }
    }

    ofstream data(str);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            data << setw(5) << m[i][j];
        }
        data << endl;
    }

    data.close();
}


void Read_Matrix(vector<vector<int>>& m, int rows, int cols, string str)
{
    m.resize(rows);
    for(auto& i : m)
        i.resize(cols);

    ifstream data;
    data.open(str);

    if(data.is_open()) {
        for(int i = 0; i < m.size(); i++) {
            for(int j = 0; j < m[i].size(); j++) {
                data >> m[i][j];
            }
        }
    }

    data.close();
}


void Multiplication(const vector<vector<int>>& m_1, const vector<vector<int>>& m_2, vector<vector<int>>& m_3)
{
    size_t rows = m_1.size();
    size_t cols = m_2[0].size();
    m_3.resize(rows);
    for(auto& i : m_3)
        i.resize(cols);

    for(int i = 0; i < m_3.size(); i++) {
        for(int j = 0; j < m_3[i].size(); j++) {
            for(int k = 0; k < m_2.size(); k++) {
                m_3[i][j] += m_1[i][k] * m_2[k][j];
            }
        }
    }
}


void Write_Res(string str, vector<vector<int>>& res)
{
    ofstream data(str);

    for(int i = 0; i < res.size(); i++) {
        for(int j = 0; j < res[i].size(); j++) {
            data << setw(10) << res[i][j];
        }
        data << endl;
    }

    data.close();
}


int main()
{
    srand(time(NULL));
    size_t row = 500, col = 500;
    vector<vector<int>> v1, v2, v3;

    Write_Matrix("Mat_1.txt", row, col);
    Write_Matrix("Mat_2.txt", row, col);

    Read_Matrix(v1, row, col, "Mat_1.txt");
    Read_Matrix(v2, row, col, "Mat_2.txt");

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Multiplication(v1, v2, v3);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    Write_Res("Multiplication.txt", v3);
    cout << "Diff(ms) = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;

    return 0;
}
