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
