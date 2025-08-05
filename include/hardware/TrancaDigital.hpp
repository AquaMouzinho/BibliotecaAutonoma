#pragma once

class TrancaDigital {
public:
    virtual ~TrancaDigital() = default;
    virtual void liberar() = 0;
    virtual void trancar() = 0;
    virtual bool estaTrancada() const = 0;
    virtual int getArmarioId() const = 0;
};