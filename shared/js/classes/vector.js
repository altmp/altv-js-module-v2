// clang-format off

export class Vector3 {
    constructor(...args) {
        [this.x, this.y, this.z] = this.#getArgValues(...args);
        Object.freeze(this);
    }

    add(...args) {
        const [x, y, z] = this.#getArgValues(...args);
        return new Vector3(this.x + x, this.y + y, this.z + z);
    }

    sub(...args) {
        const [x, y, z] = this.#getArgValues(...args);
        return new Vector3(this.x - x, this.y - y, this.z - z);
    }

    mul(...args) {
        const [x, y, z] = this.#getArgValues(...args);
        return new Vector3(this.x * x, this.y * y, this.z * z);
    }

    div(...args) {
        const [x, y, z] = this.#getArgValues(...args);
        if (x === 0 || y === 0 || z === 0) {
            throw new Error("Division by zero");
        }
        return new Vector3(this.x / x, this.y / y, this.z / z);
    }

    dot(...args) {
        const [x, y, z] = this.#getArgValues(...args);
        return this.x * x + this.y * y + this.z * z;
    }

    cross(...args) {
        const [x, y, z] = this.#getArgValues(...args);
        return new Vector3(this.y * z - this.z * y, this.z * x - this.x * z, this.x * y - this.y * x);
    }

    get lengthSquared() {
        return this.x * this.x + this.y * this.y + this.z * this.z;
    }

    get length() {
        return Math.sqrt(this.lengthSquared);
    }

    get normalized() {
        const length = this.length;
        if (length === 0) {
            return Vector3.zero;
        }
        return new Vector3(this.x / length, this.y / length, this.z / length);
    }

    get inverse() {
        return new Vector3(this.x ? 1 / this.x : 0, this.y ? 1 / this.y : 0, this.z ? 1 / this.z : 0);
    }

    get negative() {
        return new Vector3(-this.x, -this.y, -this.z);
    }

    angleTo(...args) {
        const [x, y, z] = this.#getArgValues(...args);
        const mag1 = this.length;
        const mag2 = Math.sqrt(x * x + y * y + z * z);
        const dot = this.dot(x, y, z);
        return Math.acos(dot / (mag1 * mag2));
    }

    angleToDegrees(...args) {
        return this.angleTo(...args) * (180 / Math.PI);
    }

    distanceTo(...args) {
        const [x, y, z] = this.#getArgValues(...args);
        const dx = this.x - x;
        const dy = this.y - y;
        const dz = this.z - z;
        return Math.sqrt(dx * dx + dy * dy + dz * dz);
    }

    distanceToSquared(...args) {
        const [x, y, z] = this.#getArgValues(...args);
        const dx = this.x - x;
        const dy = this.y - y;
        const dz = this.z - z;
        return dx * dx + dy * dy + dz * dz;
    }

    toFixed(precision = 4) {
        return new Vector3(parseFloat(this.x.toFixed(precision)), parseFloat(this.y.toFixed(precision)), parseFloat(this.z.toFixed(precision)));
    }

    toDegrees() {
        return new Vector3(this.x * (180 / Math.PI), this.y * (180 / Math.PI), this.z * (180 / Math.PI));
    }

    toRadians() {
        return new Vector3(this.x * (Math.PI / 180), this.y * (Math.PI / 180), this.z * (Math.PI / 180));
    }

    isInRange(range, ...args) {
        const [x, y, z] = this.#getArgValues(...args);
        return Math.abs(this.x - x) <= range && Math.abs(this.y - y) <= range && Math.abs(this.z - z) <= range;
    }

    lerp(alpha, ...args) {
        const [x, y, z] = this.#getArgValues(...args);
        return new Vector3(this.x + (x - this.x) * alpha, this.y + (y - this.y) * alpha, this.z + (z - this.z) * alpha);
    }

    #getArgValues(...args) {
        let values = [];
        if (args.length === 3) values = args;
        else if (args.length === 1) {
            const arg = args[0];
            if (arg instanceof Vector3) values = [arg.x, arg.y, arg.z];
            else if (Array.isArray(arg)) values = arg;
            else if (typeof arg === "object") values = Object.values(arg);
            else values = [arg, arg, arg];
        } else throw new Error("Invalid arguments");
        return values.map(valueToNumber);
    }

    static fromArray(arr) {
        return new Vector3(arr[0], arr[1], arr[2]);
    }
    static fromObject(obj) {
        return new Vector3(obj.x, obj.y, obj.z);
    }

    static zero = new Vector3(0, 0, 0);
    static one = new Vector3(1, 1, 1);
    static up = new Vector3(0, 0, 1);
    static down = new Vector3(0, 0, -1);
    static forward = new Vector3(0, 1, 0);
    static back = new Vector3(0, -1, 0);
    static left = new Vector3(-1, 0, 0);
    static right = new Vector3(1, 0, 0);
    static negativeInfinity = new Vector3(-Infinity, -Infinity, -Infinity);
    static positiveInfinity = new Vector3(Infinity, Infinity, Infinity);
}
cppBindings.registerExport(cppBindings.BindingExport.VECTOR3_CLASS, Vector3);

export class Vector2 {
    constructor(...args) {
        [this.x, this.y] = this.#getArgValues(...args);
        Object.freeze(this);
    }

    add(...args) {
        const [x, y] = this.#getArgValues(...args);
        return new Vector2(this.x + x, this.y + y);
    }

    sub(...args) {
        const [x, y] = this.#getArgValues(...args);
        return new Vector2(this.x - x, this.y - y);
    }

    mul(...args) {
        const [x, y] = this.#getArgValues(...args);
        return new Vector2(this.x * x, this.y * y);
    }

    div(...args) {
        const [x, y] = this.#getArgValues(...args);
        if (x === 0 || y === 0) {
            throw new Error("Division by zero");
        }
        return new Vector2(this.x / x, this.y / y);
    }

    dot(...args) {
        const [x, y] = this.#getArgValues(...args);
        return this.x * x + this.y * y;
    }

    get lengthSquared() {
        return this.x * this.x + this.y * this.y;
    }

    get length() {
        return Math.sqrt(this.lengthSquared);
    }

    get normalized() {
        const length = this.length;
        if (length === 0) {
            return Vector2.zero;
        }
        return new Vector2(this.x / length, this.y / length);
    }

    get inverse() {
        return new Vector2(this.x ? 1 / this.x : 0, this.y ? 1 / this.y : 0);
    }

    get negative() {
        return new Vector2(-this.x, -this.y);
    }

    angleTo(...args) {
        const [x, y] = this.#getArgValues(...args);
        const mag1 = this.length;
        const mag2 = Math.sqrt(x * x + y * y);
        const dot = this.dot(x, y);
        return Math.acos(dot / (mag1 * mag2));
    }

    angleToDegrees(...args) {
        return (this.angleTo(...args) * 180) / Math.PI;
    }

    distanceTo(...args) {
        const [x, y] = this.#getArgValues(...args);
        const dx = this.x - x;
        const dy = this.y - y;
        return Math.sqrt(dx * dx + dy * dy);
    }

    distanceToSquared(...args) {
        const [x, y] = this.#getArgValues(...args);
        const dx = this.x - x;
        const dy = this.y - y;
        return dx * dx + dy * dy;
    }

    toFixed(precision = 4) {
        return new Vector2(parseFloat(this.x.toFixed(precision)), parseFloat(this.y.toFixed(precision)));
    }

    toRadians() {
        return new Vector2((this.x * Math.PI) / 180, (this.y * Math.PI) / 180);
    }

    toDegrees() {
        return new Vector2((this.x * 180) / Math.PI, (this.y * 180) / Math.PI);
    }

    isInRange(range, ...args) {
        const [x, y] = this.#getArgValues(...args);
        return Math.abs(this.x - x) <= range && Math.abs(this.y - y) <= range;
    }

    lerp(alpha, ...args) {
        const [x, y] = this.#getArgValues(...args);
        return new Vector2(this.x + alpha * (x - this.x), this.y + alpha * (y - this.y));
    }

    #getArgValues(...args) {
        let values = [];
        if (args.length === 2) values = args;
        else if (args.length === 1) {
            const arg = args[0];
            if (arg instanceof Vector2) values = [arg.x, arg.y];
            else if (Array.isArray(arg)) values = arg;
            else if (typeof arg === "object") values = Object.values(arg);
            else values = [arg, arg];
        } else throw new Error("Invalid arguments");
        return values.map(valueToNumber);
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
cppBindings.registerExport(cppBindings.BindingExport.VECTOR2_CLASS, Vector2);

function valueToNumber(val) {
    if (val === Infinity || val === -Infinity) return val;
    return parseFloat(val);
}
