// Custom stack trace handling

Error.showInternals = false;

function isValidFrame(frame) {
    const showInternals = Error.showInternals || alt.isDebug;
    return !(!showInternals && frame.getFileName()?.startsWith("internal:"));
}

/**
 * @param {Error} error
 * @param {({})[]} frames
 * @returns
 */
Error.prepareStackTrace = function (error, frames) {
    let formatted = "";

    let errorStr;
    try {
        errorStr = error.toString();
    } catch (e) {
        errorStr = `<error>`;
    }
    formatted += errorStr;

    for (let i = 0; i < frames.length; i++) {
        const frame = frames[i];
        if (!isValidFrame(frame)) continue;
        formatted += `\n    at ${frame.toString()}`;
    }

    return formatted;
};
