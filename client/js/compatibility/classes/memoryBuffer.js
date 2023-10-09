/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/logging.js");

class MemoryBuffer extends alt.Buffer {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        return new alt.Buffer(args[0]);
    }

    // NOTE (xLuxy): Don't think this will ever be used by a normal user, so won't botter adding it to v2
    get address() {
        alt.logError("MemoryBuffer.address is not implemented.");
        return 0;
    }

    free() {
        super.destroy();
    }

    ubyte(size) {
        return super.readUInt8(size);
    }

    ushort(size) {
        return super.readUInt16(size);
    }

    uint(size) {
        return super.readUInt32(size);
    }

    ulong(size) {
        return super.readUInt64(size);
    }

    byte(size) {
        return super.readInt8(size);
    }

    short(size) {
        return super.readInt16(size);
    }

    int(size) {
        return super.readInt32(size);
    }

    long(size) {
        return super.readInt64(size);
    }

    float(size) {
        return super.readFloat(size);
    }

    double(size) {
        return super.readDouble(size);
    }

    string(size) {
        return super.readString(size);
    }
}

cppBindings.registerCompatibilityExport("MemoryBuffer", MemoryBuffer);
