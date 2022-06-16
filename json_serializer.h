#ifndef JSON_H
#define JSON_H

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// util
// ====

template <class C, class SEP> std::string join(const C &container, const SEP &sep) {
  if (container.empty()) {
    return "";
  }

  std::stringstream stream;

  auto it = container.begin();
  for (; it != container.end() - 1; it++) {
    stream << *it << sep;
  }
  stream << *it;

  return stream.str();
}

template <class T1, class T2, class T3>
inline std::string wrap(const T1 &base, const T2 &start, const T3 &end) {
  std::stringstream stream;
  stream << start << base << end;
  return stream.str();
}

template <class T> std::vector<std::pair<std::string, std::string>> getJsonFields(const T &v);

// type: string, number, bool
// ==========================

inline std::string toJson(std::string value) { return wrap(value, '"', '"'); }

inline std::string toJson(int value) { return std::to_string(value); }
inline std::string toJson(float value) { return std::to_string(value); }
inline std::string toJson(double value) { return std::to_string(value); }

inline std::string toJson(bool value) { return value ? "true" : "false"; }

// type: pointer -> object | null
// ==============================

template <class T> inline std::string toJson(T *value) { return value ? toJson(*value) : "null"; }

template <class T> inline std::string toJson(const std::shared_ptr<T> value) {
  return toJson(value.get());
}

// type: vector -> array
// =====================

template <class T> std::string toJson(std::vector<T> values) {
  std::vector<std::string> elements;
  for (auto v : values) {
    elements.push_back(toJson(v));
  }

  return wrap(join(elements, ","), "[", "]");
}

// type: map -> object
// ===================

template <class T> std::string toJson(std::map<std::string, T> map) {
  std::stringstream stream;

  std::vector<std::string> members;
  for (auto e : map) {
    members.push_back(toJson(e.first) + ":" + toJson(e.second));
  }

  return wrap(join(members, ","), "{", "}");
}

// object: struct -> object
// ========================

template <class T> std::string toJson(const T &value) {
  std::stringstream stream;

  std::vector<std::string> members;
  for (auto e : getJsonFields(value)) {
    members.push_back(toJson(e.first) + ":" + e.second);
  }

  return wrap(join(members, ","), "{", "}");
}

#endif
