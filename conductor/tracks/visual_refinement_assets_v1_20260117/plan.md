# Implementation Plan: Visual Refinement & Asset Management

## Phase 1: Specialized Property Delegates

Implementar editores visuais básicos para o `PropertyEditor`.

- [~] Task: Implement Color Picker Delegate
  - [ ] Detect color properties.
  - [ ] Show color preview in cell.
  - [ ] Connect `QColorDialog`.
- [ ] Task: Implement Font Delegate
  - [ ] Detect font properties.
  - [ ] Connect `QFontDialog`.

## Phase 2: Icon Browser & Selection

Integrar o sistema de ícones do Showbox.

- [ ] Task: Create `IconBrowser` Dialog
  - [ ] Grid view listing available SVGs.
  - [ ] Search/Filter by name.
- [ ] Task: Connect `IconBrowser` to PropertyEditor
  - [ ] Add icon preview to cells.
  - [ ] Trigger browser on click.

## Phase 3: Theme Integration & Canvas Styling

- [ ] Task: Implement Theme Selector in Studio
  - [ ] Global dropdown for themes.
- [ ] Task: Apply Live Themes to Canvas
  - [ ] Map selection to `ThemeManager` styles.
  - [ ] Update Canvas stylesheet dynamically.
