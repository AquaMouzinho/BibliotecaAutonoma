#include "DatabaseMock.hpp"
#include <fstream>
#include <iostream>

DatabaseMock* DatabaseMock::instance = nullptr;
std::mutex DatabaseMock::mutex;

DatabaseMock* DatabaseMock::getInstance(const std::string& filePath) {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new DatabaseMock(filePath);
    }
    return instance;
}


DatabaseMock::DatabaseMock(const std::string& filePath) : filePath(filePath) {
    std::ifstream file(filePath);
    if (file) {
        loadData();
    } else {
        data = {
            {"usuarios", json::array()},
            {"livros", json::array()},
            {"emprestimos", json::array()},
            {"armarios", json::array()},
            {"notificacoes", json::array()},
            {"sessoes", json::array()}
        };
        saveData();
    }
}

DatabaseMock::~DatabaseMock() {
    if (inTransaction) rollback();
    saveData();
}

void DatabaseMock::loadData() {
    std::ifstream file(filePath);
    if (!file.is_open()) throw std::runtime_error("Não foi possível abrir o arquivo de banco de dados");
    file >> data;
}

void DatabaseMock::saveData() {
    std::ofstream file(filePath);
    if (!file.is_open()) throw std::runtime_error("Não foi possível salvar o arquivo de banco de dados");
    file << data.dump(4);
}

bool DatabaseMock::matchesCondition(const json& record, const json& condition) {
    for (auto it = condition.items().begin(); it != condition.items().end(); ++it) {
        const std::string& key = it.key();
        const json& val = it.value();
        if (!record.contains(key) || record[key] != val) {
            return false;
        }
    }
    return true;
    
}

// CRUD
bool DatabaseMock::create(const std::string& table, const json& newData) {
    std::lock_guard<std::mutex> lock(mutex);
    
    if (!data.contains(table)) {
        data[table] = json::array();
    }

    if (inTransaction) {
        transactionCache[table].push_back(newData);
    } else {
        data[table].push_back(newData);
        saveData();
    }
    return true;
}

json DatabaseMock::read(const std::string& table, const json& condition) {
    std::lock_guard<std::mutex> lock(mutex);
    
    if (!data.contains(table)) return json::array();

    json result = json::array();
    for (const auto& record : data[table]) {
        if (condition.empty() || matchesCondition(record, condition)) {
            result.push_back(record);
        }
    }
    return result;
}

bool DatabaseMock::update(const std::string& table, const json& condition, const json& newData) {
    std::lock_guard<std::mutex> lock(mutex);
    
    if (!data.contains(table)) return false;

    bool updated = false;
    for (auto& record : data[table]) {
        if (matchesCondition(record, condition)) {
            record.update(newData);
            updated = true;
        }
    }

    if (updated && !inTransaction) saveData();
    return updated;
}

bool DatabaseMock::remove(const std::string& table, const json& condition) {
    std::lock_guard<std::mutex> lock(mutex);
    
    if (!data.contains(table)) return false;

    auto& tableData = data[table];
    auto newEnd = std::remove_if(tableData.begin(), tableData.end(),
        [&](const json& record) {
            return matchesCondition(record, condition);
        });

    bool removed = (newEnd != tableData.end());
    if (removed) {
        tableData.erase(newEnd, tableData.end());
        if (!inTransaction) saveData();
    }
    return removed;
}

// Transaction Management
bool DatabaseMock::beginTransaction() {
    std::lock_guard<std::mutex> lock(mutex);
    
    if (inTransaction) return false;
    transactionCache = json::object();
    inTransaction = true;
    return true;
}

bool DatabaseMock::commit() {
    std::lock_guard<std::mutex> lock(mutex);
    
    if (!inTransaction) return false;

    for (auto& item : transactionCache.items()) {
        auto& table = item.key();
        auto& records = item.value();
        for (auto& record : records) {
            data[table].push_back(record);
        }
    }
    saveData();
    inTransaction = false;
    return true;
}

bool DatabaseMock::rollback() {
    std::lock_guard<std::mutex> lock(mutex);
    
    inTransaction = false;
    transactionCache.clear();
    return true;
}

// Utilities
void DatabaseMock::resetDatabase() {
    std::lock_guard<std::mutex> lock(mutex);
    
    data = {
        {"usuarios", json::array()},
        {"livros", json::array()},
        {"emprestimos", json::array()},
        {"armarios", json::array()},
        {"notificacoes", json::array()},
        {"sessoes", json::array()}
    };
    saveData();
}

void DatabaseMock::printDebug() const {
    std::lock_guard<std::mutex> lock(mutex);
    
    std::cout << "=== Database State ===" << std::endl;
    std::cout << data.dump(2) << std::endl;
    if (inTransaction) {
        std::cout << "=== Pending Transaction ===" << std::endl;
        std::cout << transactionCache.dump(2) << std::endl;
    }
}