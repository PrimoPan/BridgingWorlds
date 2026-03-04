# BridgingWorlds

BridgingWorlds 是一个基于 **Unreal Engine 5.4.4** 的 C++ 项目，目标是构建一个用于“入学过渡暴露训练”的 VR MVP。

核心方向：
- 观察者不进行位移（无手柄移动/无走动）
- 仅保留“环视 + 确认（Confirm）”交互
- 场景切换使用淡入淡出（fade-to-black / fade-from-black）以避免突兀切换
- 后续在 Windows 上接入 PICO 手势输入（当前版本仅键盘 Confirm）

## 当前里程碑
已完成最小键盘 Confirm 流程：
- `ABWObserverPawn`：相机观察 Pawn（支持 Turn / LookUp）
- `ABWGameMode`：默认 Pawn 指向 `ABWObserverPawn`
- 输入映射：
  - `Turn` -> `Mouse X`
  - `LookUp` -> `Mouse Y`（负向）
  - `Confirm` -> `Space Bar`
- 按下 Confirm 会输出日志：`[BW] Confirm`，并广播 C++ 多播事件

## 演示
![BridgingWorlds Demo](Docs/preview.gif)

## 技术约束（项目约定）
- 以 C++ 为主，尽量避免 Blueprint 逻辑
- 不直接修改二进制 Unreal 资产（`.uasset` / `.umap`）
- 核心代码保持跨平台（macOS / Windows）

## 运行与验证
1. 使用 UE 5.4.4 打开 `BridgingWorlds.uproject`
2. 编译 C++ 模块
3. 进入 Play 模式验证：
   - 鼠标 X 轴可左右看
   - 鼠标 Y 轴可上下看（反向）
   - 空格触发 Confirm，并在 Output Log 中看到 `[BW] Confirm`
