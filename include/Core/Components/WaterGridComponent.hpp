#pragma once

#include <cstdint>

namespace CitySimulator {

struct WaterGridComponent {
    float waterCapacity = 0.0f;     // Capacidade máxima de água
    float waterOutput = 0.0f;       // Produção atual de água
    float waterDemand = 0.0f;       // Demanda atual de água
    bool isWaterPlant = false;      // Se é uma estação de tratamento
    bool hasWater = false;          // Se tem água disponível
    uint32_t gridId = 0;           // ID da rede de água
};

} // namespace CitySimulator