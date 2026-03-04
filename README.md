# BridgingWorlds

## 中文说明

BridgingWorlds 是一个基于 **Unreal Engine 5.4.4** 的 C++ 项目，目标是构建一个用于“入学过渡暴露训练”的 VR MVP。

### 项目目标
- 观察者不进行位移（无手柄移动/无走动）
- 仅保留“环视 + 确认（Confirm）”交互
- 场景切换使用淡入淡出（fade-to-black / fade-from-black）避免突兀变化
- 后续在 Windows 上接入 PICO 手势输入（当前阶段仅键盘 Confirm）

### 当前里程碑
已完成最小键盘 Confirm 流程：
- `ABWObserverPawn`：相机观察 Pawn（支持 Turn / LookUp）
- `ABWGameMode`：默认 Pawn 设置为 `ABWObserverPawn`
- 输入映射：
  - `Turn` -> `Mouse X`
  - `LookUp` -> `Mouse Y`（负向）
  - `Confirm` -> `Space Bar`
- 按下 Confirm 输出日志：`[BW] Confirm`，并广播 C++ 多播事件

### 演示
![BridgingWorlds Demo](Docs/preview.gif)

### 技术约束
- 以 C++ 为主，尽量避免 Blueprint 逻辑
- 不直接修改二进制 Unreal 资产（`.uasset` / `.umap`）
- 核心代码保持跨平台（macOS / Windows）

### 运行与验证
1. 使用 UE 5.4.4 打开 `BridgingWorlds.uproject`
2. 编译 C++ 模块
3. 进入 Play 模式并验证：
   - 鼠标 X 轴可左右观察
   - 鼠标 Y 轴可上下观察（反向）
   - 空格触发 Confirm，Output Log 显示 `[BW] Confirm`

---

## English

BridgingWorlds is a **Unreal Engine 5.4.4** C++ project for an MVP focused on VR exposure training for school transition.

### Project Goal
- No locomotion for the viewer (no controller movement / walking)
- Keep interaction minimal: look around + Confirm
- Use fade-to-black / fade-from-black for scene transitions
- Integrate PICO hand gesture input later on Windows (keyboard Confirm only for now)

### Current Milestone
A minimal keyboard Confirm pipeline is implemented:
- `ABWObserverPawn`: observer pawn with camera (Turn / LookUp)
- `ABWGameMode`: default pawn set to `ABWObserverPawn`
- Input mappings:
  - `Turn` -> `Mouse X`
  - `LookUp` -> `Mouse Y` (negative scale)
  - `Confirm` -> `Space Bar`
- On Confirm press: logs `[BW] Confirm` and broadcasts a C++ multicast event

### Demo
![BridgingWorlds Demo](Docs/preview.gif)

### Technical Constraints
- C++-first implementation, avoid Blueprint-heavy logic
- Do not directly modify binary Unreal assets (`.uasset` / `.umap`)
- Keep core code platform-agnostic (macOS / Windows)

### Run & Verify
1. Open `BridgingWorlds.uproject` in UE 5.4.4
2. Compile C++ modules
3. Enter Play mode and verify:
   - Mouse X rotates yaw
   - Mouse Y rotates pitch (inverted)
   - Space triggers Confirm and logs `[BW] Confirm` in Output Log
