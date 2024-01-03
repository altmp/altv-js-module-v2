<img src="https://cdn.discordapp.com/attachments/758680546506178610/1083699499882532965/image.png" height="448" width="896"/>

# alt:V JS module v2

> NOTE: The v2 module is still a work in progress and not ready for production use.

Repository containing the new JS module v2 module for [alt:V multiplayer](https://altv.mp/).

## Structure

| Directory          | Description                                           |
| ------------------ | ----------------------------------------------------- |
| [/client](/client) | Clientside JS module powered by V8                    |
| [/server](/server) | Serverside JS module powered by Node.js               |
| [/shared](/shared) | Shared code for the clientside & serverside module    |
| [/docs](/docs)     | Documentation for the internal workings of the module |
| [/deps](/deps)     | Global dependencies                                   |
| [/tools](/tools)   | Scripts for any tooling related to the module         |
| [/types](/types)   | Typings for the API                                   |

## Contributions

All contributions are greatly appreciated.
If there are any questions or you would like to discuss a feature, contact the _module maintainer_.

## Installing Module

## Installing the Module on the Client

**NOTE:** Client modules are only loaded when you are on the `dev` branch and have `debug` mode enabled.

1. Download the latest `js-module-v2-windows-client.zip` file from the [Releases page](https://github.com/altmp/altv-js-module-v2/releases/latest).

2. Copy the `modules` folder into your alt:V client directory (the folder where `altv.exe` is located).

3. Once you start alt:V, a popup will appear, asking whether you want to run unofficial modules. Click "Yes"

## Installing the Module on Your Server

**NOTE:** Your server must be on the latest `dev` branch for the module to load correctly.

1. Download the latest `js-module-v2-windows-server.zip` or `js-module-v2-linux.zip` file from the [Releases page](https://github.com/altmp/altv-js-module-v2/releases/latest).

2. Copy the `modules/js-module-v2.*` files (for Windows) or `libjs-module-v2.so` file (for Linux) into your server's `modules` folder.

3. Copy the `libnodev2.dll` file (for Windows) or `libnodev2.so` file (for Linux) into the root folder of your server, where your `altv-server.exe` (for Windows) or `altv-server` (for Linux) executable is located.

4. Load the module by adding `'js-module-v2'` to the array of modules in your `server.toml` file.

5. Create a resource with ``type = "jsv2"`` and ``client-type = "jsv2"`` in ``resource.toml`` file.

Alternatively, you can also download the server module from the official alt:V CDN server:

-   **Windows:** [https://cdn.alt-mp.com/js-module-v2/dev/x64_win32/update.json](https://cdn.alt-mp.com/js-module-v2/dev/x64_win32/update.json)

-   **Linux:** [https://cdn.alt-mp.com/js-module-v2/dev/x64_linux/update.json](https://cdn.alt-mp.com/js-module-v2/dev/x64_linux/update.json)

## v1 Interopability

Add this to `resource.toml` to use v1 API (`alt-client`, `alt-server`, etc.)
```toml
[js-module-v2]
compatibilityEnabled = true
```
