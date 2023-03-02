-- Project setup
set_project("altv-js-module")

set_languages("cxx20")

add_rules("mode.debug")
add_rules("mode.release")

if is_os("windows") then
    add_toolchains("msvc")
    add_cxxflags("/MP")
elseif is_os("linux") then
    add_toolchains("gcc")
end

-- Options
option("static-client")
    set_description("Build client as static library")
    set_default(false)
    set_showmenu(true)

option("sdk-path")
    set_description("Path to the C++ SDK to use")
    set_default("deps/cpp-sdk")
    set_showmenu(true)

option("auto-update-deps")
    set_description("Automatically update dependencies")
    set_default(true)
    set_showmenu(true)

-- Rules
rule("generate-bindings")
    before_build(function(target)
        local out = os.iorun("node tools/generate-bindings.js .. " .. target:name())
        if out ~= "" and is_mode("debug") then
            print(out)
        end
    end)

rule("update-deps")
    before_build(function(target)
        if not has_config("auto-update-deps") then return end
        import("core.project.config")
        os.iorun("node tools/update-deps.js " .. target:name() .. " " .. tostring(config.get("mode")))
    end)

-- Targets
target("cpp-sdk")
    set_kind("headeronly")
    add_headerfiles("$(sdk-path)/**.h")
    before_build(function(target)
        local oldDir = os.cd("$(sdk-path)")
        local out, err = os.iorun("git rev-parse --short HEAD")
        if err ~= "" then
            raise("Failed to get cpp-sdk git commit hash: " .. err)
            return
        end
        io.writefile("version/version.h", "#define ALT_SDK_VERSION \"" .. string.trim(out) .. "\"")
        os.cd(oldDir)
    end)

target("shared")
    set_basename("altv-js-shared")
    set_kind("static")
    add_files("shared/src/**.cpp")
    add_headerfiles("shared/src/**.h")
    add_includedirs("shared/src", "deps", "tools/out")
    add_deps("cpp-sdk")

target("server")
    set_basename("altv-js-module")
    set_kind("binary")
    add_files("server/src/**.cpp")
    add_headerfiles("server/src/**.h")
    add_includedirs("server/src", "server/deps", "shared/src", "deps", "tools/out")
    add_deps("shared")
    add_rules("generate-bindings", "update-deps")

    if is_os("linux") then
        add_links("server/deps/nodejs/lib/libnode.108")
    elseif is_mode("debug") then
        add_links("server/deps/nodejs/lib/Debug/libnode")
    else
        add_links("server/deps/nodejs/lib/Release/libnode")
    end

target("client")
    set_basename("altv-js-client")
    if has_config("static-client") then
        set_kind("static")
    else
        set_kind("shared")
    end
    add_files("client/src/**.cpp")
    add_headerfiles("client/src/**.h")
    add_includedirs("client/src", "client/deps", "shared/src", "deps", "tools/out")
    add_deps("shared")
    add_rules("generate-bindings", "update-deps")

    if is_mode("debug") then
        add_linkdirs("client/deps/v8/lib/Debug")
    else
        add_linkdirs("client/deps/v8/lib/Release")
    end
    add_links("v8_monolith")
