#pragma once

#include <cstdint>

namespace CitySimulator {

struct PowerGridComponent {
    float powerCapacity = 0.0f;     // Capacidade máxima de energia
    float powerOutput = 0.0f;       // Produção atual de energia
    float powerDemand = 0.0f;       // Demanda atual de energia
    bool isPowerPlant = false;      // Se é uma usina de energia
    bool hasPower = false;          // Se tem energia disponível
    uint32_t gridId = 0;           // ID da rede elétrica
};

} // namespace CitySimulator