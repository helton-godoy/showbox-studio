# Implementation Plan: Studio Canvas & Palette Integration

Este plano detalha a transformação do Showbox Studio em um designer funcional.

## Phase 1: Canvas Hosting & Builder Integration

Fazer o Canvas ser capaz de renderizar e gerenciar widgets do Showbox.

- [ ] Task: Integrate `ShowboxBuilder` into `Canvas`
  - [ ] Update `Canvas` to hold a reference to `IShowboxBuilder`
  - [ ] Implement a `renderPreview(const WindowConfig&)` method
- [ ] Task: Interactive Selection Logic
  - [ ] Implement visual highlight for selected widgets in the Canvas
  - [ ] Emit signals when a widget is clicked

## Phase 2: Widget Palette (Drag & Drop Prep)

Criação da barra de ferramentas com todos os widgets disponíveis.

- [ ] Task: Implement `WidgetPalette` Component
  - [ ] Create a list/grid of widget types (Icon + Name)
  - [ ] Implement Drag initiation from Palette
- [ ] Task: Drop Handling in Canvas
  - [ ] Implement logic to detect drop and call appropriate `builder->build*` method

## Phase 3: Object Inspector Sincronization

- [ ] Task: Dynamic Tree Population
  - [ ] Sync `ObjectInspector` tree view with the current Canvas hierarchy
  - [ ] Handle selection changes bidirectionally (Tree <-> Canvas)

## Phase 4: Reactive Property Editor

- [ ] Task: Property Mapping
  - [ ] Implement logic to display fields in `PropertyEditor` based on selected widget config
  - [ ] Implement "Live Update": changing a value in the editor updates the Canvas widget immediately

## Phase 5: Studio Validation

- [ ] Task: Full Design Flow Demo
  - [ ] Create a "Login Screen" from scratch using the Studio
  - [ ] Verify if the generated state matches the expected Showbox logic
