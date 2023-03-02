-- Project setup
set_project("altv-js-module")

set_languages("cxx20")
add_cxxflags("cl::/MP")

if is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
elseif is_mode("release") then
    set_symbols("hidden")
    set_optimize("faster")
end

-- Rules
rule("generate-bindings")
    before_build(function(target)
        local scope = target:values("bindings.scope")
        if(scope == nil) then
            raise("Bindings scope not set for target " .. target:name())
            return
        end
        local stdout = os.iorun("node tools/generate-bindings.js .. " .. scope)
        if(stdout ~= "" and is_mode("debug")) then
            print(stdout)
        end
    end)

-- Targets
target("cpp-sdk")
    set_kind("headeronly")
    add_headerfiles("deps/cpp-sdk/**.h")
    before_build(function(target)
        local oldDir = os.cd("deps/cpp-sdk")
        local out, err = os.iorun("git rev-parse --short HEAD")
        if(err ~= "") then
            raise("Failed to get cpp-sdk git commit hash: " .. err)
            return
        end
        os.cd(oldDir)
        io.writefile("deps/cpp-sdk/version/version.h", "#define ALT_SDK_VERSION \"" .. string.trim(out) .. "\"")
    end)

target("shared")
    set_kind("static")
    add_files("shared/src/**.cpp")
    add_headerfiles("shared/src/**.h")
    add_includedirs("shared/src", "deps", "tools/out")
    add_deps("cpp-sdk")

target("server")
    set_basename("altv-js-module")
    set_kind("shared")
    add_files("server/src/**.cpp")
    add_headerfiles("server/src/**.h")
    add_includedirs("server/src", "server/deps")
    add_deps("shared")
    set_values("bindings.scope", "SERVER")
    add_rules("generate-bindings")

target("client")
    set_basename("altv-js-client")
    set_kind("shared")
    add_files("client/src/**.cpp")
    add_headerfiles("client/src/**.h")
    add_includedirs("client/src", "client/deps")
    add_deps("shared")
    set_values("bindings.scope", "CLIENT")
    add_rules("generate-bindings")
