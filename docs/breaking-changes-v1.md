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

# TypeScript Interfaces

-   `IFireInfo` has been removed
-   `IVehicleNeon` renamed to `VehicleNeonState`
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
