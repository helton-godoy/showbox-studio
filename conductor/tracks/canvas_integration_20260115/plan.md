# Implementation Plan: Canvas Integration

This plan outlines the steps to integrate the Showbox Core library with the Showbox-Studio Canvas.

## Phase 1: Project Structure and Linkage

- [ ] Task: Validate CMake configuration for library linking
  - [ ] Ensure `showbox-ui` is correctly exported from the Core repository.
  - [ ] Verify `showbox-studio` CMakeLists.txt correctly finds and links `showbox-ui`.
- [ ] Task: Conductor - User Manual Verification 'Phase 1: Project Structure and Linkage' (Protocol in workflow.md)

## Phase 2: Widget Factory Integration

- [ ] Task: Define a shared Widget Interface/Factory
  - [ ] Write tests for widget instantiation via factory.
  - [ ] Implement/Refactor the factory in `showbox-ui` to be consumable by the Studio.
- [ ] Task: Implement basic widget registration
  - [ ] Register a simple widget (e.g., PushButton) in the factory.
- [ ] Task: Conductor - User Manual Verification 'Phase 2: Widget Factory Integration' (Protocol in workflow.md)

## Phase 3: Canvas Implementation

- [ ] Task: Refactor Studio Canvas to use Core Widgets
  - [ ] Update `Canvas.h`/`.cpp` to host widgets from the factory.
  - [ ] Implement drag-and-drop placeholder logic for Core widgets.
- [ ] Task: Conductor - User Manual Verification 'Phase 3: Canvas Implementation' (Protocol in workflow.md)

## Phase 4: Integration Testing and Cleanup

- [ ] Task: End-to-end test of widget rendering in Canvas
- [ ] Task: Documentation update for the new integration pattern
- [ ] Task: Conductor - User Manual Verification 'Phase 4: Integration Testing and Cleanup' (Protocol in workflow.md)
