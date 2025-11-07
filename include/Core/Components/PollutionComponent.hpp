#pragma once

#include <cstdint>

namespace CitySim {

struct PollutionComponent {
    float pollutionLevel = 0.0f;    // Nível atual de poluição
    float pollutionRadius = 0.0f;   // Raio de influência da poluição
    float pollutionRate = 0.0f;     // Taxa de geração de poluição
    bool isGarbageFacility = false; // Se é uma instalação de tratamento de lixo
};

} // namespace CitySim