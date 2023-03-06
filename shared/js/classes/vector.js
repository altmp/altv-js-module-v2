// clang-format off

export class Vector3 {
    x = 0;
    y = 0;
    z = 0;

    constructor(...args) {
        if(args.length === 3) {
            this.x = args[0];
            this.y = args[1];
            this.z = args[2];
        }
        else if(args.length === 1) {
            const arg = args[0];
            if(typeof arg === "object") {
                const obj = arg;
                this.x = obj.x;
                this.y = obj.y;
                this.z = obj.z;
            }
            else if(Array.isArray(arg)) {
                const arr = arg;
                this.x = arr[0];
                this.y = arr[1];
                this.z = arr[2];
            }
        }
        else throw new Error("Invalid arguments");
    }

    toArray() {
        return [this.x, this.y, this.z];
    }

    static fromArray(arr) {
        return new Vector3(arr[0], arr[1], arr[2]);
    }
    static fromObject(obj) {
        return new Vector3(obj.x, obj.y, obj.z);
    }
}

export class Vector2 {
    x = 0;
    y = 0;

    constructor(...args) {
        if(args.length === 2) {
            this.x = args[0];
            this.y = args[1];
        }
        else if(args.length === 1) {
            const arg = args[0];
            if(typeof arg === "object") {
                const obj = arg;
                this.x = obj.x;
                this.y = obj.y;
            }
            else if(Array.isArray(arg)) {
                const arr = arg;
                this.x = arr[0];
                this.y = arr[1];
            }
        }
        else throw new Error("Invalid arguments");
    }

    toArray() {
        return [this.x, this.y];
    }

    static fromArray(arr) {
        return new Vector2(arr[0], arr[1]);
    }
    static fromObject(obj) {
        return new Vector2(obj.x, obj.y);
    }
}

// Available globally
globalThis.Vector3 = Vector3;
globalThis.Vector2 = Vector2;
