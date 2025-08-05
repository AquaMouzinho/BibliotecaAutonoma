#pragma once

class SensorPorta {
public:
    virtual ~SensorPorta() = default;
    virtual bool isPortaAberta() const = 0;
    virtual int getArmarioId() const = 0;
};