#include "TableType.h"

#include <functional>
#include <cassert>
#include <iostream>
#include <utility>
#include <exception>

using std::string;
using std::greater;
using std::less;
using std::equal_to;
using std::not_equal_to;
using std::move;
using std::ostream;
using std::terminate;

// elt constructors
// const char* method, because otherwise it matches the bool one
TableType::TableType(const char* val) : tag{Tag::String}, data_string{val} {}
TableType::TableType(const string& val) : tag{Tag::String}, data_string{val} {}
TableType::TableType(string&& val) : tag{Tag::String}, data_string{move(val)} {}
TableType::TableType(double val) : tag{Tag::Double}, data_double{val} {}
TableType::TableType(int val) : tag{Tag::Int}, data_int{val} {}
TableType::TableType(bool val) : tag{Tag::Bool}, data_bool{val} {}

// copy/move ctors
TableType::TableType(const TableType& other) : tag{other.tag} {
  construct_from(other);
}
TableType::TableType(TableType&& other) noexcept : tag{other.tag} {
  construct_from(move(other));
}

// dtor
TableType::~TableType() noexcept {
  if (tag == Tag::String)
    data_string.~string();
}

// comparisons
bool TableType::operator<(const TableType& other) const noexcept {
  return compare<less>(other);
}
bool TableType::operator>(const TableType& other) const noexcept {
  return compare<greater>(other);
}
bool TableType::operator==(const TableType& other) const noexcept {
  return compare<equal_to>(other);
}
bool TableType::operator!=(const TableType& other) const noexcept {
  return compare<not_equal_to>(other);
}

// specializations on the as<> template for conversion
template <> const string& TableType::as<string>() const noexcept {
  assert(tag == Tag::String &&
         "tried to use TableType as a string when it didn't contain a string");
  return data_string;
}
template <> double TableType::as<double>() const noexcept {
  assert(tag == Tag::Double &&
         "tried to use TableType as a double when it didn't contain a double");
  return data_double;
}
template <> int TableType::as<int>() const noexcept {
  assert(tag == Tag::Int &&
         "tried to use TableType as an int when it didn't contain an int");
  return data_int;
}
template <> bool TableType::as<bool>() const noexcept {
  assert(tag == Tag::Bool &&
         "tried to use TableType as a bool when it didn't contain a bool");
  return data_bool;
}


namespace std {
// overload to std::hash
size_t hash<TableType>::operator()(const TableType& tt) const noexcept {
  switch (tt.tag) {
  case TableType::Tag::String:
    return hash<string>{}(tt.data_string);
  case TableType::Tag::Double:
    return hash<double>{}(tt.data_double);
  case TableType::Tag::Int:
    return hash<int>{}(tt.data_int);
  case TableType::Tag::Bool:
    return hash<bool>{}(tt.data_bool);
  }
  terminate();
}
}

ostream& operator<<(ostream& os, const TableType& tt) {
  switch (tt.tag) {
  case TableType::Tag::String:
    return os << tt.data_string;
  case TableType::Tag::Double:
    return os << tt.data_double;
  case TableType::Tag::Int:
    return os << tt.data_int;
  case TableType::Tag::Bool:
    return os << tt.data_bool;
  }
  terminate();
}
