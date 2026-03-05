# Pico 4U Demo 阶段：Insta360 X4 生活场景 360 素材与 Nadir 处理 SOP（Studio + 4K 轻量 + 软遮罩快交付）

## 摘要
本方案面向当前 Demo 目标，优先“稳定交付 + 降低 ASD 用户刺激风险”：
1. 采集阶段尽量减少三脚架可见性。
2. 后期阶段用 Insta360 Studio 产出统一 4K 轻量素材。
3. 播放阶段在 UE 里加“低头渐暗”软遮罩（不限制 VR 俯仰），隐藏 nadir 三脚架区域。

已锁定决策：`Insta360 Studio`、`4K 轻量档`、`软遮罩快交付`、头显 `Pico 4U`、目标稳定 `72fps` 运行体验。

## Public APIs / Interfaces / Types（实现时新增/调整）
在 `ABWObserverPawn` 增加可配置参数（C++，不改 `.umap/.uasset`）：
1. `bool bEnableNadirComfortFade = true;`
2. `float NadirFadeStartPitchDeg = -55.0f;`
3. `float NadirFadeFullPitchDeg = -80.0f;`
4. `float NadirFadeMaxAlpha = 0.35f;`
5. `FLinearColor NadirFadeColor = FLinearColor::Black;`
6. `float NadirFadeInterpSpeed = 3.0f;`

运行逻辑接口：
1. 在 `Tick` 或等价更新点读取当前 pitch。
2. 将 pitch 映射到 `[0, NadirFadeMaxAlpha]`。
3. 调用 `PlayerCameraManager->SetManualCameraFade(Alpha, NadirFadeColor, false)`。
4. 离开 Pawn/EndPlay 时将 fade 归零，避免残留。

## 执行步骤（Decision Complete）
## 1) 拍摄前（现场规范）
1. 相机高度固定在儿童视角优先：`1.20m–1.35m`。
2. 机位采用“竖直隐形杆 + 小底座”，杆体与相机中轴保持同线。
3. 每个场景先做 10 秒环境观察，确认底部区域尽量是“低纹理地面/地毯”，减少后续 nadir 注意力。
4. 灯光频闪环境统一用本地工频（国内场景按 50Hz）。
5. 同一房间内固定白平衡，不用自动白平衡跳变。

## 2) 现场拍摄（X4）
1. 每条素材前后各保留 3 秒静止段。
2. 推荐主拍规格：`5.7K 30fps`（兼顾热管理与稳定）。
3. 高运动场景可拍 `5.7K 60fps`，但仅用于必要镜头。
4. 命名规则：`School_Scene##_Take##`，记录机位高度与拍摄时间。

## 3) Studio 后期导出（Demo 统一）
1. 在 Insta360 Studio 做拼接、基础校正、裁切。
2. 统一导出 `equirectangular 2:1`。
3. Demo 默认导出：`3840x1920, H.265, 30fps`。
4. 码率起始建议：`35–50 Mbps`（先保稳定，后续按 Pico 实测调）。
5. 输出目录按场景分层：`/Panos/School/<SceneName>/final_4k.mp4`。

## 4) UE 运行时 Nadir 软遮罩（不改地图资产）
1. 不做 VR 俯仰限制（允许自然低头）。
2. 仅在低头区间触发渐暗：`-55°` 开始，`-80°` 到最大。
3. 最大遮罩强度固定为 `0.35`，避免突兀黑屏。
4. 渐变速度固定平滑，不做瞬时跳变。
5. 该逻辑默认开启，但可通过参数一键关闭用于对照测试。

## 5) Pico 4U 端验收
1. 连续播放 10 分钟无明显掉帧/卡顿。
2. 正常视角无任何额外遮挡感。
3. 低头到 nadir 区域时，三脚架不可辨识或不吸引注意。
4. 抬头时遮罩平滑消失，无闪烁/突变。
5. ASD 观察标准：无突发视觉刺激、无亮度泵动、无突然黑场。

## 测试用例与场景
1. `静态教室`：低头/抬头循环 20 次，观察遮罩稳定性。
2. `动态走廊`：画面内有人移动，检查遮罩是否干扰主体关注。
3. `高亮窗边`：检查曝光与遮罩叠加是否造成不适。
4. `边界角度`：pitch 在 `-54/-56/-79/-81` 四个点验证插值连续性。
5. `长时测试`：单场景 15 分钟佩戴，确认无明显疲劳诱因。

## 假设与默认值
1. 当前阶段以 Demo 稳定交付为第一优先，不追求逐帧无痕手工地面修补。
2. 后续如果进入正式发布阶段，再把关键镜头升级为“手工纹理 nadir 修补”。
3. 当前不修改 `.umap/.uasset`；若后续需要材质/后处理资产，会提供独立 in-editor checklist。

## 参考资料
1. Insta360 Studio 导出与拼接（官方）：https://onlinemanual.insta360.com/x4/en-us/camera/stitching/studio
2. 隐形自拍杆使用要点（官方）：https://onlinemanual.insta360.com/x4/en-us/tutorial/app/editing/invisibleselfiestick
3. Nadir Logo 相关设置入口（官方支持）：https://www.insta360.com/support/supportcourse?post_id=15735
