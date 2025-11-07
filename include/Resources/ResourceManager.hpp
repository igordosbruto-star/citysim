#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <stdexcept>

namespace CitySim {

/**
 * @brief Template base para gerenciamento de recursos
 * @tparam Resource Tipo do recurso a ser gerenciado
 */
template<typename Resource>
class ResourceManager {
public:
    ResourceManager() = default;
    virtual ~ResourceManager() = default;

    /**
     * @brief Carrega um recurso do disco
     * @param path Caminho para o arquivo do recurso
     * @param id Identificador único para o recurso
     * @return true se o carregamento foi bem sucedido
     */
    bool Load(const std::string& path, const std::string& id) {
        auto resource = std::make_shared<Resource>();
        if (!LoadFromFile(*resource, path)) {
            return false;
        }
        m_Resources[id] = resource;
        return true;
    }

    /**
     * @brief Obtém um recurso pelo seu ID
     * @param id Identificador do recurso
     * @return Ponteiro compartilhado para o recurso
     * @throws std::runtime_error se o recurso não for encontrado
     */
    std::shared_ptr<Resource> Get(const std::string& id) {
        auto it = m_Resources.find(id);
        if (it == m_Resources.end()) {
            throw std::runtime_error("Resource not found: " + id);
        }
        return it->second;
    }

    /**
     * @brief Remove um recurso da memória
     * @param id Identificador do recurso
     */
    void Unload(const std::string& id) {
        m_Resources.erase(id);
    }

    /**
     * @brief Remove todos os recursos da memória
     */
    void Clear() {
        m_Resources.clear();
    }

protected:
    /**
     * @brief Carrega um recurso específico do disco
     * @param resource Referência para o recurso a ser carregado
     * @param path Caminho para o arquivo
     * @return true se o carregamento foi bem sucedido
     */
    virtual bool LoadFromFile(Resource& resource, const std::string& path) = 0;

private:
    std::unordered_map<std::string, std::shared_ptr<Resource>> m_Resources;
};

} // namespace CitySim