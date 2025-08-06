#pragma once
#include "IDatabaseConnector.hpp"
#include "DatabaseMock.hpp"
#include <memory>
#include <unordered_map>

class DatabaseConnectorProxy : public IDatabaseConnector
{
private:
  std::shared_ptr<IDatabaseConnector> realDatabase;
  DatabaseMock *mockDatabase;
  bool useMock;
  std::unordered_map<std::string, json> queryCache;

public:
  DatabaseConnectorProxy(const std::string &environment)
  {
    useMock = (environment == "test");
    mockDatabase = DatabaseMock::getInstance();
  }

  bool create(const std::string &table, const json &data) override
  {
    if (useMock)
    {
      return mockDatabase->create(table, data);
    }
    return realDatabase->create(table, data);
  }

  json read(const std::string &table, const json &condition = {}) override
  {
    std::string cacheKey = table + condition.dump();

    if (queryCache.find(cacheKey) != queryCache.end())
    {
      return queryCache[cacheKey];
    }

    json result = useMock ? mockDatabase->read(table, condition)
                          : realDatabase->read(table, condition);

    if (condition.empty())
    {
      queryCache[cacheKey] = result;
    }

    return result;
  }

  bool update(const std::string &table, const json &condition, const json &newData) override
  {
    invalidarCache(table);
    return useMock ? mockDatabase->update(table, condition, newData)
                   : realDatabase->update(table, condition, newData);
  }

  bool remove(const std::string &table, const json &condition) override
  {
    invalidarCache(table);
    return useMock ? mockDatabase->remove(table, condition)
                   : realDatabase->remove(table, condition);
  }

  bool beginTransaction() override
  {
    return useMock ? mockDatabase->beginTransaction()
                   : realDatabase->beginTransaction();
  }

  bool commit() override
  {
    return useMock ? mockDatabase->commit()
                   : realDatabase->commit();
  }

  bool rollback() override
  {
    return useMock ? mockDatabase->rollback()
                   : realDatabase->rollback();
  }

private:
  void invalidarCache(const std::string &table)
  {
    for (auto it = queryCache.begin(); it != queryCache.end();)
    {
      if (it->first.find(table) != std::string::npos)
      {
        it = queryCache.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }
};