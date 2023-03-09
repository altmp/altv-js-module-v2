// clang-format off
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

// Paths to search for JS bindings
const paths = [
    { path: "client/js/", scope: "client" },
    { path: "server/js/", scope: "server" },
    { path: "shared/js/", scope: "shared" }
];

// Full output file
const resultTemplate = `// !!! THIS FILE WAS AUTOMATICALLY GENERATED (ON {DATE}), DO NOT EDIT MANUALLY !!!
#include "Bindings.h"

namespace js {
    std::unordered_map<std::string, Binding> Binding::__bindings =
    {
        {BINDINGS_LIST}
    };
}
`;

// Template for each binding item in the bindings map
const bindingTemplate = `{ "{BINDING_NAME}", Binding{ "{BINDING_NAME}", Binding::Scope::{BINDING_SCOPE}, { {BINDING_SRC} } } }`;

// Result bindings output path
const outputPath = "shared/src/BindingsMap.cpp";

(async() => {
    showLog("Generating bindings...");
    const bindings = [];
    for (const { path, scope: pathScope } of paths) {
        const bindingsPath = pathUtil.resolve(__dirname, basePath, path);
        for await(const file of getBindingFiles(bindingsPath)) {
            const name = pathUtil.relative(bindingsPath, file).replace(/\\/g, "/").toLowerCase();
            // Generate the binding data
            const src = await fs.readFile(file, "utf8");
            // Concat with existing binding, to allow for shared bindings to be added on by client/server bindings
            const existingBinding = bindings.find(binding => binding.name === name);
            if(existingBinding) {
                existingBinding.src += "," + getBindingCodeChars(src);
                if(pathScope === "shared") existingBinding.scope = "SHARED";
            }
            else bindings.push({ name: `${pathScope}/${name}`, src: getBindingCodeChars(src), scope: pathScope.toUpperCase() });
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

/**
 * @param {string} src
 */
function getBindingCodeChars(src) {
    // This const has to be added so the bindings work at runtime,
    // as the global __alt is removed after loading the bindings
    let code;
    if(!src.includes("const alt =")) code = `const alt = __alt;\n${src}`;
    else code = src;
    const chars = code.split("").map((char) => char.charCodeAt(0));
    return chars.toString();
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
