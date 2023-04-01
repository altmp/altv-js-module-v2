// clang-format off
// Updates the dependencies of the client and server
// Usage: node tools/update-deps.js [scope=client|server|all] [mode=debug|release]

const fs = require("fs/promises");
const { createWriteStream } = require("fs");
const pathUtil = require("path");
const crypto = require("crypto");
const childProcess = require("child_process");
const https = require("https");

// Script arguments
const SCOPE = process.argv[2] ?? "all";
if (SCOPE !== "client" && SCOPE !== "server" && SCOPE !== "all") {
    console.error("Invalid scope");
    process.exit(1);
}
const DEBUG = process.argv[3] === "debug";

// Constants
const CDN_URL = "https://cdn.alt-mp.com";
const CLIENT_FILES = [
    {
        name: "v8_monolith.lib",
        path: "client/deps/v8/lib/Release",
        urlPath: "deps/v8/{BRANCH}/x64_win32/Release",
        os: "x64_win32",
    },
    {
        name: "v8_monolith.lib",
        path: "client/deps/v8/lib/Debug",
        urlPath: "deps/v8/{BRANCH}/x64_win32/Debug",
        os: "x64_win32",
        debugOnly: true,
    },
];
const SERVER_FILES = [
    {
        name: "libnode.lib",
        path: "server/deps/nodejs/lib/Release",
        urlPath: "deps/nodejs/{BRANCH}/x64_win32/Release",
        os: "x64_win32",
    },
    {
        name: "libnode.dll",
        path: "server/deps/nodejs/lib/Release",
        urlPath: "deps/nodejs/{BRANCH}/x64_win32/Release",
        os: "x64_win32",
    },
    {
        name: "libnode.lib",
        path: "server/deps/nodejs/lib/Debug",
        urlPath: "deps/nodejs/{BRANCH}/x64_win32/Debug",
        os: "x64_win32",
        debugOnly: true,
    },
    {
        name: "libnode.dll",
        path: "server/deps/nodejs/lib/Debug",
        urlPath: "deps/nodejs/{BRANCH}/x64_win32/Debug",
        os: "x64_win32",
        debugOnly: true,
    },
    {
        name: "libnode.so.108",
        path: "server/deps/nodejs/lib",
        urlPath: "deps/nodejs/{BRANCH}/x64_linux",
        os: "x64_linux",
    },
];

(async () => {
    const files =
        SCOPE === "client" ? CLIENT_FILES : SCOPE === "server" ? SERVER_FILES : CLIENT_FILES.concat(SERVER_FILES);
    for (const file of files) {
        if (file.debugOnly && !DEBUG) continue;
        if (file.os !== getOSName()) continue;
        const fileUrlPath = file.urlPath.replace("{BRANCH}", getGitBranch()).replace("{OS}", getOSName());
        const url = `${CDN_URL}/${fileUrlPath}/${file.name}`;
        const path = pathUtil.resolve(__dirname, "../", file.path, file.name);

        let hash = "INVALID";
        const fileExists = await doesFileExist(path);
        if (fileExists) hash = await getFileHash(path);
        const cdnInfo = await getCDNInfo(url);
        const name = pathUtil.basename(path);
        if (cdnInfo.hashList[name] === hash) return;

        console.log(`Downloading ${name}... (Version: ${cdnInfo.version})`);
        await downloadFile(url, path);
    }
})();

function downloadFile(url, path) {
    return new Promise((resolve, reject) => {
        https
            .get(url, (res) => {
                const stream = createWriteStream(path, { flags: "w" });
                res.pipe(stream);
                stream.on("finish", resolve);
                stream.on("error", reject);
            })
            .on("error", reject);
    });
}

/**
 * @param {string} path
 * @returns { Promise<{ version: string, hashList: { [name: string]: string }, sizeList: { [name: string]: string } }> }
 */
function getCDNInfo(path) {
    return new Promise((resolve, reject) => {
        const basePath = pathUtil.dirname(path);
        https
            .get(`${basePath}/update.json`, (res) => {
                let data = "";
                res.on("data", (chunk) => (data += chunk));
                res.on("end", () => resolve(JSON.parse(data)));
            })
            .on("error", reject);
    });
}

async function getFileHash(file) {
    const content = await fs.readFile(file);
    return crypto.createHash("sha1").update(content).digest("hex");
}

function getGitBranch() {
    let branch = "dev";
    const gitBranch = childProcess.execSync("git rev-parse --abbrev-ref HEAD", { encoding: "utf8" });
    if (gitBranch === "rc") branch = "rc";
    else if (gitBranch === "release") branch = "release";
    return branch;
}

function getOSName() {
    return process.platform === "win32" ? "x64_win32" : "x64_linux";
}

async function doesFileExist(path) {
    try {
        await fs.stat(path);
        return true;
    } catch {
        return false;
    }
}
