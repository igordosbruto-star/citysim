#pragma once

#include <cstdint>
#include <entt/entt.hpp>

namespace CitySim {

struct PowerGridComponent {
    float powerCapacity = 0.0f;     // Capacidade máxima de energia
    float powerOutput = 0.0f;       // Produção atual de energia
    float powerDemand = 0.0f;       // Demanda atual de energia
    bool isPowerPlant = false;      // Se é uma usina de energia
    bool hasPower = false;          // Se tem energia disponível
    entt::entity gridRoot{};        // Entidade raiz da rede elétrica
};

} // namespace CitySim