#pragma once
#include "IDatabaseConnector.hpp"
#include <fstream>
#include <filesystem>
#include <mutex>

class DatabaseMock : public IDatabaseConnector {
private:
    static DatabaseMock* instance;
    static std::mutex mutex;

    std::string filePath;
    json data;
    json transactionCache;
    bool inTransaction = false;

    explicit DatabaseMock(const std::string& filePath = "db_fake.json");
    ~DatabaseMock();

    void loadData();
    void saveData();
    bool matchesCondition(const json& record, const json& condition);

public:
DatabaseMock(const DatabaseMock&) = delete;
DatabaseMock& operator=(const DatabaseMock&) = delete; 

    static DatabaseMock* getInstance(const std::string& filePath = "db_fake.json");

    // CRUD
    bool create(const std::string& table, const json& data) override;
    json read(const std::string& table, const json& condition = {}) override;
    bool update(const std::string& table, const json& condition, const json& newData) override;
    bool remove(const std::string& table, const json& condition) override;

    // Transações
    bool beginTransaction() override;
    bool commit() override;
    bool rollback() override;

    // Utilitários
    void resetDatabase();
    void printDebug() const;
};