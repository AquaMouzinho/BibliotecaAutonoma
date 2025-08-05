#ifndef SENSOR_RFID_HPP
#define SENSOR_RFID_HPP

#include <vector>
#include <string>
#include <functional>
#include <atomic>

class SensorRFID {
public:
    virtual ~SensorRFID() = default;

    // Interface principal
    virtual void setCallbackLeitura(std::function<void(const std::string&)> callback) = 0;
    virtual std::vector<std::string> getTagsDetectadas() const = 0;
    virtual void iniciarMonitoramento() = 0;
    virtual void pararMonitoramento() = 0;

    // Métodos para simulação (apenas para testes)
    virtual void simularLeitura(const std::string& tag) = 0;
    virtual void simularRemocao(const std::string& tag) = 0;
    virtual void limparTags() = 0;
};

#endif