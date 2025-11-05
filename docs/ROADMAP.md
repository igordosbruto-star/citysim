# ROADMAP.md — City Simulator

> Este roadmap é um **documento vivo**.  
> **Revisão:** quinzenal ou por release.  
> **Última atualização:** 04-11-2025
> **Status:** `Planned` · `In Progress` · `Done` ·

## Histórico de alterações
- 04-11-2025 — Criação do roadmap inicial (M0–M3).


---

## **Visão Geral**
O Roadmap do **City Simulator** é estruturado em **fases de crescimento**, assim como a própria cidade que o jogo simula.  
Cada marco representa uma **camada de maturidade**: da fundação do motor à metrópole funcional e refinada.  

**Progressão de Escala:**
Marco 3.5 → 1k habitantes  (Vila)
Marco 4   → 2k habitantes  (Cidade Pequena)  
Marco 4.5 → 5k habitantes  (Cidade Média)
Marco 4.8 → 8k habitantes  (Cidade Desenvolvida)
Marco 5   → 15k habitantes (Metrópole)
Marco 6+  → 20k+ habitantes (Megacidade)

Cada marco contém:  
- 🎯 **Meta:** o objetivo principal da etapa.  
- 🧱 **Entregas:** o que será construído ou implementado.  
- ✅ **Definition of Done (DOD):** critérios objetivos que determinam a conclusão.  

---

> *"Cada versão é um novo alicerce; cada marco, um tijolo na cidade dos sonhos."*

---

## Visão geral de marcos (releases)

## 🏗️ **Marco 1 — Fundação Técnica (Engine e Estrutura Base)**
### 🎯 Meta
Estabelecer o núcleo técnico e a base estrutural do projeto em C++ com SFML.

### 🧱 Entregas
- Configuração do ambiente de desenvolvimento (SFML, CMake, Git).  
- Sistema de renderização top-down 2D funcional (tilemap básico).  
- Estrutura ECS (Entity Component System) inicial para gerenciar entidades.  
- Sistema de input e atualização de entidades por frame.  
- Prova de conceito com mapa estático renderizado.  
- Estrutura base do editor (wxWidgets, OpenGL, GLEW).
- Janela principal do editor com painéis básicos.

### ✅ Definition of Done
- Projeto compila e roda a 60 FPS em mapa 2D.  
- Câmera movimentável com teclado/mouse.  
- Um tilemap é carregado e exibido corretamente.  
- Estrutura ECS reconhece e atualiza entidades genéricas (ex: “Edifício”, “Cidadão”, “Veículo”).  
- Build estável e versionado no repositório.  
- Editor compila e abre uma janela com painéis vazios.
- Comunicação básica entre editor e motor do jogo.

---

## 🌱 **Marco 2 — Interatividade e Construção**
### 🎯 Meta
Permitir que o jogador interaja com o mapa e construa elementos básicos.

### 🧱 Entregas
- Ferramentas de construção e zoneamento (residencial, comercial, industrial).  
- Sistema de remoção/demolição.  
- UI inicial com botões de seleção e feedback visual.  
- Armazenamento de mapa em formato de dados (JSON ou binário).  
- Primeiros efeitos visuais de feedback (sombras, seleção, partículas leves).  
- Ferramentas de edição de mapas no editor (pincel, borracha, preenchimento).
- Painel de propriedades para edição de tiles e zonas.

### ✅ Definition of Done
- Jogador pode construir e remover zonas livremente.  
- Zonas são salvas e carregadas corretamente.  
- Interface responde instantaneamente às ações do jogador.  
- Nenhum crash crítico durante 10 minutos de uso contínuo.  
- Editor permite carregar, editar e salvar mapas. 
- Ferramentas de edição respondem em tempo real.

---

## ⚡ **Marco 3 — Sistemas Vitais (Energia, Água, Lixo)**
### 🎯 Meta
Implementar as fundações dos sistemas urbanos essenciais para a simulação.

### 🧱 Entregas
- Sistema de energia elétrica (geradores, linhas de transmissão).  
- Sistema de abastecimento de água (estações e encanamento básico).  
- Sistema de coleta de lixo e poluição.  
- Overlays visuais para cada sistema (exibição de cobertura).  
- Indicadores simples de falha (ex: ícone “sem energia”).
- Editor de redes de energia e água
- Overlays no editor para mostrar redes

### ✅ Definition of Done
- Cada sistema opera de forma independente e visualizável via overlay.  
- Cidades pequenas funcionam com equilíbrio energético e hídrico.  
- Poluição afeta a satisfação dos cidadãos.  
- Todos os dados persistem entre saves.  
- Editor permite colocar e conectar usinas, tubulações, etc.
- Overlays mostram a cobertura dos sistemas

---

🔬 **Marco 3.5 — Tech-Tree Básica (Fundação)**

### 🔗 Dependências
- Sistemas de energia e água do Marco 3 funcionais
- Sistema de construção do Marco 2 estável
- Save/Load do Marco 2 operacional

### 🎯 Meta
Implementar a estrutura fundamental do sistema de tecnologia e integrar com sistemas de recursos existentes.

### 🧱 Entregas
- Estrutura de dados para tech-tree (nós, conexões, estados)
- UI básica da árvore tecnológica (navegação mínima viável)
- Sistema de desbloqueio para 5-10 tecnologias fundamentais
- Integração com construção - algumas construções requerem techs específicas
- Sistema de pontos de pesquisa básico (geração e consumo)
- Editor de tech-tree básico (adicionar nós, conexões)
- Visualização da árvore tecnológica no editor

🎮 Tecnologias Iniciais Propostas:

```txt
Tecnologias Básicas (Raiz) - DESBLOQUEADAS
├── Infraestrutura
│   ├→ Estradas Básicas [Nova]
│   ├→ Energia Básica [Nova] 
│   └→ Água e Saneamento [Nova]
└── Zonas Urbanas
    ├→ Residencial Básico [Desbloqueado]
    ├→ Comercial Básico [Desbloqueado]
    └→ Industrial Básico [Desbloqueado]
```

✅ Definition of Done
- Jogador pode abrir a interface de tech-tree (tecla T)
- 8 tecnologias implementadas com pré-requisitos funcionando
- Sistema de pontos de pesquisa gera/acumula/gasta corretamente
- 3 construções exigem tecnologias específicas para serem builtadas
- Save/Load preserva estado da tech-tree
- UI responsiva e intuitiva para navegação básica
- Editor permite criar e editar tecnologias
- Pré-requisitos podem ser definidos visualmente

---

🧭 **Marco 4 — População e Economia Básica**
### 🎯 Meta
Implementar a simulação fundamental de cidadãos e sistema econômico mínimo para viabilizar o crescimento da cidade.

### 🧱 Entregas
- Simulação de cidadãos ("Sims") com necessidades básicas (moradia, trabalho).
- Sistema de impostos e despesas essenciais (serviços básicos).
- HUD de orçamento simplificado (receita/despesa/saldo).
- Crescimento populacional baseado em disponibilidade de empregos e moradias.
- Sistema de felicidade básico (emprego, moradia, serviços essenciais).
- Editor de atributos de cidadãos e edifícios
- Painel de estatísticas da cidade no editor

### ✅ Definition of Done
- Cidadãos são gerados conforme zoneamento residencial disponível.
- Economia opera com orçamento equilibrado em cidades pequenas (< 2k habitantes).
- População cresce/decresce baseado em fatores básicos de satisfação.
- Feedback visual básico (ícones de felicidade sobre zonas).
- FPS mantido ≥ 50 em simulações com 5k habitantes.
- Editor permite ajustar parâmetros de simulação
- Estatísticas são atualizadas em tempo real

---

🚦 **Marco 4.5 — Tráfego e Mobilidade Urbana**
### 🎯 Meta
Implementar sistema de tráfego e transporte que afeta a eficiência da cidade.

### 🧱 Entregas
- Sistema de pathfinding A* para veículos e cidadãos.
- Simulação de tráfego entre zonas conectadas (casa → trabalho → comércio).
- Indicadores de congestionamento e eficiência de rotas.
- Ferramentas básicas de gestão de tráfego (estradas de mão dupla/única).
- Overlay de tráfego para visualização de fluxo.
- Editor de rotas e tráfego
- Ferramentas de desenho de estradas e definição de sentidos

### ✅ Definition of Done
- Veículos trafegam entre zonas de forma realista.
- Congestionamentos afetam tempo de deslocamento e felicidade.
- Sistema de pathfinding eficiente (≤ 10ms por rota calculada).
- **Otimização:** Máximo 500 veículos simulados simultaneamente
- **Performance:** FPS ≥ 45 com tráfego ativo (5k habitantes)
- Jogador pode identificar e solucionar problemas básicos de tráfego.
- Editor permite desenhar estradas e configurar tráfego
- Simulação de tráfego pode ser visualizada no editor



🔬 **Marco 4.8 — Expansão da Tech-Tree**
### 🔗 Dependências
- Sistema de população do Marco 4 funcional
- Economia básica estável
- Tech-tree básica do Marco 3.5 operacional

### 🎯 Meta
Expandir para 25 tecnologias com efeitos de gameplay simples e balanceamento inicial.

### 🧱 Entregas
- 25 tecnologias balanceadas cobrindo todos os ramos principais
- Efeitos básicos de eficiência (ex: +10% produção, -5% custos)
- Fontes de pesquisa adicionais (edifícios educacionais básicos)
- Sistema de especialização inicial (2 ramos por categoria)
- UI melhorada com tooltips e feedback visual
- Editor de tech-tree expandido (25 tecnologias)
- Ferramentas de balanceamento no editor

### ✅ Definition of Done
- 25 tecnologias implementadas e testadas
- Efeitos aplicados corretamente na simulação
- Balanceamento: nenhuma tecnologia claramente superior
- UI permite navegação fácil entre 25+ tecnologias
- Save/Load funciona com estado expandido
- Editor suporta 25 tecnologias com todos os atributos
- Balanceamento pode ser ajustado via editor

---

🔬 **Marco 5 — Tech-Tree Avançada e Progressão Complexa**
### 🔗 Dependências
- Todos os sistemas anteriores (1-4.8) estáveis
- População de até 10k habitantes suportada
- Economia complexa funcionando

### 🎯 Meta
Expandir e aprofundar o sistema de tecnologia com ramificações estratégicas, efeitos complexos e integração completa com todos os sistemas do jogo.

### 🧱 Entregas
- Tech-tree completa com 40-50 tecnologias organizadas em ramos especializados
- Sistema de ramificações exclusivas - escolhas que abrem caminhos únicos
- Efeitos avançados de tecnologias:
 - Bônus de eficiência (ex: +20% produção energética)
 - Redução de custos de manutenção
 - Novas mecânicas de gameplay (políticas, impostos especiais)
 - Transformações estéticas em edifícios e veículos
- Múltiplas fontes de pesquisa:
 - Universidades e centros de pesquisa
 - Eventos aleatórios
 - Conquistas de população
- Editor de tech-tree avançado (50 tecnologias, ramificações)
- Ferramentas de teste de balanceamento no editor

- Sistema de especialização - árvores focadas em diferentes estilos de jogo
- UI polida com tooltips detalhados, arte temática e feedback visual rico

🎮 Exemplo de Ramificações:

```txt
Energia →
├── Ramo Verde: Solar → Eólica → Nuclear Limpa
└── Ramo Tradicional: Carvão → Petróleo → Nuclear

Transporte →
├── Ramo Individual: Carros → Rodovias → Auto-estradas
└── Ramo Coletivo: Ônibus → Metrô → Trens-bala
```

✅ Definition of Done
- Todas as 45+ tecnologias implementadas e balanceadas
- Sistema de ramificações funcionando (escolhas irreversíveis)
- Efeitos de tecnologia afetam visivelmente 3+ sistemas do jogo
- Múltiplas estratégias viáveis (ex: cidade ecológica vs industrial)
- UI/UX polida com feedback imediato das consequências
- Save/Load mantém todo o estado complexo da tech-tree
- Performance: carregamento da tech-tree em < 2 segundos
- Editor suporta ramificações e efeitos complexos
- Testes de balanceamento podem ser rodados no editor

---

## 🏙️ **Marco 6 — Sistema de Serviços Públicos e Desastres**
### 🎯 Meta
Adicionar complexidade e imersão por meio de serviços e eventos emergentes.

### 🧱 Entregas
- Implementação de Bombeiros, Polícia, Saúde e Educação.  
- Modelagem de alcance de serviços e tempo de resposta.  
- Sistema de desastres configurável (fogo, inundação, terremoto).  
- Notificações e alertas visuais/sonoros de eventos.  
- Editor de serviços públicos (bombeiros, polícia, etc.)
- Editor de eventos de desastres


### ✅ Definition of Done
- Todos os serviços funcionam e impactam o bem-estar dos cidadãos.  
- Desastres afetam infraestrutura e exigem respostas adequadas.  
- Configuração “on/off” de desastres acessível via menu.  
- Cidades resilientes recompensam o jogador com bônus de satisfação.  
- Editor permite colocar e configurar serviços
- Eventos de desastres podem ser criados e configurados

---

## 💡 **Marco 7 — Refinamento Visual e Atmosférico**
### 🎯 Meta
Transformar a cidade em um espaço vivo e cativante.

### 🧱 Entregas
- Ciclo de dia/noite dinâmico.  
- Iluminação urbana e reflexos sutis.  
- Efeitos climáticos (chuva, neve, partículas).  
- Sons ambientes e trilha sonora procedural.  
- Animações leves nos edifícios e sprites dinâmicos.  
- Editor de efeitos visuais (dia/noite, clima)
- Preview de iluminação e partículas no editor

### ✅ Definition of Done
- Atmosfera muda visivelmente com o tempo.  
- Sons e clima reagem ao estado da cidade.  
- Nenhum impacto perceptível no desempenho (FPS > 50 em média).  
- Visual consistente e coeso em todos os biomas.  
- Editor permite ajustar ciclos e efeitos climáticos
- Preview mostra as mudanças em tempo real

---

## 🪙 **Marco 8 — Interface, UX e Tutoriais**
### 🎯 Meta
Aperfeiçoar a experiência do jogador com clareza, onboarding e fluidez.

### 🧱 Entregas
- UI redesenhada com hierarquia lógica e estética minimalista.  
- Tutorial interativo “Acampamento da Independência”.  
- Sistema de dicas contextuais.  
- Indicadores animados para ações importantes.  
- Editor de interface de usuário (layouts, temas) 
- Editor de tutoriais e missões

### ✅ Definition of Done
- Jogadores conseguem jogar sem instruções externas.  
- Tutorial completo em até 10 minutos.  
- Feedbacks de erro e sucesso claros.  
- Todos os menus funcionais e sem bugs críticos.  
- Editor permite criar e editar interfaces de usuário
- Tutoriais e missões podem ser criados no editor

---

## 🚀 **Marco 9 — Alpha Playtest (Versão Interna)**
### 🎯 Meta
Testar o jogo de ponta a ponta com público restrito.

### 🧱 Entregas
- Build jogável completa (do início ao sandbox).  
- Ferramentas internas de debug (FPS, logs, estatísticas).  
- Sistema de feedback interno (relato de bugs e sugestões).  
- Balanceamento inicial da economia e progressão.  
- Ferramentas de debug no editor
- Exportação de builds de teste

### ✅ Definition of Done
- Build jogável e estável por 1h sem crash.  
- Feedback positivo de pelo menos 70% dos testadores.  
- Lista de bugs priorizada e documentada.  
- Editor inclui ferramentas para debug e análise de performance
- Builds de teste podem ser geradas a partir do editor

---

## 🌈 **Marco 10 — Beta e Polimento Final**
### 🎯 Meta
Preparar o jogo para o público com otimização, identidade e alma.

### 🧱 Entregas
- Ajustes finos de balanceamento e performance.  
- Polimento de UI, música e partículas.  
- Implementação de conquistas e estatísticas.  
- Logotipo, menu principal, créditos e branding visual.  
- Polimento da interface do editor
- Documentação do editor

### ✅ Definition of Done
- FPS estável em todas as resoluções suportadas.  
- Nenhum bug bloqueante.  
- Identidade visual e sonora coesa.  
- Build considerada “Beta Jogável” pronta para distribuição.  
- Interface do editor é intuitiva e estável
- Documentação completa do editor está disponível

---

## 🏁 **Marco 11 — Lançamento e Pós-Lançamento**
### 🎯 Meta
Lançar a versão pública inicial e planejar futuras expansões.

### 🧱 Entregas
- Publicação oficial da versão 1.0.  
- Canal de feedback da comunidade (Discord, formulário, etc).  
- Patch 1.0.1 (hotfix inicial).  
- Planejamento de DLCs ou atualizações gratuitas (novos biomas, políticas, tecnologias).  
- Lançamento do editor junto com o jogo
- Suporte a mods via editor

### ✅ Definition of Done
- Jogo publicado e funcional.  
- Comunidade ativa com suporte básico.  
- Relatórios de crash monitorados e corrigidos.  
- Roadmap futuro (v1.1+) documentado. 
- Editor está estável e pronto para uso pela comunidade
- Sistema de modding integrado ao editor 

---

> *“Uma cidade nunca está realmente pronta. Ela apenas continua crescendo — assim como quem a sonhou.”*

---

## Governança & contribuição
- **Owner do roadmap:** *(Wesley Roque)*  
- **Processo:** PR com rótulo `roadmap` + descrição breve do ajuste; revisão quinzenal.  
- **Guia:** ver `CONTRIBUTING.md`.

