// clang-format off

export class Quaternion {
    #x = 0;
    #y = 0;
    #z = 0;
    #w = 0;

    constructor(...args) {
        this.#x = x;
        this.#y = y;
        this.#z = z;
        this.#w = w;
        if (args.length === 4) {
            this.#x = parseInt(args[0]);
            this.#y = parseInt(args[1]);
            this.#z = parseInt(args[2]);
            this.#w = parseInt(args[3]);
        } else if (args.length === 1) {
            const arg = args[0];
            if (Array.isArray(arg)) {
                this.#x = parseInt(arg[0]);
                this.#y = parseInt(arg[1]);
                this.#z = parseInt(arg[2]);
                this.#w = parseInt(arg[3]);
            } else if (typeof arg === "object") {
                this.#x = parseInt(arg.x);
                this.#y = parseInt(arg.y);
                this.#z = parseInt(arg.z);
                this.#w = parseInt(arg.w);
            }
        }
    }

    get x() {
        return this.#x;
    }
    get y() {
        return this.#y;
    }
    get z() {
        return this.#z;
    }
    get w() {
        return this.#w;
    }

    get length() {
        return Math.sqrt(this.lengthSquared);
    }

    get lengthSquared() {
        return this.#x * this.#x + this.#y * this.#y + this.#z * this.#z + this.#w * this.#w;
    }

    get conjugate() {
        return new Quaternion(-this.#x, -this.#y, -this.#z, this.#w);
    }

    get inverse() {
        return this.conjugate.multiply(1 / this.lengthSquared);
    }

    get normalized() {
        return this.multiply(1 / this.length);
    }

    get pitch() {
        return Math.atan2(2 * (this.#w * this.#x + this.#y * this.#z), 1 - 2 * (this.#x * this.#x + this.#y * this.#y));
    }

    get yaw() {
        return Math.asin(2 * (this.#w * this.#y - this.#z * this.#x));
    }

    get roll() {
        return Math.atan2(2 * (this.#w * this.#z + this.#x * this.#y), 1 - 2 * (this.#y * this.#y + this.#z * this.#z));
    }

    get eulerAngles() {
        return new Vector3(this.pitch, this.yaw, this.roll);
    }

    get axis() {
        const s = Math.sqrt(1 - this.#w * this.#w);
        if (s < 0.001) {
            return new Vector3(this.#x, this.#y, this.#z);
        } else {
            return new Vector3(this.#x / s, this.#y / s, this.#z / s);
        }
    }

    get angle() {
        return 2 * Math.acos(this.#w);
    }

    get matrix() {
        const x = this.#x;
        const y = this.#y;
        const z = this.#z;
        const w = this.#w;

        const xx = x * x;
        const xy = x * y;
        const xz = x * z;
        const xw = x * w;

        const yy = y * y;
        const yz = y * z;
        const yw = y * w;

        const zz = z * z;
        const zw = z * w;

        return [1 - 2 * (yy + zz), 2 * (xy - zw), 2 * (xz + yw), 0, 2 * (xy + zw), 1 - 2 * (xx + zz), 2 * (yz - xw), 0, 2 * (xz - yw), 2 * (yz + xw), 1 - 2 * (xx + yy), 0, 0, 0, 0, 1];
    }

    get forward() {
        return new Vector3(2 * (this.#x * this.#z + this.#w * this.#y), 2 * (this.#y * this.#z - this.#w * this.#x), 1 - 2 * (this.#x * this.#x + this.#y * this.#y));
    }

    get right() {
        return new Vector3(1 - 2 * (this.#y * this.#y + this.#z * this.#z), 2 * (this.#x * this.#y + this.#w * this.#z), 2 * (this.#x * this.#z - this.#w * this.#y));
    }

    get up() {
        return new Vector3(2 * (this.#x * this.#y - this.#w * this.#z), 1 - 2 * (this.#x * this.#x + this.#z * this.#z), 2 * (this.#y * this.#z + this.#w * this.#x));
    }

    get left() {
        return new Vector3(1 - 2 * (this.#y * this.#y + this.#z * this.#z), 2 * (this.#x * this.#y - this.#w * this.#z), 2 * (this.#x * this.#z + this.#w * this.#y));
    }

    get back() {
        return new Vector3(2 * (this.#x * this.#z - this.#w * this.#y), 2 * (this.#y * this.#z + this.#w * this.#x), 1 - 2 * (this.#x * this.#x + this.#y * this.#y));
    }

    get down() {
        return new Vector3(2 * (this.#x * this.#y + this.#w * this.#z), 1 - 2 * (this.#x * this.#x + this.#z * this.#z), 2 * (this.#y * this.#z - this.#w * this.#x));
    }

    static fromEuler(x, y, z) {
        const c1 = Math.cos(x / 2);
        const c2 = Math.cos(y / 2);
        const c3 = Math.cos(z / 2);
        const s1 = Math.sin(x / 2);
        const s2 = Math.sin(y / 2);
        const s3 = Math.sin(z / 2);

        return new Quaternion(s1 * c2 * c3 + c1 * s2 * s3, c1 * s2 * c3 - s1 * c2 * s3, c1 * c2 * s3 + s1 * s2 * c3, c1 * c2 * c3 - s1 * s2 * s3);
    }

    static fromAxisAngle(axis, angle) {
        const halfAngle = angle / 2;
        const s = Math.sin(halfAngle);

        return new Quaternion(axis.x * s, axis.y * s, axis.z * s, Math.cos(halfAngle));
    }

    static fromMatrix(matrix) {
        const trace = matrix[0] + matrix[5] + matrix[10];
        let S = 0;

        if (trace > 0) {
            S = Math.sqrt(trace + 1.0) * 2;
            return new Quaternion((matrix[6] - matrix[9]) / S, (matrix[8] - matrix[2]) / S, (matrix[1] - matrix[4]) / S, 0.25 * S);
        } else if (matrix[0] > matrix[5] && matrix[0] > matrix[10]) {
            S = Math.sqrt(1.0 + matrix[0] - matrix[5] - matrix[10]) * 2;
            return new Quaternion(0.25 * S, (matrix[1] + matrix[4]) / S, (matrix[8] + matrix[2]) / S, (matrix[6] - matrix[9]) / S);
        } else if (matrix[5] > matrix[10]) {
            S = Math.sqrt(1.0 + matrix[5] - matrix[0] - matrix[10]) * 2;
            return new Quaternion((matrix[1] + matrix[4]) / S, 0.25 * S, (matrix[6] + matrix[9]) / S, (matrix[8] - matrix[2]) / S);
        } else {
            S = Math.sqrt(1.0 + matrix[10] - matrix[0] - matrix[5]) * 2;
            return new Quaternion((matrix[8] + matrix[2]) / S, (matrix[6] + matrix[9]) / S, 0.25 * S, (matrix[1] - matrix[4]) / S);
        }
    }

    static fromArray(array) {
        return new Quaternion(array[0], array[1], array[2], array[3]);
    }
}
cppBindings.registerExport(cppBindings.BindingExport.QUATERNION_CLASS, Quaternion);
