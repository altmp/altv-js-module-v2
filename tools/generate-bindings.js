// Generates the JSBindings.h file, which contains all the JS bindings for the server and client
// Usage: node tools/generate-bindings.js [basePath] [scope=shared|client|server]

const fs = require("fs").promises;
const pathUtil = require("path");

// Base path should point to the main directory of the repo
if(process.argv.length < 3) {
    showError("Missing 'basePath' argument");
    showUsage();
    process.exit(1);
}
const basePath = process.argv[2];
if(process.argv.length < 4) {
    showError("Missing 'scope' argument");
    showUsage();
    process.exit(1);
}
const scope = process.argv[3];
if(scope !== "shared" && scope !== "client" && scope !== "server") {
    showError("Invalid value for 'scope' argument, allowed values: ['shared', 'client', 'server']");
    showUsage();
    process.exit(1);
}

// Paths to search for JS bindings
const paths = [
    { path: "shared/js/", scope: "shared" },
    { path: "client/js/", scope: "client" },
    { path: "server/js/", scope: "server" }
];

// Full output file
const resultTemplate = `// !!! THIS FILE WAS AUTOMATICALLY GENERATED (ON {DATE}), DO NOT EDIT MANUALLY !!!
#pragma once
#include <string>
#include <unordered_map>

namespace JSBindings {
    struct Binding
    {
        bool valid = false;
        std::string name;
        enum class Scope { SHARED, SERVER, CLIENT } scope;
        std::string src;

        Binding() = default;
        Binding(const std::string& _name, Scope _scope, const std::string& _src) : valid(true), name(_name), scope(_scope), src(_src) {}
    };
    static std::unordered_map<std::string, Binding> __bindings =
    {
        {BINDINGS_LIST}
    };

    static const Binding& Get(const std::string& name)
    {
        static Binding invalidBinding;
        if(!__bindings.contains(name)) return invalidBinding;
        return __bindings.at(name);
    }
}
`;

// Template for each binding item in the bindings map
const bindingTemplate = `{ "{BINDING_NAME}", Binding{ "{BINDING_NAME}", Binding::Scope::{BINDING_SCOPE}, "{BINDING_SRC}" } }`;

// Result bindings output path
const outputPath = "tools/out/JSBindings.h";

(async() => {
    showLog("Generating bindings...");
    const bindings = [];
    for (const { path, scope: pathScope } of paths) {
        if(pathScope !== "shared" && pathScope !== scope) continue;
        const bindingsPath = pathUtil.resolve(__dirname, basePath, path);
        for await(const file of getBindingFiles(bindingsPath)) {
            const name = pathUtil.relative(bindingsPath, file).replace(/\\/g, "/").toLowerCase();
            // Generate the binding data
            const src = await fs.readFile(file, "utf8");
            // Concat with existing binding, to allow for shared bindings to be added on by client/server bindings
            const existingBinding = bindings.find(binding => binding.name === name);
            if(existingBinding) {
                existingBinding.src += cleanBindingSource(src);
                if(pathScope === "SHARED") existingBinding.scope = "SHARED";
            }
            else bindings.push({ name: name, src: cleanBindingSource(src), scope: pathScope.toUpperCase() });
            showLog(`Generated bindings for: ${pathUtil.relative(`${__dirname}/..`, file).replace(/\\/g, "/")}`);
        }
    }
    // Generate data for the bindings map
    let bindingsList = "";
    for(let i = 0; i < bindings.length; i++) {
        const binding = bindings[i];
        const bindingStr = bindingTemplate
            .replace(/\{BINDING_NAME\}/g, binding.name)
            .replace("{BINDING_SCOPE}", binding.scope)
            .replace("{BINDING_SRC}", binding.src);
        bindingsList += bindingStr;
        if(i < bindings.length - 1) bindingsList += ",\n        ";
    }

    const outputStr = resultTemplate
        .replace("{DATE}", `${getDate()} ${getTime()}`)
        .replace("{BINDINGS_LIST}", bindingsList);
    await fs.writeFile(pathUtil.resolve(__dirname, basePath, outputPath), outputStr);
    showLog(`Wrote bindings result to file: ${outputPath}`);
})();

// Recursively gets all binding files in the directory, returns an async iterator
async function* getBindingFiles(dir) {
    const items = await fs.readdir(dir, { withFileTypes: true });
    for (const item of items) {
        const path = pathUtil.resolve(dir, item.name);
        if(item.isDirectory()) yield* getBindingFiles(path);
        if(!path.endsWith(".js")) continue;
        else yield path;
    }
}

function cleanBindingSource(src) {
    let str = src.trim().replace(/\"/g, "\\\"");
    return str;
}

function getDate() {
    const date = new Date();
    const day = date.getDate(), month = date.getMonth() + 1, year = date.getFullYear();
    return `${day < 10 ? `0${day}` : day}/${month < 10 ? `0${month}` : month}/${year}`;
}

function getTime() {
    const date = new Date();
    const hours = date.getHours(), minutes = date.getMinutes(), seconds = date.getSeconds();
    return `${hours < 10 ? `0${hours}` : hours}:${minutes < 10 ? `0${minutes}` : minutes}:${seconds < 10 ? `0${seconds}` : seconds}`;
}

function showLog(...args) {
    console.log(`[${getTime()}]`, ...args);
}

function showError(...args) {
    console.error(`[${getTime()}]`, ...args);
}

function showUsage() {
    showLog("Usage: convert-bindings.js <basePath> <scope>");
    showLog("<basePath>: Path to the base of the repository");
    showLog("<scope>: 'SHARED' includes only shared bindings, 'CLIENT' shared and client bindings, 'SERVER' shared and server bindings");
}
