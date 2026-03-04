# BridgingWorlds (UE 5.4.4) ¡ª Codex Project Instructions

## Project goal
Build a UE 5.4.4 C++ MVP for VR school-transition exposure:
- Viewer does NOT locomote (no controller movement). Only look around + simple Confirm input.
- Always use fade-to-black / fade-from-black when switching scenes (avoid sudden changes).
- Later on Windows, replace keyboard Confirm with PICO hand gesture input. Do NOT add PICO dependencies now.

## Hard constraints (must follow)
- C++ is the primary implementation. Avoid Blueprint logic unless explicitly requested.
- Do NOT modify binary Unreal assets directly (.uasset/.umap). If an asset is needed, output a short in-editor checklist.
- Keep the core code platform-agnostic (macOS + Windows). No PICO/OpenXR plugin code in core.
- Any platform-specific input must be isolated (future work). For now: keyboard Confirm.

## Immediate task (first milestone)
Create a minimal keyboard-driven ¡°Confirm¡± pipeline:
1) Add ABWObserverPawn (APawn) with a Camera.
2) Bind inputs:
   - Axis: Turn (Mouse X), LookUp (Mouse Y with negative scale)
   - Action: Confirm (Space Bar)
   On Confirm: log ¡°[BW] Confirm¡± and expose a C++ multicast delegate/event.
3) Add ABWGameMode (AGameModeBase) and set DefaultPawnClass to ABWObserverPawn.
4) Configure defaults via .ini edits:
   - Set GlobalDefaultGameMode to BWGameMode in Config/DefaultEngine.ini
   - Ensure mappings exist in Config/DefaultInput.ini
5) Add a repo-root .gitignore suitable for Unreal C++ on macOS/Windows.

## Repo conventions
- Keep diffs small and compile-safe.
- Prefer minimal includes and Unreal naming conventions.
- After edits, summarize changed files and why.