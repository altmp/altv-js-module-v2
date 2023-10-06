# Building

After cloning, run `git submodule update --init --recursive` command to pull required dependencies.

This project uses `Xmake` as the build system, as such it is very easy to build and run the individual targets.

To generate and configure the project without building use `xmake config`.

To build a specific target use `xmake build <TARGET>`. E.g. `xmake build server`.

Available targets are `client` and `server`. (All other targets are useless on their own)

The build output can be found in the `build` directory. On Windows e.g. `build/windows/x64/release`.

## Build options

To display the available configuration options for the project, use the `xmake f --help` command.

The build options have to be set when configuring the project.

## VSCode

Alternatively, it is possible to use the [XMake VSCode extension](https://marketplace.visualstudio.com/items?itemName=tboox.xmake-vscode).
When installed, it should detect the XMake configuration automatically after generating once, and then you have the XMake overview in the bottom section of VSCode.
![Image](https://i.imgur.com/hbWMbmy.png)
Then instead of running the XMake build command manually, you can just build the project by pressing the `Build` button.
By default it will build all targets, to build a specific target click on the `default` button and select the target needed.
