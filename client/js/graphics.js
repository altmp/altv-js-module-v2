/// <reference path="../../types/client/index.d.ts"/>
/// <reference path="../../types/shared/index.d.ts"/>
/// <reference path="../../types/natives/index.d.ts"/>
// import * as alt from "@altv/client";
// import * as native from "@altv/natives";

// clang-format off
/** @type {typeof import("./../../shared/js/utils.js")} */
const { assert, assertRGBA, assertVector2, assertVector3 } = requireBinding("shared/utils.js");
requireBinding("shared/timers.js");

const natives = cppBindings.getBuiltinModule("@altv/natives");

function assertDrawTextArgs(text, font, scale, color, outline, dropShadow, textAlign) {
    assert(typeof text === "string", "Expected a string as first argument");
    assert(typeof font === "number", "Expected a number as third argument");
    assert(typeof scale === "number", "Expected a number as fourth argument");
    assertRGBA(color, "Expected RGBA as fifth argument");
    assert(typeof outline === "boolean", "Expected boolean as sixth argument");
    assert(typeof dropShadow === "boolean", "Expected boolean as seventh argument");
    assert(typeof textAlign === "number", "Expected number as eighth argument");
}

function drawText2dThisFrame(text, pos2d = new alt.Vector2(0.5), font = 0, scale = 0.5, color = new alt.RGBA(255, 255, 255), outline = true, dropShadow = true, textAlign = 0) {
    assertDrawTextArgs(text, font, scale, color, outline, dropShadow, textAlign);
    assertVector2(pos2d, "Expected Vector2 as second argument");

    natives.setTextFont(font);
    natives.setTextProportional(false);
    natives.setTextScale(scale, scale);
    natives.setTextColour(color.r, color.g, color.b, color.a);
    natives.setTextEdge(2, 0, 0, 0, 150);

    if (outline) {
        natives.setTextOutline();
    }

    if (dropShadow) {
        natives.setTextDropshadow(0, 0, 0, 0, 255);
        natives.setTextDropShadow();
    }

    natives.setTextJustification(textAlign);

    if (textAlign === 2) {
        natives.setTextWrap(0, pos2d.x);
    }

    natives.beginTextCommandDisplayText("CELL_EMAIL_BCON");
    // Split text into pieces of max 99 chars blocks
    text.match(/.{1,99}/g)?.forEach((textBlock) => {
        natives.addTextComponentSubstringPlayerName(textBlock);
    });

    natives.endTextCommandDisplayText(pos2d.x, pos2d.y, 0);
}

function drawText2d(text, pos2d, font, scale, color, outline, dropShadow, textAlign) {
    return new alt.Timers.EveryTick(() => {
        alt.Drawing.drawText2dThisFrame(text, pos2d, font, scale, color, outline, dropShadow, textAlign);
    });
}

function drawText3dThisFrame(text, pos3d, font = 0, scale = 0.5, color = new alt.RGBA(255, 255, 255), outline = true, dropShadow = true, textAlign = 0) {
    assertDrawTextArgs(text, font, scale, color, outline, dropShadow, textAlign);
    assertVector3(pos3d, "Expected Vector3 as second argument");

    natives.setDrawOrigin(pos3d.x, pos3d.y, pos3d.z, false);
    natives.beginTextCommandDisplayText("STRING");
    natives.addTextComponentSubstringPlayerName(text);
    natives.setTextFont(font);
    natives.setTextScale(1, scale);

    natives.setTextJustification(textAlign);
    if (textAlign === 2) {
        natives.setTextWrap(0.0, pos2d.x);
    } else {
        natives.setTextWrap(0.0, 1.0);
    }

    natives.setTextColour(color.r, color.g, color.b, color.a);

    if (outline) natives.setTextOutline();
    if (dropShadow) {
        natives.setTextDropshadow(0, 0, 0, 0, 255);
        natives.setTextDropShadow();
    }

    natives.endTextCommandDisplayText(0, 0, 0);
    natives.clearDrawOrigin();
}

function drawText3d(text, pos3d, font, scale, color, outline, dropShadow, textAlign) {
    return new alt.Timers.EveryTick(() => {
        alt.Drawing.drawText3dThisFrame(text, pos3d, font, scale, color, outline, dropShadow, textAlign);
    });
}

alt.Drawing.drawText2dThisFrame = drawText2dThisFrame;
alt.Drawing.drawText2d = drawText2d;
alt.Drawing.drawText3dThisFrame = drawText3dThisFrame;
alt.Drawing.drawText3d = drawText3d;
