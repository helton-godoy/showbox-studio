# Pilha Tecnológica: Showbox Suite

## Linguagens e Frameworks

- **Linguagem Principal:** C++17 (Garante equilíbrio entre performance e recursos modernos).
- **Framework de UI:** Qt 6.6+ (Utilizando QtWidgets para fidelidade desktop, QtCharts para visualização de dados e QtSVG para ícones e ilustrações).
- **Network & I/O:** Qt Network (para possíveis integrações de API).

## Ferramentas de Desenvolvimento

- **Sistema de Build:** CMake (3.16+). A transição de qmake para CMake é prioritária para suportar a modularidade necessária entre Core e Studio.
- **Ambiente de Desenvolvimento:** Obrigatório o uso do container Docker definido em `@src/dev.Dockerfile` para garantir consistência e "pronto para uso".
- **Gerenciamento de Dependências:** CMake FetchContent ou Submodules (para integrar o Core Showbox no Studio).
- **Linter/Formatter:** Ferramentas compatíveis com o padrão C++ (ex: clang-format).

## Arquitetura

- **Estrutura Modular:** O `showbox-suite` é organizado em bibliotecas (`libs/showbox-ui`) e executáveis (`showbox` CLI e `showbox-studio`).
- **Padrões de Design:** Uso intensivo de padrões como Factory (para criação de widgets), Observer (Signals/Slots do Qt) e Singleton (para controladores globais).

## Distribuição e Empacotamento

- **Estratégia de Empacotamento:** Uso de ambientes Docker isolados e otimizados por formato (AppImage, DEB, RPM, Flatpak), localizados em `packaging/**`.
  - Permite builds paralelos.
  - Gera imagens individualmente menores e mais seguras.
- **Formatos Suportados:**
  - **Linux:** AppImage (via `linuxdeploy`), DEB, RPM, Flatpak.
  - **Outros:** Windows (MSIX) e macOS (DMG) planejados.
- **Deploy:** Scripts automatizados em `packaging/` orquestram o build dentro dos containers.
