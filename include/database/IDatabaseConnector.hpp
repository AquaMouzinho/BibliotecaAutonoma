#pragma once
#include "../../json.hpp"
#include <string>

using json = nlohmann::json;

class IDatabaseConnector {
public:
    virtual ~IDatabaseConnector() = default;

    // Operações básicas
    virtual bool create(const std::string& table, const json& data) = 0;
    virtual json read(const std::string& table, const json& condition = {}) = 0;
    virtual bool update(const std::string& table, const json& condition, const json& newData) = 0;
    virtual bool remove(const std::string& table, const json& condition) = 0;

    // Operações transacionais
    virtual bool beginTransaction() = 0;
    virtual bool commit() = 0;
    virtual bool rollback() = 0;
};