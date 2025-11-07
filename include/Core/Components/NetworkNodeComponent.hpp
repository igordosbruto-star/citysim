#pragma once

#include <cstdint>
#include <vector>

namespace CitySimulator {

struct NetworkNodeComponent {
    uint32_t nodeId = 0;                    // ID único do nó na rede
    std::vector<uint32_t> connections;      // IDs dos nós conectados
    bool isActive = false;                  // Se o nó está ativo
    float connectionRange = 1.0f;           // Alcance máximo de conexão
    bool isPowered = false;                 // Se tem energia (usado para nós de energia)
    bool hasWater = false;                  // Se tem água (usado para nós de água)
};

} // namespace CitySimulator