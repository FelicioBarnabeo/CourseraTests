#include "test_runner.h"

using namespace std;

template<typename T>
class Table
{
public:
    Table(size_t rows, size_t columns) : m_rows(rows), m_columns(columns)
    {
        Resize(rows,columns);
    }
    pair<size_t, size_t> Size() const { return {m_rows, m_columns};}
    void Resize(size_t newRows, size_t newColumns)
    {
        m_rows = newRows;
        m_columns = newColumns;
        m_data.resize(m_rows);
        for(auto &v : m_data)
        {
            v.resize(m_columns);
        }
    }
    vector<T>& operator [](size_t idx) {return m_data[idx];}
    const vector<T>& operator [](size_t idx) const {return m_data[idx];}
private:
    size_t m_rows;
    size_t m_columns;
    vector<vector<T>> m_data;
};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    cout<<t.Size().first<<" "<<t.Size().second<<endl;
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestTable);
//  return 0;
//}
