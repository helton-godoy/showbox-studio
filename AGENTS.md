# SHOWBOX STUDIO - PROJECT KNOWLEDGE BASE

**Generated:** 2026-01-14
**Project Phase:** Planning/Specification

## OVERVIEW

Visual desktop editor for Showbox CLI (PySide6) - currently in planning phase.

## STRUCTURE

```
./
└── AGENT_GUIDE.md    # Complete specification document (346 lines)
```

## WHERE TO LOOK

| Task             | Location             | Notes                                             |
|------------------|----------------------|---------------------------------------------------|
| Project spec     | AGENT_GUIDE.md       | Complete implementation guide, 20 widgets, phases |
| Showbox CLI docs | ../showbox/docs/     | Referenced in spec                                |
| Examples         | ../showbox/examples/ | Reference implementations                         |

## PROJECT STATUS

- **Phase:** Planning (spec only, no code yet)
- **Stack:** Python/PySide6 (planned)
- **Primary Doc:** AGENT_GUIDE.md (346 lines)

## PLANNED STRUCTURE (from AGENT_GUIDE.md)

```
showbox-studio/
├── studio/
│   ├── main.py                 # Entry point
│   ├── models.py               # WidgetModel, ProjectModel
│   ├── generator.py            # Shell script generation
│   ├── parser.py               # Shell -> model parser
│   └── ui/
│       ├── mainwindow.py       # Main window
│       ├── canvas.py           # Preview area
│       ├── palette.py          # Widget palette
│       ├── properties.py       # Property editor
│       ├── inspector.py        # Object inspector
│       ├── codeeditor.py       # Code editor
│       ├── logiceditor.py      # Logic editor
│       └── widgets/            # Canvas widgets (20 types)
├── resources/
│   ├── icons/
│   └── templates/
└── data/
    └── widget_definitions.json  # Widget metadata
```

## CRITICAL RULES (from spec)

1. **Parity Total:** Every Showbox CLI feature must have editor equivalent
2. **Preview Fiel:** Canvas must render identical to real Showbox
3. **Código Válido:** Generated script must execute without errors
4. **UX Intuitiva:** Usable by non-programmers
5. **Sincronização:** Canvas, Inspector, Properties always synced

## 20 WIDGETS TO IMPLEMENT (planned)

**Ação:** pushbutton
**Entrada:** checkbox, radiobutton, textbox, listbox, dropdownlist, combobox, slider, calendar
**Exibição:** label, progressbar, textview, separator, table, chart
**Layout:** frame, groupbox, tabs, page
**Auxiliar:** item, space, stretch

## COMMANDS TO RUN (when implemented)

```bash
# Activate virtual environment
source .venv/bin/activate

# Run editor
python -m studio.main
```
