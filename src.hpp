// CrossArray implementation header for OJ harness (no STL)
#pragma once
namespace sjtu {
class CrossArray{
private:
    int max_lines;
    int **data;
    int *lens;
    int inserted;
public:
    explicit CrossArray(int lines) : max_lines(lines), data(nullptr), lens(nullptr), inserted(0) {
        if (max_lines < 0) max_lines = 0;
        data = new int*[max_lines];
        lens = new int[max_lines];
        for (int i = 0; i < max_lines; ++i) { data[i] = nullptr; lens[i] = 0; }
    }

    CrossArray(const CrossArray & o) : max_lines(o.max_lines), data(nullptr), lens(nullptr), inserted(o.inserted) {
        data = new int*[max_lines];
        lens = new int[max_lines];
        for (int i = 0; i < max_lines; ++i) {
            lens[i] = o.lens[i];
            if (o.data[i] == nullptr) {
                data[i] = nullptr;
            } else {
                data[i] = new int[lens[i]];
                for (int j = 0; j < lens[i]; ++j) data[i][j] = o.data[i][j];
            }
        }
    }

    CrossArray & WhichGreater(CrossArray & o) {
        long long cnt_this = 0, cnt_o = 0;
        for (int i = 0; i < max_lines; ++i) cnt_this += lens[i];
        for (int i = 0; i < o.max_lines; ++i) cnt_o += o.lens[i];
        if (cnt_o > cnt_this) return o;
        return *this;
    }

    bool IsSame(const CrossArray & o) {
        return this->data == o.data;
    }

    bool InsertArrays(const int * Input, int size) {
        if (inserted >= max_lines) return false;
        if (size < 0) size = 0;
        int idx = inserted;
        if (size == 0) {
            data[idx] = nullptr;
            lens[idx] = 0;
        } else {
            int *arr = new int[size];
            for (int i = 0; i < size; ++i) arr[i] = Input[i];
            data[idx] = arr;
            lens[idx] = size;
        }
        inserted++;
        return true;
    }

    void AppendArrays(const int * Input,int Line,int size) {
        if (size <= 0) return;
        int old_len = lens[Line];
        int new_len = old_len + size;
        int *new_arr = new int[new_len];
        if (data[Line] != nullptr) {
            for (int i = 0; i < old_len; ++i) new_arr[i] = data[Line][i];
        }
        for (int i = 0; i < size; ++i) new_arr[old_len + i] = Input[i];
        if (data[Line] != nullptr) delete [] data[Line];
        data[Line] = new_arr;
        lens[Line] = new_len;
    }

    void DoubleCrossLength() {
        int new_max = max_lines * 2;
        int **new_data = new int*[new_max];
        int *new_lens = new int[new_max];
        for (int i = 0; i < new_max; ++i) { new_data[i] = nullptr; new_lens[i] = 0; }
        for (int i = 0; i < max_lines; ++i) { new_data[i] = data[i]; new_lens[i] = lens[i]; }
        delete [] data;
        delete [] lens;
        data = new_data;
        lens = new_lens;
        max_lines = new_max;
    }

    const int * AtArray(int i) { return data[i]; }

    int & At(int i , int j) { return data[i][j]; }

    ~CrossArray() {
        if (data) {
            for (int i = 0; i < max_lines; ++i) {
                if (data[i] != nullptr) delete [] data[i];
            }
            delete [] data;
        }
        if (lens) delete [] lens;
        data = nullptr; lens = nullptr; max_lines = 0; inserted = 0;
    }
};
}

