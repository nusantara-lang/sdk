/*
 * ----------------------------------------------------------------------------
 * Project: Nusa
 * Author: Fern Aerell
 * License: BSD 3-Clause License
 * Copyright (c) 2025, The Nusa Project Authors
 * ----------------------------------------------------------------------------
 */

#include "nusa/support/char_stream.h"
#include "nusa/support/memory_mapped_file.h"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace nusa {

CharStream::CharStream() = default;

CharStream CharStream::cStr(const char* cstr)
{
    CharStream cs;
    cs.setCStr(cstr);
    return cs;
}

CharStream CharStream::file(const char* path)
{
    CharStream cs;
    cs.setFile(path);
    return cs;
}

void CharStream::setCStr(const char* input)
{
    this->_set(input, false);
}

void CharStream::setFile(const char* path)
{
    this->_set(path, true);
}

const size_t& CharStream::size()
{
    return this->_size;
}

const size_t& CharStream::index()
{
    return this->_index;
}

const size_t& CharStream::line()
{
    return this->_line;
}

const size_t& CharStream::column()
{
    return this->_column;
}

void CharStream::index(const size_t& index)
{
    this->_indexValidation(index);
    this->_index = index;
}

bool CharStream::end()
{
    return this->_index >= this->_size;
}

void CharStream::next()
{
    if (this->end())
        throw std::out_of_range("Cannot move to next character: index " + std::to_string(this->_index) + " is out of bounds (max: " + std::to_string(std::max((size_t)0, this->_size) - 1) + ").");

    if (!this->_statesCache.contains(this->_line))
        this->_statesCache[this->_line] = {};

    if (!this->_statesCache[this->_line].contains(this->_index))
        this->_statesCache[this->_line][this->_index] = this->_column;

    if (this->cchar() == '\n')
    {
        this->_line++;
        this->_column = 0;
    }
    else
        this->_column++;

    this->_index++;
}

void CharStream::next(const size_t& count)
{
    for (size_t i{0}; i < count; i++)
        this->next();
}

const char& CharStream::charAt(const size_t& index)
{
    this->_indexValidation(index);

    return this->_chars[index];
}

const char& CharStream::cchar()
{
    return this->charAt(this->_index);
}

bool CharStream::match(const size_t& index, const char* chars)
{
    this->_indexValidation(index);

    size_t size = std::strlen(chars);

    if (size == 0)
        return false;

    size_t futureIndex = index + size - 1;
    if (futureIndex >= this->_size)
        return false;

    for (size_t i = 0; i < size; i++)
        if (this->_chars[index + i] != chars[i])
            return false;

    return true;
}

bool CharStream::cmatch(const char* chars)
{
    return this->match(this->_index, chars);
}

void CharStream::reset()
{
    this->_index = 0;
    this->_line = 0;
    this->_column = 0;
}

void CharStream::clear()
{
    this->reset();
    this->_file = std::nullopt;
    this->_chars = nullptr;
}

const char* CharStream::path() const
{
    if (this->_file.has_value())
        return this->_file.value().path();
    else
        return nullptr;
}

void CharStream::saveStateTemp()
{
    this->_stateTemp = {this->_index, this->_line, this->_column};
}

void CharStream::loadStateTemp()
{
    if (this->_stateTemp.empty())
        throw std::runtime_error("Cannot load empty _stateTemp.");

    this->_index = std::exchange(this->_stateTemp[0], 0);
    this->_line = std::exchange(this->_stateTemp[1], 0);
    this->_column = std::exchange(this->_stateTemp[2], 0);
}

std::string_view CharStream::lineView(const size_t& line)
{
    this->_lineValidation(line);

    const auto& it{this->_statesCache.find(line)};
    if (it->second.size() > 1)
        return {this->_chars + it->second.begin()->first, this->_chars + (it->second.rbegin()->first + 1 == this->_size ? it->second.rbegin()->first + 1 : it->second.rbegin()->first)};
    else
        return {this->_chars + it->second.begin()->first};
}

void CharStream::_set(const char* input, const bool& file)
{
    this->clear();

    if (file)
    {
        this->_file = MemoryMappedFile{input};
        this->_size = this->_file->size();
        this->_chars = this->_file->chars();
    }
    else
    {
        this->_size = std::strlen(input);
        this->_chars = input;
    }
}

void CharStream::_indexValidation(const size_t& index)
{
    if (index < this->_size)
        return;

    throw std::out_of_range("Index " + std::to_string(index) + " is out of bounds (max: " + std::to_string(std::max((size_t)0, this->_size) - 1) + ").");
}

void CharStream::_lineValidation(const size_t& line)
{
    if (line < this->_statesCache.size())
        return;

    throw std::out_of_range("Line " + std::to_string(line) + " is out of bounds (max: " + std::to_string(std::max((size_t)0, this->_statesCache.size()) - 1) + ").");
}

} // namespace nusa