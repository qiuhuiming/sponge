#include "byte_stream.hh"

#include <deque>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) {
    this->capacity = capacity;
    read_count = writen_count = 0;
    end = false;
}

size_t ByteStream::write(const string &data) {
    size_t accepted_count = 0;
    for (char c : data) {
        if (buffer.size() == capacity) {
            return accepted_count;
        }
        buffer.push_back(c);
        accepted_count++;
        writen_count++;
    }
    return accepted_count;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string result = "";
    deque<char> tmp = buffer;
    for (size_t i = 0; i < len; i++) {
        result = result + tmp.front();
        tmp.pop_front();
    }

    return result;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    for (size_t i = 0; i < len; i++) {
        buffer.pop_front();
        read_count++;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string result = peek_output(len);
    pop_output(len);
    return result;
}

void ByteStream::end_input() { end = true;}

bool ByteStream::input_ended() const { return end;}

size_t ByteStream::buffer_size() const {
    return buffer.size();
}

bool ByteStream::buffer_empty() const {
    return buffer.empty();
}

bool ByteStream::eof() const {
    return end && buffer_empty();
}

size_t ByteStream::bytes_written() const { return writen_count; }

size_t ByteStream::bytes_read() const { return read_count; }

size_t ByteStream::remaining_capacity() const { return capacity - buffer_size(); }
