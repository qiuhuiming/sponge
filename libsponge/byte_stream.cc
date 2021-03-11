#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) {
    buffer = string(capacity, '\0');
    this->capacity = capacity;
    real_size = writen_count = read_count = 0;
    end = false;
}

size_t ByteStream::write(const string &data) {
    if (data.size() + real_size > capacity) {
        size_t accept_num = capacity - real_size;
        string _data = data.substr(0, accept_num);
        return write(_data);
    } else {
        buffer.replace(real_size, data.size(), data);
        real_size += data.size();
        writen_count += data.size();
        return data.size();
    }
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return buffer.substr(0, len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    string newBuffer = buffer.substr(len, real_size - len);
    buffer.replace(0, real_size - len, newBuffer);
    read_count += len;
    real_size -= len;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string result = peek_output(len);
    pop_output(len);
    return result;
}

void ByteStream::end_input() {
    end = true;
}

bool ByteStream::input_ended() const {
    return end;
}

size_t ByteStream::buffer_size() const {
    return real_size;
}

bool ByteStream::buffer_empty() const {
    return real_size == 0;
}

bool ByteStream::eof() const {
    return end && buffer_size() == 0;
}

size_t ByteStream::bytes_written() const {
    return writen_count;
}

size_t ByteStream::bytes_read() const {
    return read_count;
}

size_t ByteStream::remaining_capacity() const {
    return capacity - real_size;
}
