#pragma once

#include <cstdint>
#include <entt/entt.hpp>

namespace CitySim {

struct WaterGridComponent {
    float waterCapacity = 0.0f;     // Capacidade máxima de água
    float waterOutput = 0.0f;       // Produção atual de água
    float waterDemand = 0.0f;       // Demanda atual de água
    bool isWaterPlant = false;      // Se é uma estação de tratamento
    bool hasWater = false;          // Se tem água disponível
    entt::entity gridRoot{};        // Entidade raiz da rede de água
};

} // namespace CitySim