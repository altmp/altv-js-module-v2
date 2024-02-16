/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

requireBinding("shared/logging.js");

class MemoryBuffer extends alt.Buffer {
    constructor(size) {
        return new alt.Buffer(size);
    }

    // NOTE (xLuxy): Don't think this will ever be used by a normal user, so won't botter adding it to v2
    get address() {
        alt.logError("MemoryBuffer.address is not implemented.");
        return 0;
    }

    free() {
        this.destroy();
    }

    ubyte(size) {
        return this.readUInt8(size);
    }

    ushort(size) {
        return this.readUInt16(size);
    }

    uint(size) {
        return this.readUInt32(size);
    }

    ulong(size) {
        return this.readUInt64(size);
    }

    byte(size) {
        return this.readInt8(size);
    }

    short(size) {
        return this.readInt16(size);
    }

    int(size) {
        return this.readInt32(size);
    }

    long(size) {
        return this.readInt64(size);
    }

    float(size) {
        return this.readFloat(size);
    }

    double(size) {
        return this.readDouble(size);
    }

    string(size) {
        return this.readString(size);
    }
}

extendAltEntityClass(alt.Buffer, MemoryBuffer);

cppBindings.registerCompatibilityExport("MemoryBuffer", MemoryBuffer);
