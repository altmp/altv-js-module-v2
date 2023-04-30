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

option("debug-bindings")
    set_description("Print generated bindings")
    set_default(false)
    set_showmenu(true)

option("module-version")
    set_description("Module version")
    set_default("internal")
    set_showmenu(true)

-- Rules
rule("generate-bindings")
    before_build(function(target)
        local out = os.iorun("node tools/generate-bindings.js ..")
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
    set_kind("headeronly")
    add_headerfiles("shared/src/**.h")
    add_deps("cpp-sdk")
    set_configdir("shared/src")
    add_configfiles("shared/src/Version.h.in")
    add_rules("generate-bindings")
    if has_config("debug-bindings") then
        add_defines("DEBUG_BINDINGS=1")
    end

target("server")
    set_basename("js-module-v2")
    set_kind("shared")
    add_files("server/src/**.cpp", "shared/src/**.cpp")
    add_headerfiles("server/src/**.h")
    add_includedirs(
        "server/src", "server/deps", "server/deps/nodejs/include", "server/deps/nodejs/deps/uv/include", "server/deps/nodejs/deps/v8/include",
        "shared/src",
        "deps", "deps/cpp-sdk",
        "build"
    )
    add_deps("shared")
    add_rules("update-deps")
    add_defines("ALT_SERVER_API", "NODE_WANT_INTERNALS=1", "HAVE_OPENSSL=1", "HAVE_INSPECTOR=1")
    add_defines("MODULE_VERSION=\"$(module-version)\"")

    if is_os("linux") then
        add_links("node")
        add_linkdirs("$(scriptdir)/server/deps/nodejs/lib")
    else
        if is_mode("debug") then add_links("server/deps/nodejs/lib/Debug/libnode")
        else add_links("server/deps/nodejs/lib/Release/libnode") end
        add_links("dbghelp", "winmm", "shlwapi", "advapi32")
    end
    set_runtimes("MD")
    set_symbols("debug")

target("client")
    set_enabled(false)
    set_basename("js-client-v2")
    if has_config("static-client") then
        set_kind("static")
    else
        set_kind("shared")
    end
    add_files("client/src/**.cpp", "shared/src/**.cpp")
    add_headerfiles("client/src/**.h")
    add_includedirs(
        "client/src", "client/deps", "client/deps/v8/include",
        "shared/src",
        "deps", "deps/cpp-sdk",
        "build"
    )
    add_deps("shared")
    add_rules("update-deps")
    add_defines("ALT_CLIENT_API", "V8_COMPRESS_POINTERS=1", "V8_31BIT_SMIS_ON_64BIT_ARCH=1", "V8_IMMINENT_DEPRECATION_WARNINGS=1")
    add_defines("MODULE_VERSION=\"$(module-version)\"")

    if is_mode("debug") then
        add_linkdirs("client/deps/v8/lib/Debug")
    else
        add_linkdirs("client/deps/v8/lib/Release")
    end
    add_links("dbghelp", "winmm", "shlwapi", "advapi32")
    add_links("v8_monolith")
    set_runtimes("MD")
