# VISION.md — City Simulator - Documento de Visão

**Tagline:** *Construa do zero. Evolua com sabedoria.*

## 1) Propósito
**City Simulator** é jogo 2D de simulação urbana com estética pixel art top-down, focado na criação e gestão estratégica de cidades. O jogador planeja, constrói e gerencia uma cidade em crescimento, desbloqueando novas tecnologias através de uma árvore de pesquisa para evoluir de uma pequena vila para uma metrópole tecnológica.

## 2) Pilares do Design
### 2.1. Progressão por Tech-Tree
**"Cada escolha define sua prioridade no desenvolvimento da cidade"**
Sistema de tech-tree com ramos específicos (energia, transporte, industria) onde desbloqueios anteriores são pré-requisitos para tecnologias avançadas.

### 2.2. Estética Pixel Art Top-Down Rica
**"Visual RPG Maker com profundidade estratégica"**
Arte 2D top-down estilo RPG Maker, utilizando técnicas de parallax, iluminação e layers para criar a sensação de profundidade e dimensão.

### 2.3 Ciclo de Jogo Viciante
**"Só mais um ajuste..."**
O loop principal de construir -> observar consequências -> ajustar -> ver a cidade crescer deve ser gratificante e repleto de feedbacks visuais e numéricos significativos.

## 3.) Metas de Qualidade e Performance
### 3.1 Performance
**Alvo:** 60 FPS estáveis em cidades até 5k habitantes
**Escalonamento:** 
- 50 FPS em cidades de 8k habitantes
- 45 FPS em cidades de 15k habitantes  
- 30 FPS mínimo em cidades muito extensas (20k+)
**Tecnologia:** C++17 com SFML para gráficos, áudio e input

### 3.2 Campanha para tutorial
**"Você foi escolhido para liderar o acampamento da independencia, quais os seus primeiros passos?"**
"Como vamos atrair pessoas para nosso vilarejo?" -> Desbloqueie Zona Residencial -> Estabeleça primeiro bairro
"Para sobrevivermos precisamos de luz!" -> Pesquise Energia Básica -> Forneça eletricidade à cidade
"Para irmos de um lugar a outro fica mais facil com um caminho!" -> Pesquise Estradas Básicas -> Conecte à Rodovia

**Objetivo Final**: Alcançar População 500 e desbloquear 3 tecnologias.
**Design**: O tutorial é uma série de pequenas missões com texto consiso e setas apontando para UI. É dispensável para jogadores experientes.

## 4.) Escopo do Jogo
### 4.1 Sistema de Zoneamento e Construção
**Zonas**: Residencial (baixa/alta densidade), Comercial (baixa/alta densidade), Industrial (leve/pesada).
**Construções Especiais**: Serviços (bombeiros, polícia, saúde), Educação (escolas, universidades), Parques, Monumentos.
**Ferramentas**: Pincel de zoneamento, ferramenta de demolição, upgrade de estradas.

### 4.2. Sistema de Recursos e Economia
**Orçamento**: Impostos por tipo de zona, financiamento de serviços.
**Recursos**: Eletricidade (termelétrica, eólica, solar), Água (poços, estações de tratamento), Lixo (aterros, incineradores).
**Gráficos**: Painel de orçamento detalhado com receitas/despesas.

### 4.3. Simulação de Agentes e IA
**"Sims" (Cidadãos)**: Agentes visuais com rotinas (casa -> trabalho -> lazer), necessidades (felicidade, educação, saúde) e opiniões que afetam a taxa de crescimento.
**Tráfego**: Sistema de pathfinding para carros, transporte público (ônibus, metrô). O tráfego é um desafio central.

### 4.4. Mundo e Ambiente
**Mapas**: Diferentes biomas (planície, litoral, montanha) com recursos variados.
**Desastres**: Incêndios, inundações, terremotos (configuráveis como on/off).

### 4.5. Progressão e Vitória
**Tecnologias**: Desbloquear novos edifícios e serviços ao atingir certas populações.
**Metas**: Objetivos opcionais (prefeitura nível 5, cidade sem poluição, orçamento positivo por 10 anos).
**Modo Livre/Sandbox**: Sem objetivos fixos.

### 4.6. Simulação com Progressão Tecnológica
**Cidadãos Adaptativos**: Comportamento muda conforme tecnologias disponíveis
**Problemas e Soluções**: Cada tecnologia resolve problemas específicos
**Evolução Visual**: Cidade muda esteticamente conforme tecnologia avança

### 4.7. Estrutura da Árvore Tecnológica (exemplo)

Tecnologias Básicas (Raiz)
├── Infraestrutura
│   ├→ Estradas Básicas → Asfaltamento → Avenidas
│   ├→ Energia Básica → Rede Elétrica → Energia Solar
│   └→ Água e Saneamento → Tratamento → Purificação Avançada
├── Zonas Urbanas
│   ├→ Residencial Básico → Condomínios → Arranha-céus
│   ├→ Comercial Local → Shopping Centers → Distrito Financeiro
│   └→ Indústria Leve → Tecnoparque → Centro de Pesquisa
└── Serviços Públicos
    ├→ Corpo de Bombeiros → Sistema de Prevenção
    ├→ Polícia Municipal → Centro de Monitoramento
    └── Educação Básica → Universidades → Polo Científico

### 4.8. Sistema de Progressão e Pesquisa
**Mecânica Unificada:**
- Ações do jogador → Ganha Experiência (XP) → Sobe de Nível
- Cada nível → Ganha Pontos de Pesquisa
- Edifícios educacionais → Geram Pontos de Pesquisa passivamente

**Pré-requisitos:** Tecnologias anteriores necessárias para avançar
**Especialização:** Escolhas de ramo tecnológico criam cidades únicas

## 5.) Direção de Arte & SFML
### 5.1. Estilo Visual Top-Down
**Referência**: RPG Maker com elementos 3D sutis
**Técnicas**:
- Parallax scrolling para camadas de fundo
- Iluminação dinâmica (dia/noite, iluminação urbana)
- Sprites com múltiplos ângulos para efeito 3D
- Partículas para efeitos especiais (fumaça, chuva, neve)

### 5.2. Interface do Usuário (UI)
**Minimalista**: Barras de informação contextuais, menus recolhíveis.
**Feedback Visual Claro**:
- Cores para indicar zoneamento (verde=residencial, azul=comercial, amarelo=industrial).
- Overlays (poluição, tráfego, valores de terreno) para diagnosticar problemas.
- Ícones de bolha sobre os edifícios mostrando necessidades (e.g., um ícone de "luz" para "sem energia").

## 6.) Arquitetura Técnica (C++)
### 6.1. Motor e Bibliotecas
**Motor Gráfico**: SFML (leve e adequado para 2D/pixel art).
**Física/Colisão**: Biblioteca simples ou customizada.
**Áudio**: SFML Audio

### 6.2. Módulos Principais (exemplos)
class TechTreeSystem {
    std::map<TechID, Technology> technologies;
    std::set<TechID> unlockedTechs;
public:
    bool canUnlock(TechID tech);  // Verifica pré-requisitos
    void researchTechnology(TechID tech);  // Gasta pontos e desbloqueia
};

class TopDownRenderer {
    sf::Texture tileAtlas;  // Spritesheet com todos os tiles
    std::vector<sf::VertexArray> mapLayers;  // Camadas parallax
public:
    void drawParallaxLayers(sf::RenderWindow& window);  // Renderização otimizada
    void applyDynamicLighting();  // Iluminação dinâmica dia/noite
};


### 6.3. Estruturas de Dados Chave
**TileMap**: Matriz 2D para armazenar o terreno, zonas e edifícios.
**Sistema de Entidades (ECS - Entity Component System)**: Gerenciamento eficiente de milhares de entidades (cidadãos, veículos, edifícios).
**Grafos**: Para pathfinding de veículos e cidadãos (A* algorithm).

## 7.) Visão do Roadmap de Desenvolvimento
**Fase de Fundação** (Marcos 1-3): Motor SFML, construção básica, sistemas vitais
**Fase de Expansão** (Marcos 3.5-4.8): Tech-tree progressiva, população, tráfego
**Fase de Polimento** (Marcos 5-11): Tech-tree avançada, serviços, UX, lançamento
*Para detalhes técnicos completos, consulte [ROADMAP.md](ROADMAP.md)*

## 8.) Exemplo de Fluxo de Jogo
1. Começa com tech-tree básica (8 tecnologias) e construções essenciais
2. Realiza ações → Ganha XP → Sobe de nível → Recebe pontos de pesquisa
3. Investe em edifícios educacionais para pesquisa passiva
4. Escolhe ramo tecnológico para especialização estratégica
5. Desbloqueia novas zonas, serviços e infraestrutura
6. Enfrenta novos desafios que exigem pesquisas avançadas
7. Evolui de vila (1k) para metrópole (15k+) com identidade única

**1º Polimento**: Balanceamento da árvore + efeitos visuais de progresso
**2º Polimento**: Balanceamento, tutorial, otimização de performance, sons e música.

## 9.) Filosofia Criativa
*City Simulator é sobre progresso com propósito. Cada decisão molda não apenas a cidade, mas o espírito de quem a conduz. Não se trata de erguer prédios, e sim de criar harmonia.*

—  
*Última edição: 04-11-2025*




