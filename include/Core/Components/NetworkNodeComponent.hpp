#pragma once

#pragma once

#include <entt/entt.hpp>
#include <vector>

namespace CitySim {

struct NetworkNodeComponent {
    entt::entity nodeEntity{};              // Entidade que representa o nó
    std::vector<entt::entity> connections;  // Entidades conectadas
    bool isActive = false;                  // Se o nó está ativo
    float connectionRange = 1.0f;           // Alcance máximo de conexão
    bool isPowered = false;                 // Se tem energia (usado para nós de energia)
    bool hasWater = false;                  // Se tem água (usado para nós de água)
};

} // namespace CitySim