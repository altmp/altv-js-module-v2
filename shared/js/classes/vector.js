// clang-format off

// WIP
class VectorCache {
    #size = 0;
    #cache = new Map();
    #ctor = null;

    constructor(size, ctor) {
        this.#size = size;
        this.#ctor = ctor;
    }

    insert(values) {
        const map = this.#cache;
        for (let i = 0; i < this.#size; i++) {
            if (!map.has(values[i])) map.set(values[i], new Map());
            map = map.get(values[i]);
            if (i === this.#size - 1) map.set(values[i], new this.#ctor(...values));
        }
    }
    get(values) {
        const map = this.#cache;
        for (let i = 0; i < this.#size; i++) {
            if (!map.has(values[i])) return null;
            map = map.get(values[i]);
            if (i === this.#size - 1) return map.get(values[i]);
        }
    }
}

class Vector {
    #size = 0;
    values = [];

    constructor(size, values) {
        this.#size = size;
        this.values = values;
        Object.freeze(this);
    }

    add(...args) {
        let values = this.#getArgValues(...args);
        return new this.constructor(...this.values.map((value, i) => value + values[i]));
    }
    sub(...args) {
        let values = this.#getArgValues(...args);
        return new this.constructor(...this.values.map((value, i) => value - values[i]));
    }
    mul(...args) {
        let values = this.#getArgValues(...args);
        return new this.constructor(...this.values.map((value, i) => value * values[i]));
    }
    div(...args) {
        let values = this.#getArgValues(...args);
        return new this.constructor(...this.values.map((value, i) => value / values[i]));
    }

    dot(...args) {
        let values = this.#getArgValues(...args);
        let sum = 0;
        for (let i = 0; i < this.#size; i++) sum += this.values[i] * values[i];
        return sum;
    }

    toArray() {
        return Array.from(this.values);
    }

    toFixed(precision = 4) {
        let fixedValues = [];
        for (let i = 0; i < this.#size; i++) fixedValues.push(parseFloat(this.values[i].toFixed(precision)));
        return new this.constructor(...fixedValues);
    }

    get lengthSquared() {
        let sum = 0;
        for (let i = 0; i < this.#size; i++) sum += this.values[i] * this.values[i];
        return sum;
    }

    get length() {
        return Math.sqrt(this.lengthSquared);
    }

    get negative() {
        return new this.constructor(...this.values.map((value) => -value));
    }

    get inverse() {
        return new this.constructor(...this.values.map((value) => 1 / value));
    }

    get normalized() {
        return this.div(this.length);
    }

    distanceTo(...args) {
        return Math.sqrt(this.distanceToSquared(...args));
    }

    distanceToSquared(...args) {
        let values = this.#getArgValues(...args);
        let sum = 0;
        for (let i = 0; i < this.#size; i++) sum += (this.values[i] - values[i]) * (this.values[i] - values[i]);
        return sum;
    }

    angleTo(...args) {
        let values = this.#getArgValues(...args);
        let dot = this.dot(...values);
        let length = this.length * Math.sqrt(values.map((value) => value * value).reduce((a, b) => a + b));
        return Math.acos(dot / length);
    }

    angleToDegrees(...args) {
        return this.angleTo(...args) * (180 / Math.PI);
    }

    toDegrees() {
        return new this.constructor(...this.values.map((value) => value * (180 / Math.PI)));
    }

    toRadians() {
        return new this.constructor(...this.values.map((value) => value * (Math.PI / 180)));
    }

    isInRange(range, ...args) {
        let values = this.#getArgValues(...args);
        for (let i = 0; i < this.#size; i++) {
            if (this.values[i] < values[i] - range || this.values[i] > values[i] + range) return false;
        }
        return true;
    }

    lerp(ratio, ...args) {
        let values = this.#getArgValues(...args);
        return new this.constructor(...this.values.map((value, i) => value + (values[i] - value) * ratio));
    }

    #getArgValues(...args) {
        let values = [];
        if (args.length === this.#size) values = args;
        else if (args.length === 1) {
            const arg = args[0];
            if (arg instanceof Vector) values = arg.values;
            else if (Array.isArray(arg)) values = arg;
            else for (let i = 0; i < this.#size; i++) values.push(arg);
        } else throw new Error("Invalid arguments");
        return values;
    }
}

export class Vector3 extends Vector {
    constructor(...args) {
        let values;
        if (args.length === 3) values = [parseInt(args[0]), parseInt(args[1]), parseInt(args[2])];
        else if (args.length === 1) {
            const arg = args[0];
            if (Array.isArray(arg)) values = [parseInt(arg[0]), parseInt(arg[1]), parseInt(arg[2])];
            else if (typeof arg === "object") values = [parseInt(arg.x), parseInt(arg.y), parseInt(arg.z)];
            else values = [parseInt(arg), parseInt(arg), parseInt(arg)];
        } else throw new Error("Invalid arguments");
        super(3, values);
    }

    get x() {
        return this.values[0];
    }
    get y() {
        return this.values[1];
    }
    get z() {
        return this.values[2];
    }

    static fromArray(arr) {
        return new Vector3(arr[0], arr[1], arr[2]);
    }
    static fromObject(obj) {
        return new Vector3(obj.x, obj.y, obj.z);
    }

    static zero = new Vector3(0, 0, 0);
    static one = new Vector3(1, 1, 1);
    static back = new Vector3(0, -1, 0);
    static up = new Vector3(0, 0, 1);
    static down = new Vector3(0, 0, -1);
    static forward = new Vector3(0, 1, 0);
    static left = new Vector3(-1, 0, 0);
    static right = new Vector3(1, 0, 0);
    static negativeInfinity = new Vector3(-Infinity, -Infinity, -Infinity);
    static positiveInfinity = new Vector3(Infinity, Infinity, Infinity);
}
cppBindings.registerExport("classes:vector3", Vector3);

export class Vector2 extends Vector {
    constructor(...args) {
        let values;
        if (args.length === 2) values = [parseInt(args[0]), parseInt(args[1])];
        else if (args.length === 1) {
            const arg = args[0];
            if (Array.isArray(arg)) values = [parseInt(arg[0]), parseInt(arg[1])];
            else if (typeof arg === "object") values = [parseInt(arg.x), parseInt(arg.y)];
            else values = [parseInt(arg), parseInt(arg)];
        } else throw new Error("Invalid arguments");
        super(2, values);
    }

    get x() {
        return this.values[0];
    }
    get y() {
        return this.values[1];
    }

    static fromArray(arr) {
        return new Vector2(arr[0], arr[1]);
    }
    static fromObject(obj) {
        return new Vector2(obj.x, obj.y);
    }

    static zero = new Vector2(0, 0);
    static one = new Vector2(1, 1);
    static up = new Vector2(0, 1);
    static down = new Vector2(0, -1);
    static left = new Vector2(-1, 0);
    static right = new Vector2(1, 0);
    static negativeInfinity = new Vector2(-Infinity, -Infinity);
    static positiveInfinity = new Vector2(Infinity, Infinity);
}
cppBindings.registerExport("classes:vector2", Vector2);
