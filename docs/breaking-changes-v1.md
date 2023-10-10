# Breaking Changes Related to Imports

In version 1 (`v1`), default imports were supported for `alt-server`, `alt-client`, `alt-shared`, `alt`, and `natives`. However, with the introduction of the v2 module (`v2`), default imports are no longer functional. To adapt to the new changes, you should update your import statements to use the `import * as X from "x"` syntax.

## Example

### Before (Incorrect):

```javascript
import alt from "alt-client";
```

### After (Correct):

```javascript
import * as alt from "alt-client";
```

---

# Enums

All enums, which were previously declared as `const enum` in TypeScript are no longer const because they now exists in JavaScript. All Enum values are also changed to use the `UPPER_SNAKE_CASE` syntax. All Enums are located inside the `alt.Enums` namespace. In addition, the following enums were renamed:

-   `WindowTint` -> `VehicleWindowTint`
-   `NumberPlateStyle` -> `VehicleNumberPlateStyle`
-   `PermissionState` -> `Permission`

# TypeScript Interfaces

-   `IFireInfo` has been removed
-   `IVehicleNeon` -> `VehicleNeonState`
-   `ICloth` -> `Clothing`
-   `IDlcCloth` -> `DlcClothing`
-   `IProp` -> `Prop`
-   `IDlcProp` -> `DlcProp`
-   `IHeadOverlay` -> `Appearance.HeadOverlay`
-   `IHeadBlendData` -> `HeadBlendData`
-   `IBoneInfo` -> `BoneInfo`
-   `IVehicleModel`-> `VehicleModelInfo`
-   `IPedModel` -> `PedModelInfo`
-   `IWeaponModel` -> `WeaponModel`
-   `IAmmoFlags` -> `AmmoData`
-   `IDecoration` has been removed
-   `ICustomBaseObjectMeta` -> `BaseObjectMeta`
-   `ICustomBlipMeta` -> `BlipMeta`
-   `ICustomColshapeMeta` -> `ColShapeMeta`
-   `ICustomCheckpointMeta` -> `CheckpointMeta`
-   `ICustomVoiceChannelMeta` -> `VoiceChannelMeta`
-   `ICustomEntityMeta` -> `EntityMeta`
-   `ICustomPlayerMeta` -> `PlayerMeta`
-   `ICustomVehicleMeta` -> `VehicleMeta`
-   `ICustomEmitEvent` -> `Events.CustomServerToPlayerEvent`
-   `IServerConfig` has been removed
-   `ICustomBaseObjectSyncedMeta` -> `BaseObjectSyncedMeta`
-   `ICustomVirtualEntityStreamSyncedMeta` -> `VirtualEntityStreamSyncedMeta`

# Profiler

The Profiler class in `v1` is now a namespace in `v2` meaning: You can't create a new `Profiler` class instance. Right now, only `takeHeapSnapshot` is available as static method.

# MemoryBuffer class

In `v1`, the `MemoryBuffer` class had a property named `address`. The memory address which was returned by that property was not returning the value you did expect it to return - therefore it has been removed in v2. However, i still added the property and made it log an error message for the time being.
